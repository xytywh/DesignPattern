class Library
{
public:
    //稳定 template method
    void Run()
    {

        Step1();

        if (Step2()) //֧支持变化-->虚函数的多态调用
        {
            Step3();
        }

        for (int i = 0; i < 4; i++)
        {
            Step4(); //֧支持变化-->虚函数的多态调用
        }

        Step5();
    }
    virtual ~Library() {} //基类虚构函数要virtual

protected:

    // 稳定的写成非虚方法
    void Step1()
    { //稳定
        //.....
    }
    void Step3()
    { //稳定
        //.....
    }
    void Step5()
    { //稳定
        //.....
    }

    // 变化的写成虚函数
    virtual bool Step2() = 0; //变化，交给子类实现
    virtual void Step4() = 0; //变化，交给子类实现
};