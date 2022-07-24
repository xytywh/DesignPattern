class Context;

class TaxStrategy
{
public:
    virtual double Calculate(const Context &context) = 0;
    virtual ~TaxStrategy() {}
};

class CNTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //***********
    }
};

class USTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //***********
    }
};

class DETax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //***********
    }
};

//扩展  遵循了开闭原则 这里是一个新的类  一般按照C++的编码规范 我们写到一个新的文件中  比如编译器支持增量编译  增量部署之类的
// 就会比strategy1写法节省很多时间
//*********************************
class FRTax : public TaxStrategy
{
public:
    virtual double Calculate(const Context &context)
    {
        //.........
    }
};

class SalesOrder
{
private:
    TaxStrategy *strategy;//基类指针，用于多态调用

public:
    // 这里是一个工厂模式  可以返回不同的之类指针
    SalesOrder(StrategyFactory *strategyFactory)
    {//赋值具体的子类对象
        this->strategy = strategyFactory->NewStrategy();
    }
    ~SalesOrder()
    {
        delete this->strategy;
    }

public:
    double CalculateTax()
    {
        //...
        Context context();

        double val = strategy->Calculate(context); //多态调用
        //...
    }
};
