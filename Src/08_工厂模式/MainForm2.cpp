// MainForm2本身不依赖于具体类了 我们把它对具体类的依赖给提出去了 是的其本身不依赖于具体类了
class MainForm : public Form
{
    // 这里是抽象基类 不依赖具体类
    SplitterFactory *factory; //工厂

public:
    MainForm(SplitterFactory *factory)
    {
        this->factory = factory;
    }

    void Button1_Click()
    {
        // 这里是抽象基类 不依赖具体类
        ISplitter *splitter = factory->CreateSplitter(); //多态new

        splitter->split();
    }
};
