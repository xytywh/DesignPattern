// C++不推荐多继承  不过推荐另外一种 即只有一个类 其他都是抽象基类
class MainForm : public Form, public IProgress {
    TextBox *txtFilePath;
    TextBox *txtFileNumber;
    ProgressBar *progressBar;

public:
    void Button1_Click() {

        string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        // 第三个参数传递this指针可以的，因为当前函数继承了IProgress父类
        FileSplitter splitter(filePath, number, this);

        splitter.split();
    }
    virtual void DoProgress(float value) {
        progressBar->SetValue(value);
    }
};
