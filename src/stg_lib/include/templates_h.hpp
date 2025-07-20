/**
 * @file templates_h.hpp
 * @author IcEtHoRn
 * @brief Thread-safe view object pool implementation[线程安全的视图对象池实现] \n
 * [你不会心甘情愿地看着你的项目变成一坨屎山。] \n
 * ["_ts后缀代表线程安全(抛出异常时状态将会损坏，无法使用，但运行速度快)，“_es"代表异常时安全]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-07-19
 *
 */
#ifndef OGAME_STGLIB_TEMPLATE_H
#define OGAME_STGLIB_TEMPLATE_H 1
#include "error_h.hpp"
#include "open_game.hpp"
#include <mutex>
#include <ranges>
#include <utility>
#include <vector>

namespace open_stg::view_h
{
struct mutex_helper
{
    std::mutex &ref;
    mutex_helper(std::mutex &r) : ref(r)
    {
        r.lock();
    }
    ~mutex_helper() noexcept
    {
        ref.unlock();
    }
};
/**
 * @brief [视图对象的线程安全池，不包含删除功能] \n
 * [构造函数非线程安全]
 * @tparam TViewObj Type of view object, must derive from view_obj[视图对象类型，必须继承自view_obj]
 */
template <typename TViewObj>
    requires std::derived_from<TViewObj, open_stg::view_h::view_obj> && std::destructible<TViewObj> &&
             (std::movable<TViewObj> || std::copyable<TViewObj>)
class view_obj_pool
{
  public:
    using name_obj_pair = std::pair<std::string, TViewObj>;
    using handle = uint32_t;
    using handle_vector = std::vector<handle>;
    using name_obj_initlist = std::initializer_list<name_obj_pair>;

  private:
    mutable std::mutex m_lock{};                      ///< Mutex for thread safety[线程安全互斥锁]
    std::vector<TViewObj> m_vObjects{};               ///< Storage for view objects[视图对象存储]
    std::map<std::string, handle> m_mNameHandleMap{}; ///< Name to handle mapping[名称到句柄的映射]

  public:
    view_obj_pool() = default;
    view_obj_pool(const view_obj_pool &o)
        requires std::copyable<std::vector<TViewObj>> && std::copyable<TViewObj>
    {
        m_mNameHandleMap = o.m_mNameHandleMap;
        m_vObjects = o.m_vObjects;
    }
    view_obj_pool(view_obj_pool &&rr)
        requires std::movable<TViewObj>
    {
        m_mNameHandleMap = std::move(rr.m_mNameHandleMap);
        m_vObjects = std::move(rr.m_vObjects);
    }
    void swap(view_obj_pool &o) noexcept
    {
        std::swap(m_mNameHandleMap, o.m_mNameHandleMap);
        std::swap(m_vObjects, o.m_vObjects);
    }
    void swap_ts(view_obj_pool &o) noexcept
    {
        mutex_helper l{m_lock};
        mutex_helper l2{o.m_lock};
        swap(o);
    }
    handle add_object(std::string_view svName, const TViewObj &crViewObj)
    {
        if (std::string sName{svName}; m_mNameHandleMap.contains(sName))
        {
            throw error_h::name_exist_error(sName);
        }
        else
        {
            handle hObj = m_vObjects.size();
            m_vObjects.push_back(crViewObj);
            m_mNameHandleMap.insert(std::pair<std::string, handle>(std::move(sName), hObj));
            return hObj;
        }
    }
    handle add_object(std::string_view svName, TViewObj &&rrViewObj)
        requires std::movable<TViewObj>
    {
        if (std::string sName{svName}; m_mNameHandleMap.contains(sName))
        {
            throw error_h::name_exist_error(sName);
        }
        else
        {
            handle hObj = m_vObjects.size();
            m_vObjects.push_back(std::move(rrViewObj));
            m_mNameHandleMap.insert(std::pair<std::string, handle>(std::move(sName), hObj));
            return hObj;
        }
    }

    handle add_object_ts(std::string_view svName, const TViewObj &crViewObj)
        requires std::copyable<TViewObj>
    {
        mutex_helper l{m_lock};
        return add_object(svName, crViewObj);
    }
    handle add_object_ts(std::string_view svName, TViewObj &&rrViewObj)
        requires std::movable<TViewObj>
    {
        mutex_helper l{m_lock};
        return add_object(svName, std::move(rrViewObj));
    }
    //[吐槽：看着就很费内存]
    handle add_object_es(std::string_view svName, const TViewObj &rcViewObj)
        requires std::copyable<TViewObj>
    {
        view_obj_pool copy{*this};
        handle h = copy.add_object(svName, rcViewObj);
        swap(copy);
        return h;
    }
    handle add_object_es(std::string_view svName, TViewObj &&rrViewObj)
        requires std::movable<TViewObj>
    {
        view_obj_pool copy{*this};
        auto h = copy.add_object(svName, std::move(rrViewObj));
        swap(copy);
        return h;
    }
    template <std::ranges::range TRange>
        requires std::same_as<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
    handle_vector add_multiple_object(const TRange &range)
    {
        handle_vector hs{};
        for (const auto &p : range)
        {
            // constexpr
            if constexpr (auto pair(p); std::copyable<TViewObj>)
            {
                hs.push_back(add_object(pair.first, pair.second));
            }
            else
            {
                hs.push_back(add_object(pair.first, std::move(pair.second)));
            }
        }
        return hs;
    }
    handle_vector add_multiple_object(name_obj_initlist list)
    {
        return add_multiple_object<name_obj_initlist>(list);
    }
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
                 handle_vector add_multiple_object_ts(TRange range)
                     requires std::movable<TViewObj> || std::copyable<TViewObj>
    {
        mutex_helper l{m_lock};
        add_multiple_object(range);
    }
    handle_vector add_multiple_object_ts(name_obj_initlist list)
    {
        mutex_helper l{m_lock};
        return add_multiple_object(list);
    }
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
    handle_vector add_multiple_object_es(TRange range)
    {
        view_obj_pool copy{*this};
        auto r = copy.add_multiple_object(range);
        swap(copy);
        return r;
    }
    handle_vector add_multiple_object_es(name_obj_initlist list)
        requires std::movable<TViewObj> || std::copyable<TViewObj>
    {
        return add_multiple_object_es<name_obj_initlist>(list);
    }
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
                 view_obj_pool(TRange range)
                     requires std::movable<TViewObj> || std::copyable<TViewObj> :view_obj_pool()
    {
        add_multiple_object(range);
    }
    view_obj_pool(name_obj_initlist list):view_obj_pool()
    {
        add_multiple_object(list);
    }
    
};
template class view_obj_pool<image>;
} // namespace open_stg::view_h
#endif
