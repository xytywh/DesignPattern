enum TaxBase
{
    CN_Tax,
    US_Tax,
    DE_Tax,
    FR_Tax //更改
};

class SalesOrder
{
    TaxBase tax;

public:
    double CalculateTax()
    {
        //...
        // 很多的if else往往就是可以使用策略模式的信号 除非所有的可能性都确定了 不会变化了  例如根据星期几进行判断执行不同的逻辑
        if (tax == CN_Tax)
        {
            //CN***********
        }
        else if (tax == US_Tax)
        {
            //US***********
        }
        else if (tax == DE_Tax)
        {
            //DE***********
        }
        // 上面的代码虽说没有改动 但是不能叫复用 在面向对象或者是设计模式领域说的复用指的是编译单位的复用 二进制层面的复用
        // 拷贝一段代码不叫复用  编译部署之后不用再动了才叫复用
        // 违法开闭原则  （对扩展开放 对更改封闭）  最好不要是直接修改源代码的方式来应对未来的变化
        else if (tax == FR_Tax)
        {   //更改
            //...
        }

        //....
    }
};
