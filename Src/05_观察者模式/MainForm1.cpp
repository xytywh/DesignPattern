class MainForm : public Form
{
    TextBox *txtFilePath;
    TextBox *txtFileNumber;
    // 违反了依赖控制原则  这个可能是一直在变化  所以考虑怎么重构能够不违法那几个原则
    ProgressBar *progressBar;

public:
    void Button1_Click()
    {

        string filePath = txtFilePath->getText();
        int number = atoi(txtFileNumber->getText().c_str());

        FileSplitter splitter(filePath, number, progressBar);

        splitter.split();
    }
};
