class MainForm : public Form
{
    ISplitter *prototype; //原型对象  这个不能直接使用  只能用来克隆新的对象  类似于之前的工厂

public:
    MainForm(ISplitter *prototype)
    {
        this->prototype = prototype;
    }

    void Button1_Click()
    {
        ISplitter *splitter = prototype->clone(); //克隆原型

        splitter->split();
    }
};
