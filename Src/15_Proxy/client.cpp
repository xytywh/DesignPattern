class ISubject {
public:
    virtual void process();
};

class RealSubject : public ISubject {
public:
    virtual void process() {
        // ....
    }
};

class ClientApp {
private:
    ISubject *subject;

public:
    ClientApp() {
        // 这里表示的含义并不一定代表new一个RealSubject对象  而是指通过某种方法返回一个RealSubject对象
        // 但是存在这么一种情况 比如分布式或者安全控制的原因 我们 不能直接得到这个RealSubject对象
        subject = new RealSubject();
    }

    void DoTask() {
        // ...
        subject->process();
        // ....
    }
};