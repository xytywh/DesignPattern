class MainForm : public Form, public IProgress
{
    TextBox *txtFilePath;
    TextBox *txtFileNumber;

    // 这里progressBar是MainForm类中的一个成员  MainForm继承了IProgress
    // 下面的ConsoleNotifier本身就继承了IProgress
    // 所以下面添加的时候一个添加this 一个添加&cn
    ProgressBar *progressBar;

public:
    void Button1_Click()
    {

        string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        ConsoleNotifier cn;

        FileSplitter splitter(filePath, number);

        splitter.addIProgress(this); //添加IProgress的子类对象 订阅通知
        splitter.addIProgress(&cn);  //添加IProgress的子类对象 订阅通知

        splitter.split();

        splitter.removeIProgress(this);
    }

    virtual void DoProgress(float value)
    {
        progressBar->setValue(value);
    }
};

class ConsoleNotifier : public IProgress
{
public:
    virtual void DoProgress(float value)
    {
        std::cout << ".";
    }
};
