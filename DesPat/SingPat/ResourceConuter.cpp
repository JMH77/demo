#include <iostream>

//饿汉类
class EagerCounter {
public:
    //禁用拷贝构造以及拷贝赋值
    EagerCounter(const EagerCounter &e) = delete;
    EagerCounter& operator = (const EagerCounter &e) =delete;
    //饿汉实例获取接口
    static EagerCounter* getInstance() {
        return m_eager;
    }

    //打印当前实例所在地址
    void printAdr() {
        std::cout << "饿汉地址: " << this << std::endl;
    }

private:
    EagerCounter() {
        std::cout << "此处调用饿汉模式构造函数"  << std::endl;
    }
    static EagerCounter* m_eager;
    static int count;
};
EagerCounter* EagerCounter::m_eager = new EagerCounter();


//懒汉类
class LazyCounter {
public:
    LazyCounter(const LazyCounter &l) = delete;
    LazyCounter& operator = (const LazyCounter &l) =delete;
    //懒汉实例获取接口
    static LazyCounter* getInstance() {
        if(m_lazyer == nullptr){
            m_lazyer = new LazyCounter;
        }
        return m_lazyer;
    }

    //打印当前实例所在地址
    void printAdr() {
        std::cout << "懒汉地址: " << this << std::endl;
    }

private:
    LazyCounter() {
        std::cout << "此处调用懒汉模式构造函数"  << std::endl;
    }
    static LazyCounter* m_lazyer;
    static int count;
};
LazyCounter* LazyCounter::m_lazyer = nullptr;



int main() {

    EagerCounter* eager1 = EagerCounter::getInstance();
    LazyCounter* lazyer1 = LazyCounter::getInstance();
    eager1->printAdr();
    lazyer1->printAdr();
    EagerCounter* eager2 = eager1->getInstance();
    LazyCounter* lazyer2 = lazyer1->getInstance();
    std::cout << "赋值之后的地址: " << std::endl;
    eager2->printAdr();
    lazyer2->printAdr();
    
    return 1;
}