/**
 * @file templates_h.hpp
 * @author IcEtHoRn
 * @brief Thread-safe view object pool implementation[线程安全的视图对象池实现] \n
 * [你不会心甘情愿地看着你的项目变成一坨屎山。] \n
 * ["_ts后缀代表线程安全，“_es"代表异常时安全，非异常安全版本抛出异常时状态将会损坏，无法使用] \n
 * []
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-07-19
 *
 */
#ifndef OGAME_STGLIB_TEMPLATE_H
#define OGAME_STGLIB_TEMPLATE_H 1
#include "og_macro.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <map>
#include <mutex>
#include <ranges>
#include <time.h>
#include <utility>
#include <vector>
#if __has_include("windows.h")
#include <windows.h>
#endif
namespace OpenGame
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
 * @brief [视图对象的线程安全池，不包含删除功能，用来处理留用对象，如图片，动画等资源] \n
 * [对象池中的对象将长期存在，生命周期将大于或等于对象池的生命周期] \n
 * [构造函数非线程安全]
 */
template <typename TObj>
    requires std::destructible<TObj> && (std::movable<TObj> || std::copyable<TObj>)
class object_pool
{
  public:
    using name_obj_pair = std::pair<std::string, TObj>;
    using handle = uint32_t;
    using handle_vector = std::vector<handle>;
    using name_obj_initlist = std::initializer_list<name_obj_pair>;
    using iterator_category = std::forward_iterator_tag;
    using value_type = TObj;
    using pointer = TObj *;
    using reference = TObj &;
    // using shared_value = std::shared_ptr<value_type>;
    void throw_exception_if_name_exists(const std::string &sName)
    {
        if (m_mNameHandleMap.contains(sName))
        {
            throw std::out_of_range(sName);
        }
    }

  private:
    mutable std::mutex m_lock{};                      ///< Mutex for thread safety[线程安全互斥锁]
    std::vector<TObj> m_vObjects{};                   ///< Storage for view objects[视图对象存储]
    std::map<std::string, handle> m_mNameHandleMap{}; ///< Name to handle mapping[名称到句柄的映射]

  public:
    /**
     * @brief Default constructor[默认构造函数]
     */
    object_pool() = default;
    /**
     * @brief Copy constructor[拷贝构造函数]
     * @param o Object to copy[要拷贝的对象]
     */
    object_pool(const object_pool &o)
        requires std::copyable<std::vector<TObj>> && std::copyable<TObj>
    {
        m_mNameHandleMap = o.m_mNameHandleMap;
        m_vObjects = o.m_vObjects;
    }
    /**
     * @brief Move constructor[移动构造函数]
     * @param rr Object to move[要移动的对象]
     */
    object_pool(object_pool &&rr)
        requires std::movable<TObj>
    {
        m_mNameHandleMap = std::move(rr.m_mNameHandleMap);
        m_vObjects = std::move(rr.m_vObjects);
    }
    /**
     * @brief Swap contents with another pool[与另一个对象池交换内容]
     * @param o Pool to swap with[要交换的对象池]
     */
    inline void swap(object_pool &o) noexcept
    {
        std::swap(m_mNameHandleMap, o.m_mNameHandleMap);
        std::swap(m_vObjects, o.m_vObjects);
    }
    /**
     * @brief Thread-safe swap[线程安全的交换操作]
     * @param o Pool to swap with[要交换的对象池]
     */
    inline void swap_ts(object_pool &o) noexcept
    {
        mutex_helper l{m_lock};
        mutex_helper l2{o.m_lock};
        swap(o);
    }
    // /**
    //  * @brief [把shared_ptr塞入对象池]
    //  *
    //  * @param svName
    //  * @param ptr
    //  * @return handle
    //  */
    // handle add_object_shared_ptr(std::string_view svName, std::shared_ptr<TObj> ptr)
    // {
    //     std::string sName{svName};
    //     throw_exception_if_name_exists(sName);
    //     handle hObj = m_vObjects.size();
    //     m_vObjects.push_back(ptr);
    //     m_mNameHandleMap.insert(std::pair<std::string, handle>(std::move(sName), hObj));
    //     return hObj;
    // }
    // template <typename TDerivedType>
    //     requires std::derived_from<TDerivedType, TObj>
    // handle add_derived_object_ptr(std::string_view svName, std::shared_ptr<TDerivedType> ptr)
    // {
    //     return add_derived_object_ptr(svName, std::dynamic_pointer_cast<TObj>(ptr));
    // }
    /**
     * @brief [在对象池中直接构造对象]
     * @tparam TArgs
     * @param svName
     * @param args
     * @return handle
     */
    template <typename... TArgs> inline handle emplace_object(std::string_view svName, TArgs... args)
    {
        // return add_object_shared_ptr(svName, std::make_shared<TObj>(std::forward<TArgs>(args)...));
        std::string sName{svName};
        throw_exception_if_name_exists(sName);
        handle hObj = m_vObjects.size();
        m_vObjects.emplace_back(std::forward<TArgs>(args)...);
        m_mNameHandleMap.insert(std::pair<std::string, handle>(std::move(sName), hObj));
        return hObj;
    }
    template <typename... TArgs> inline handle emplace_object_ts(std::string_view svName, TArgs &&...args)
    {
        mutex_helper l{m_lock};
        return emplace_object(svName, std::forward<TArgs>(args)...);
    }
    //[内存：你不要过来啊！！！]
    template <typename... TArgs> inline handle emplace_object_es(std::string_view svName, TArgs... args)
    {
        object_pool copy{*this};
        handle h = copy.emplace_object(svName, std::forward(args)...);
        this->swap(copy);
        return h;
    }
    /**
     * @brief Add object to pool[添加对象到对象池]
     * @param svName Object name[对象名称]
     * @param crViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    inline handle add_object(std::string_view svName, const TObj &crViewObj)
        requires std::copyable<TObj>
    {
        return emplace_object(svName, crViewObj);
    }
    /**
     * @brief Add movable object to pool[添加可移动对象到对象池]
     * @param svName Object name[对象名称]
     * @param rrViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    inline handle add_object(std::string_view svName, TObj &&rrViewObj)
        requires std::movable<TObj>
    {
        return emplace_object(svName, rrViewObj);
    }
    /**
     * @brief Thread-safe object addition[线程安全的对象添加]
     * @param svName Object name[对象名称]
     * @param crViewObj Object to add[要添加的对象]
     * @return handle Object handle[对象句柄]
     * @exception name_exist_error
     */
    inline handle add_object_ts(std::string_view svName, const TObj &crViewObj)
        requires std::copyable<TObj>
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
    inline handle add_object_ts(std::string_view svName, TObj &&rrViewObj)
        requires std::movable<TObj>
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
    inline handle add_object_es(std::string_view svName, const TObj &rcViewObj)
        requires std::copyable<TObj>
    {
        object_pool copy{*this};
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
    inline handle add_object_es(std::string_view svName, TObj &&rrViewObj)
        requires std::movable<TObj>
    {
        object_pool copy{*this};
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
                 (std::movable<TObj> || std::copyable<TObj>)
    handle_vector add_multiple_object(const TRange &range)
    {
        handle_vector hs{};
        for (const auto &p : range)
        {
            // constexpr
            if constexpr (auto pair(p); std::copyable<TObj>)
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
    inline handle_vector add_multiple_object(name_obj_initlist list)
    {
        return add_multiple_object<name_obj_initlist>(list);
    }
    /**
     * @brief Thread-safe multiple object addition from range[从范围线程安全添加多个对象]
     * @tparam TRange Range type[范围类型]
     */
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TObj> || std::copyable<TObj>)
                 inline handle_vector add_multiple_object_ts(TRange range)
                     requires std::movable<TObj> || std::copyable<TObj>
    {
        mutex_helper l{m_lock};
        add_multiple_object(range);
    }
    /**
     * @brief Thread-safe multiple object addition from initializer list[从初始化列表线程安全添加多个对象]
     * @param list Initializer list[初始化列表]
     * @return handle_vector Vector of handles[句柄向量]
     */
    inline handle_vector add_multiple_object_ts(name_obj_initlist list)
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
                 (std::movable<TObj> || std::copyable<TObj>)
    inline handle_vector add_multiple_object_es(TRange range)
    {
        object_pool copy{*this};
        auto r = copy.add_multiple_object(range);
        swap(copy);
        return r;
    }
    /**
     * @brief Exception-safe multiple object addition from initializer list[从初始化列表异常安全添加多个对象]
     * @param list Initializer list[初始化列表]
     * @return handle_vector Vector of handles[句柄向量]
     */
    inline handle_vector add_multiple_object_es(name_obj_initlist list)
        requires std::movable<TObj> || std::copyable<TObj>
    {
        return add_multiple_object_es<name_obj_initlist>(list);
    }
    /**
     * @brief Construct from range[从范围构造]
     * @tparam TRange Range type[范围类型]
     */
    template <std::ranges::range TRange>
        requires std::convertible_to<std::ranges::range_value_t<TRange>, name_obj_pair> &&
                 (std::movable<TObj> || std::copyable<TObj>)
                 object_pool(TRange range)
                     requires std::movable<TObj> || std::copyable<TObj>
        : object_pool()
    {
        add_multiple_object(range);
    }
    object_pool(name_obj_initlist list) : object_pool()
    {
        add_multiple_object(list);
    }
    /**
     * @brief Get object by name[通过名称获取对象]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, const TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, const TObj &> at(std::string_view svName) const
    {
        if (std::string sName{svName}; m_mNameHandleMap.contains(sName))
        {
            handle h = m_mNameHandleMap.at(sName);
            auto &o = m_vObjects.at(h);
            return {h, o};
        }
        else
        {
            throw std::out_of_range(sName);
        }
    }
    /**
     * @brief Get mutable object by name[通过名称获取可变对象]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, TObj &> at(std::string_view svName)
    {
        auto p = std::as_const(*this).at(svName);
        return {p.first, const_cast<TObj &>(p.second)};
    }
    /**
     * @brief Get object by handle[通过句柄获取对象]
     * @param h Object handle[对象句柄]
     * @return const TViewObj& Reference to object[对象引用]
     */
    const TObj &at(handle h) const
    {
        return m_vObjects.at(h);
    }
    /**
     * @brief Get mutable object by handle[通过句柄获取可变对象]
     * @param h Object handle[对象句柄]
     * @return TViewObj& Reference to object[对象引用]
     */
    TObj &at(handle h)
    {
        return const_cast<TObj &>(std::as_const(*this).at(h));
    }
    /**
     * @brief Subscript operator for const access[下标操作符(常量访问)]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, const TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, const TObj &> operator[](std::string_view svName) const
    {
        return at(svName);
    }
    /**
     * @brief Subscript operator for mutable access[下标操作符(可变访问)]
     * @param svName Object name[对象名称]
     * @return std::pair<handle, TViewObj &> Handle and object reference[句柄和对象引用]
     */
    std::pair<handle, TObj &> operator[](std::string_view svName)
    {
        return at(svName);
    }
    size_t size() const
    {
        If ConstExpr(IsDebug)
        {
            if (m_vObjects.size() != m_mNameHandleMap.size())
            {
                assert(true);
            }
        }
        return m_vObjects.size();
    }
    Void Clear()
    {
        m_mNameHandleMap.clear();
        m_vObjects.clear();
    }
    // using iterator = std::vector<std::shared_ptr<TObj>>::iterator;
    using iterator = std::vector<TObj>::iterator;
    inline iterator begin()
    {
        return m_vObjects.begin();
    }
    inline iterator end()
    {
        return m_vObjects.end();
    }
    // using const_iterator = std::vector<std::shared_ptr<TObj>>::const_iterator;
    using const_iterator = std::vector<TObj>::const_iterator;
    inline const_iterator cbegin() const
    {
        return m_vObjects.cbegin();
    }
    inline const_iterator cend() const
    {
        return m_vObjects.cend();
    }
    static_assert(std::forward_iterator<iterator>);
    static_assert(std::forward_iterator<const_iterator>);
};
template <typename T> using ObjectPool = object_pool<T>;
template class object_pool<int>;
using Boolean = uint8_t;
template <typename TObject> class CircularListIterator
{
  private:
    size_t m_sCurrentIndex = 0;
    const size_t m_csMaxSize = 0;
    std::span<TObject> m_containerSpan;

  public:
    CircularListIterator(std::span<TObject> containerSpan, size_t maxSize = 0)
        : m_sCurrentIndex(0), m_csMaxSize(maxSize != 0 ? maxSize : containerSpan.size()), m_containerSpan(containerSpan)
    {
        if (!m_csMaxSize)
        {
            throw std::invalid_argument(
                ":( 传入的span大小为零会无法运作的，亲！ || The incoming span with zero size won't work,dear!");
        }
    }
    void next()
    {
        if (m_sCurrentIndex++; m_sCurrentIndex >= m_csMaxSize)
        {
            m_sCurrentIndex = 0;
        }
    }
    size_t GetIndex()
    {
        return m_sCurrentIndex;
    }
};
template <typename T> using circular_list_iterator = CircularListIterator<T>;
template class CircularListIterator<int>;

// 什么神奇游戏需要每秒运算超过256次？
template <size_t sRingTimesPreSecond>
    requires(sRingTimesPreSecond <= std::numeric_limits<uint8_t>::max() && sRingTimesPreSecond > 0)
class Clock
{
  private:
    std::array<int64_t, sRingTimesPreSecond + 1> m_timeTable{};
    std::function<void(size_t)> m_fOnTimePass{};
    int64_t m_iOffset{};
    CircularListIterator<int64_t> m_iterator{m_timeTable, sRingTimesPreSecond};

  public:
    void SetPassCallBack(std::function<void(size_t)> f)
    {
        m_fOnTimePass = f;
    }
#if defined LINUX

  private:
    constexpr const static inline int64_t NS_PER_SEC = 1'000'000'000;
    int64_t timespecToInt64(const struct timespec &ts)
    {
        return ts.tv_sec * NS_PER_SEC + ts.tv_nsec;
    }
    struct timespec int64ToTimespec(int64_t i)
    {
        struct timespec ts;
        ts.tv_sec = i / NS_PER_SEC;
        ts.tv_nsec = i % NS_PER_SEC;
        return ts;
    }

  public:
    constexpr Clock()
    {
        for (size_t i = 0; i < sRingTimesPreSecond + 1; i++)
        {
            m_timeTable[i] = static_cast<int64_t>(i * NS_PER_SEC / 60.0l);
        }
    }
    inline void Init()
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        m_iOffset = timespecToInt64(ts);
    }
    void WaitToClockRing()
    {
        uint32_t uTriggeredCycles = 0;
        struct timespec tsNow{};
        clock_gettime(CLOCK_MONOTONIC, &tsNow);
        int64_t iNow{timespecToInt64(tsNow)};

        int64_t iTimeDifference = iNow - m_iOffset;
        int64_t iSecondPassed = iTimeDifference / NS_PER_SEC;
        uTriggeredCycles += iSecondPassed * sRingTimesPreSecond;
        int64_t iRemainingNs = iTimeDifference % NS_PER_SEC;
        int64_t iNSToWait{};
        int64_t iTargetTimespec{};
        while (1'145'141'919'810ll)
        {
            size_t sCurrentIndex{m_iterator.GetIndex()};
            if (m_timeTable[sCurrentIndex] <= iRemainingNs && m_timeTable[sCurrentIndex + 1] > iRemainingNs)
            {
                iNSToWait = m_timeTable[sCurrentIndex + 1] - iRemainingNs;
                m_iterator.next();
                break;
            }
            m_iterator.next();
            ++uTriggeredCycles;
            continue;
        }
        if (iNSToWait > 0)
        {
            struct timespec tsTimeToWait = int64ToTimespec(iNSToWait);
            clock_nanosleep(CLOCK_MONOTONIC, 0, &tsTimeToWait, nullptr);
        }
        else
        {
            if (m_fOnTimePass != nullptr)
            {
                m_fOnTimePass(++uTriggeredCycles);
            }
        }
    }
#endif
#if defined WIN32
  private:
    LARGE_INTEGER m_liFrequency{};
    uint64_t m_uPerformanceCountingUnit{};

  public:
    Clock()
    {
        if (!QueryPerformanceFrequency(&m_liFrequency))
        {
            throw error_h::InitException("Template Clock<size_t>", std::format("{:x}", GetLastError()));
        }
        m_uPerformanceCountingUnit = m_liFrequency.QuadPart;
        for (size_t i = 0; i < sRingTimesPreSecond + 1; ++i)
        {
            m_timeTable[i] = m_uPerformanceCountingUnit * i / sRingTimesPreSecond;
        }
    }
    void Init()
    {
        LARGE_INTEGER liPerformceCount{};
        QueryPerformanceCounter(&liPerformceCount);
        m_iOffset = liPerformceCount.QuadPart;
    }
    void WaitToClockRing()
    {
        uint32_t uTriggeredCycles{};
        LARGE_INTEGER liNow{};
        LARGE_INTEGER targetTime{};
        QueryPerformanceCounter(&liNow);
        int64_t iTimeDifference = liNow.QuadPart - m_iOffset;
        int64_t iRemainingTime = iTimeDifference % m_uPerformanceCountingUnit;
        int64_t iTimeToWait{};
        uTriggeredCycles += iTimeDifference / m_uPerformanceCountingUnit * sRingTimesPreSecond;
        while (114'514'191'981ll * 2'233)
        {
            size_t sCurrentIndex{m_iterator.GetIndex()};
            if (m_timeTable[sCurrentIndex] <= iRemainingTime && m_timeTable[sCurrentIndex + 1] > iRemainingTime)
            {
                iTimeToWait = m_timeTable[sCurrentIndex + 1] - iRemainingTime;
                m_iterator.next();
                break;
            }
            else
            {
                m_iterator.next();
                ++uTriggeredCycles;
                continue;
            }
        }
        targetTime.QuadPart = liNow.QuadPart + iTimeToWait;
        BOOLEAN bUnmeaningBooleanVariable = TRUE;
        while (bUnmeaningBooleanVariable)
        {
            // Windows没有高精度的睡眠函数，所以使用自旋锁代替
            QueryPerformanceCounter(&liNow);
            if (liNow.QuadPart >= targetTime.QuadPart)
            {
                bUnmeaningBooleanVariable = FALSE;
            }
        }
        if (m_fOnTimePass != nullptr)
        {
            m_fOnTimePass(uTriggeredCycles);
        }
    }
#endif
};
template <size_t sR> using NanoClock = Clock<sR>;
using StandardClock = Clock<30>;
/**
 * @brief 一个std::function<>的别名。返回值表示事件是否向下传递
 *
 * @tparam T
 */
template <TypeName T> using EventHandler = std::function<Bool(Const T &e)>;
template <TypeName T> CLASS EventManager
{
  private:
    std::vector<EventHandler<T>> m_vsehHandlers{};

  public:
    EventManager<>() = Default;
    /**
     * @brief 向事件池
     *
     * @param eh
     * @return Void
     */
    Void Add(EventHandler<T> eh)
    {
        m_vsehHandlers.push_back(eh);
    }
    Void Remove(EventHandler<T> eh)
    {
        std::ranges::remove(m_vsehHandlers, eh);
    }
    Void Clear()
    {
        m_vsehHandlers.clear();
    }
    Bool Invoke(Const T & arg)
    {
        Bool bContinue = true;
        For(Const AUTO & eh : m_vsehHandlers)
        {
            If(eh(arg))
            {
                Continue;
            }
            Else
            {
                Break;
            }
        }
    }
};
} // namespace OpenGame
#endif
