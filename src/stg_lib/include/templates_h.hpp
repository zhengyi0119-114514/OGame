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
    using iterator_category = std::forward_iterator_tag;
    using value_type = TViewObj;
    using difference_type = std::ptrdiff_t;
    using pointer = TViewObj *;
    using reference = TViewObj &;

  private:
    mutable std::mutex m_lock{};                      ///< Mutex for thread safety[线程安全互斥锁]
    std::vector<TViewObj> m_vObjects{};               ///< Storage for view objects[视图对象存储]
    std::map<std::string, handle> m_mNameHandleMap{}; ///< Name to handle mapping[名称到句柄的映射]

  public:
    /**
     * @brief Default constructor[默认构造函数]
     */
    view_obj_pool() = default;
    /**
     * @brief Copy constructor[拷贝构造函数]
     * @param o Object to copy[要拷贝的对象]
     */
    view_obj_pool(const view_obj_pool &o)
        requires std::copyable<std::vector<TViewObj>> && std::copyable<TViewObj>
    {
        m_mNameHandleMap = o.m_mNameHandleMap;
        m_vObjects = o.m_vObjects;
    }
    /**
     * @brief Move constructor[移动构造函数]
     * @param rr Object to move[要移动的对象]
     */
    view_obj_pool(view_obj_pool &&rr)
        requires std::movable<TViewObj>
    {
        m_mNameHandleMap = std::move(rr.m_mNameHandleMap);
        m_vObjects = std::move(rr.m_vObjects);
    }
    /**
     * @brief Swap contents with another pool[与另一个对象池交换内容]
     * @param o Pool to swap with[要交换的对象池]
     */
    void swap(view_obj_pool &o) noexcept
    {
        std::swap(m_mNameHandleMap, o.m_mNameHandleMap);
        std::swap(m_vObjects, o.m_vObjects);
    }
    /**
     * @brief Thread-safe swap[线程安全的交换操作]
     * @param o Pool to swap with[要交换的对象池]
     */
    void swap_ts(view_obj_pool &o) noexcept
    {
        mutex_helper l{m_lock};
        mutex_helper l2{o.m_lock};
        swap(o);
    }
    /**
     * @brief Add object to pool[添加对象到对象池]
     * @param svName Object name[对象名称]
     * @param crViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
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
    /**
     * @brief Add movable object to pool[添加可移动对象到对象池]
     * @param svName Object name[对象名称]
     * @param rrViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
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
    /**
     * @brief Thread-safe object addition[线程安全的对象添加]
     * @param svName Object name[对象名称]
     * @param crViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    handle add_object_ts(std::string_view svName, const TViewObj &crViewObj)
        requires std::copyable<TViewObj>
    {
        mutex_helper l{m_lock};
        return add_object(svName, crViewObj);
    }
    /**
     * @brief Thread-safe movable object addition[线程安全的可移动对象添加]
     * @param svName Object name[对象名称]
     * @param rrViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    handle add_object_ts(std::string_view svName, TViewObj &&rrViewObj)
        requires std::movable<TViewObj>
    {
        mutex_helper l{m_lock};
        return add_object(svName, std::move(rrViewObj));
    }
    // Memory inefficient implementation[内存效率低的实现]
    /**
     * @brief Add object with exception safety[添加对象(异常安全)]
     * @param svName Object name[对象名称]
     * @param rcViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    handle add_object_es(std::string_view svName, const TViewObj &rcViewObj)
        requires std::copyable<TViewObj>
    {
        view_obj_pool copy{*this};
        handle h = copy.add_object(svName, rcViewObj);
        swap(copy);
        return h;
    }
    // Memory inefficient implementation[内存效率低的实现]
    /**
     * @brief Add movable object with exception safety[添加可移动对象(异常安全)]
     * @param svName Object name[对象名称]
     * @param rrViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    handle add_object_es(std::string_view svName, TViewObj &&rrViewObj)
        requires std::movable<TViewObj>
    {
        view_obj_pool copy{*this};
        auto h = copy.add_object(svName, std::move(rrViewObj));
        swap(copy);
        return h;
    }
    /**
     * @brief Add multiple objects from range[从范围添加多个对象]
     * @tparam TRange Range type[范围类型]
     * @exception name_exist_error
     */
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
    /**
     * @brief Add multiple objects from initializer list[从初始化列表添加多个对象]
     * @param list Initializer list[初始化列表]
     * @return handle_vector Vector of handles[句柄向量]
     */
    handle_vector add_multiple_object(name_obj_initlist list)
    {
        return add_multiple_object<name_obj_initlist>(list);
    }
    /**
     * @brief Thread-safe multiple object addition from range[从范围线程安全添加多个对象]
     * @tparam TRange Range type[范围类型]
     */
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
                 handle_vector add_multiple_object_ts(TRange range)
                     requires std::movable<TViewObj> || std::copyable<TViewObj>
    {
        mutex_helper l{m_lock};
        add_multiple_object(range);
    }
    /**
     * @brief Thread-safe multiple object addition from initializer list[从初始化列表线程安全添加多个对象]
     * @param list Initializer list[初始化列表]
     * @return handle_vector Vector of handles[句柄向量]
     */
    handle_vector add_multiple_object_ts(name_obj_initlist list)
    {
        mutex_helper l{m_lock};
        return add_multiple_object(list);
    }
    /**
     * @brief Exception-safe multiple object addition from range[从范围异常安全添加多个对象]
     * @tparam TRange Range type[范围类型]
     */
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
    /**
     * @brief Exception-safe multiple object addition from initializer list[从初始化列表异常安全添加多个对象]
     * @param list Initializer list[初始化列表]
     * @return handle_vector Vector of handles[句柄向量]
     */
    handle_vector add_multiple_object_es(name_obj_initlist list)
        requires std::movable<TViewObj> || std::copyable<TViewObj>
    {
        return add_multiple_object_es<name_obj_initlist>(list);
    }
    /**
     * @brief Construct from range[从范围构造]
     * @tparam TRange Range type[范围类型]
     */
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TViewObj> || std::copyable<TViewObj>)
                 view_obj_pool(TRange range)
                     requires std::movable<TViewObj> || std::copyable<TViewObj>
        : view_obj_pool()
    {
        add_multiple_object(range);
    }
    view_obj_pool(name_obj_initlist list) : view_obj_pool()
    {
        add_multiple_object(list);
    }
    /**
     * @brief Get object by name[通过名称获取对象]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, const TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, const TViewObj &> at(std::string_view svName) const
    {
        if (std::string sName{svName}; m_mNameHandleMap.contains(sName))
        {
            handle h = m_mNameHandleMap.at(sName);
            auto &o = m_vObjects.at(h);
            return {h, o};
        }
        else
        {
            throw error_h::name_exist_error(sName);
        }
    }
    /**
     * @brief Get mutable object by name[通过名称获取可变对象]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, TViewObj &> at(std::string_view svName)
    {
        auto p = std::as_const(*this).at(svName);
        return {p.first, const_cast<TViewObj &>(p.second)};
    }
    /**
     * @brief Get object by handle[通过句柄获取对象]
     * @param h Object handle[对象句柄]
     * @return const TViewObj& Reference to object[对象引用]
     */
    const TViewObj &at(handle h) const
    {
        return m_vObjects.at(h);
    }
    /**
     * @brief Get mutable object by handle[通过句柄获取可变对象]
     * @param h Object handle[对象句柄]
     * @return TViewObj& Reference to object[对象引用]
     */
    TViewObj &at(handle h)
    {
        return const_cast<TViewObj &>(std::as_const(*this).at(h));
    }
    /**
     * @brief Subscript operator for const access[下标操作符(常量访问)]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, const TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, const TViewObj &> operator[](std::string_view svName) const
    {
        return at(svName);
    }
    /**
     * @brief Subscript operator for mutable access[下标操作符(可变访问)]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, TViewObj &> operator[](std::string_view svName)
    {
        return at(svName);
    }
    template <typename TIterator, std::ranges::range TContainer>
        requires std::input_or_output_iterator<TIterator>
    struct iter_t
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = typename TContainer::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

        TIterator iter;
        TContainer *cont;

        iter_t() = default;
        iter_t(TIterator i, TContainer *c) : iter(i), cont(c)
        {
        }

        iter_t &operator++()
        {
            ++iter;
            return *this;
        }
        iter_t operator++(int)
        {
            auto copy{*this};
            ++iter;
            return copy;
        }
        reference operator*()
        {
            return cont->at(iter->second);
        }
        const reference operator*() const
        {
            return cont->at(iter->second);
        }
        pointer operator->()
        {
            return &cont->at(iter->second);
        }
        const pointer operator->() const
        {
            return &cont->at(iter->second);
        }
        bool operator!=(const iter_t &rsh) const = default;
        bool operator==(const iter_t &rsh) const = default;
    };
    using iterator = iter_t<std::map<std::string, handle>::iterator, std::vector<TViewObj>>;
    iterator begin()
    {
        return {m_mNameHandleMap.begin(), &m_vObjects};
    }
    iterator end()
    {
        return {m_mNameHandleMap.end(), &m_vObjects};
    }
    using const_iterator = iter_t<std::map<std::string, handle>::const_iterator, const std::vector<TViewObj>>;
    const_iterator begin() const
    {
        return {m_mNameHandleMap.cbegin(), &m_vObjects};
    }
    const_iterator end() const
    {
        return {m_mNameHandleMap.cend(), &m_vObjects};
    }
    static_assert(std::forward_iterator<iterator>);
    static_assert(std::forward_iterator<const_iterator>);
    static_assert(std::ranges::range<view_obj_pool>);
};
template class view_obj_pool<open_stg::view_h::graphs_object>;

} // namespace open_stg::view_h
#endif
