class MainForm : public Form
{
    TextBox *txtFilePath;
    TextBox *txtFileNumber;
    ProgressBar *progressBar;

public:
    void Button1_Click()
    {

        // 面向接口编程  典型表现就是变量要申明成抽象基类
        // 这里的new的BinarySplitter也违背了依赖倒置原则 也依赖BinarySpitter存在此文件才能编译
        ISplitter *splitter = new BinarySplitter(); //依赖具体类

        splitter->split();
    }
};
