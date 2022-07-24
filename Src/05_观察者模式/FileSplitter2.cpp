class IProgress {
public:
    virtual void DoProgress(float value) = 0;

    virtual ~IProgress();
};

class FileSplitter {
    string m_filePath;
    int m_fileNumber;
    // ProgressBar *m_progressBar; // 通知 我们不使用一个具体的控件  使用一种非常抽象的方式
    IProgress *m_iprogress; // 抽象的通知机制  这里只支持一个观察者
public:
    FileSplitter(const string &filePath, int fileNumber, IProgress *iprogress) :
            m_filePath(filePath),
            m_fileNumber(fileNumber),
            m_iprogress(iprogress) {
    }

    void split() {

        //1.读取大文件

        //2.分批次向小文件写入
        for (int i = 0; i < m_fileNumber; i++) {
            //...
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            onProgress(progressValue);

        }
    }

protected:
    void onProgress(float value) {
        if (m_iprogress != nullptr) {
            // 这里就调用到了MainForm中实现的DoProgress方法
            m_iprogress->DoProgress(value); // 更新进度条
        }
    }

};