//目标接口（新接口）
class ITarget {
public:
    virtual void process() = 0;
};

//遗留接口（老接口）
class IAdaptee {
public:
    virtual void foo(int data) = 0;

    virtual int bar() = 0;
};

//遗留类
class OldClass : public IAdaptee {
    //....
    virtual void foo(int data) {

    }

    virtual int bar() {
        // ...
        return 0;
    }
};

//对象适配器
class Adapter : public ITarget //继承目标类
{
protected:
    IAdaptee *pAdaptee; //组合遗留不兼容类

public:
    Adapter(IAdaptee *pAdaptee) {
        this->pAdaptee = pAdaptee;
    }

    virtual void process() { //兼容转换代码部分
        int data = pAdaptee->bar();
        pAdaptee->foo(data);
    }
};

int main() {
    IAdaptee *pAdaptee = new OldClass();

    // 给适配器类传入老的接口对象 使用适配器的方法完成老的接口对象的方法
    // 接口转换： 老接口转成新接口
    ITarget *pTarget = new Adapter(pAdaptee);
    pTarget->process();
}

//另一种：类适配器 多继承没有上面的继承+组合方法好
class Adapter : public ITarget,
                protected OldClass {
    //多继承，重载类方法
};


// STL中的stack和queue都是用deque实现的适配器模式 组合(类实现中含有deque类)
class stack {
    deque container;
};

class queue {
    deque container;
};