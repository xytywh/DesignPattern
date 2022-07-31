class Singleton {
private:
    // 构造函数和拷贝构造函数私有，或C++11 =delete  外部不能使用  只有内部能使用
    // 构造函数申明成私有 外部不能调用它生成对象  只能通过getInstance函数生成对象 而getInstance函数保证了只系统中只生成一个对象
    Singleton();

    Singleton(const Singleton &other);

    static Singleton *m_instance;

public:
    static Singleton *getInstance();
};

Singleton *Singleton::m_instance = nullptr;

// 线程非安全版本 单线程用确实已经足够了 但是如果是多线程其实不能保证只创建一个对象  所以是线程非安全
Singleton *Singleton::getInstance() {
    if (m_instance == nullptr) {
        // 假如是在多线程的环境下  thread1到达这里 准备创建对象  然后时间片给了thread2  他的条件m_instance也会是nullptr
        // 所以两个线程就各自都创建了一个对象 不满足单例模式
        m_instance = new Singleton();
    }
    return m_instance;
}

// 线程安全版本，但读操作太多，锁的代价过高
// 比如对象已经创建成功了   现有两个线程  第一个线程先执行  第二个线程再执行 但是会等待线程1执行完释放锁  但是其实此时其实不需要加锁
// 因为这两个线程都只需要读这个对象 而不需要写 等待锁也是要时间的 如果是高并发场景  效率就不好
Singleton *Singleton::getInstance() {
    // lock加锁
    if (m_instance == nullptr) {
        m_instance = new Singleton();
    }
    // unlock解锁
    return m_instance;
}

// 双检查锁，但由于编译乱序会导致双检查锁失效
Singleton *Singleton::getInstance() {
    if (m_instance == nullptr) {
        // 这里比上面的加锁方式效率高的原因是我们先判断是否为空 再去加锁 只有在最开始对象还没有创建的时候m_instance为空
        // 只要有一个线程创建出来一个m_instance对象 后面的就都很快的直接返回这个对象就行了 可能出现的问题编译乱序也就是在最开始创建对象的时候

        // lock加锁

        // 加锁之后还需要进行一下m_instance是否为空的判断
        // 不然的话考虑这么一个场景 如果两个线程都跑过了41行到达了45行 哪怕有加锁 后一个执行的线程要等待前一个线程执行完  但是因为后一个线程
        // 不会再进行一次是否为空的判断  所以另外一个线程也还会再创建一个对象 不符合单例模式
        // 当然了 锁前肯定要进行一个判空  不然效率低 上面已经说过了

        if (m_instance == nullptr) {

            // 编译乱序出现的问题就是对于下面这一句
            // 顺序1：首先分配一块内存  然后调用构造函数创建类对象 最后将这个内存的首地址给m_instance 这种顺序的话没问题
            // 顺序2：首先分配一块内存  然后将这个内存的首地址给m_instance 最后调用构造函数创建类对象  这种顺序的话就有问题了
            // 对于顺序2 加入执行到了m_instance获得了首地址(m_instance不为空了， 但是还没有调用构造函数实际创建类对象，另外一个线程执行
            // 那么认为m_instance不为空 直接返回这个对象去使用 可以用吗？(虽然不为空 但是也不能用  因为只是分配了内存 但是内存中的东西还需要调用
            // 构造函数去得到 但是还没有调用构造函数  所有可能会出错)

            m_instance = new Singleton();
        }
        // unlock解锁
    }
    return m_instance;
}

// C++ 11版本之后的跨平台实现，内存栅栏
std::atomic<Singleton *> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton *Singleton::getInstance() {
    Singleton *tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire); // 获取内存fence
    if (tmp == nullptr) {
        std::lock_guard <std::mutex> lock(m_mutex); // 加锁，lock_guard会自动解锁
        tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Singleton;
            std::atomic_thread_fence(std::memory_order_release); // 释放内存fence
            m_instance.store(tmp, std::memory_order_relaxed);    // 保存到m_instance中
        }
    }
    return tmp;
}
