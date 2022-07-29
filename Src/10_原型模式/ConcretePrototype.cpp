// 具体类
// 和工厂模式的不同之处在于省去了用于生成各种不同对象的继承了工厂基类的具体工厂类（这个生成对象的工作在自己的类对象加了一个clone函数完成了）
// 成员函数clone完成了生成自己的任务
class BinarySplitter : public ISplitter {
public:
    virtual ISplitter *clone() {
        return new BinarySplitter(*this); // 需要拷贝构造函数正确实现
    }
};

class TxtSplitter : public ISplitter {
public:
    virtual ISplitter *clone() {
        return new TxtSplitter(*this);
    }
};

class PictureSplitter : public ISplitter {
public:
    virtual ISplitter *clone() {
        return new PictureSplitter(*this);
    }
};

class VideoSplitter : public ISplitter {
public:
    virtual ISplitter *clone() {
        return new VideoSplitter(*this);
    }
};
