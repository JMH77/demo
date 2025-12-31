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

    //销毁函数
    static void destroy() {
    delete m_eager;
    m_eager = nullptr;
    }

private:
    EagerCounter() {
        std::cout << "此处调用饿汉模式构造函数"  << std::endl;
    }
    ~EagerCounter() {
        std::cout << "此处调用饿汉模式析构函数"  << std::endl;
    }
    static EagerCounter* m_eager;
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
    
    //销毁函数
    static void destroy() {
    delete m_lazyer;
    m_lazyer = nullptr;
    }

private:
    LazyCounter() {
        std::cout << "此处调用懒汉模式构造函数"  << std::endl;
    }
    ~LazyCounter() {
        std::cout << "此处调用懒汉模式析构函数"  << std::endl;
    }
    static LazyCounter* m_lazyer;
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
    eager1->destroy();
    lazyer1->destroy();
    //下面这几个eager 和 lazyer其实都是野指针，因为当前还没有手动删除
    eager1->printAdr();
    lazyer1->printAdr();
    eager2->printAdr();
    lazyer2->printAdr();
    return 1;
}



//如果你现在就在面试现场，面试官指着你刚才写的代码问：

// “同学，你这个 LazyCounter 用了 new。如果我希望在程序退出时看到析构函数执行，但在 main 函数里我不想看到任何 delete 语句，你有什么简单的办法？”

// 方案 A：配合“内部静态实例”（最简单的满分答案）
// 这就是我们之前说的 Meyers 单例。

// static LazyCounter& getInstance() {
//     static LazyCounter instance; // 局部静态变量
//     return instance;
// }

// 方案 B：配合“自杀”接口
// 如果你坚持使用 new，你需要在 private 析构的同时，提供一个 public 的接口来处理销毁：

// class LazyCounter {
// private:
//     ~LazyCounter() { /* 真正收尾 */ }
// public:
//     static void destroy() {
//         delete m_instance; // 类内部可以访问私有析构
//     }
// };


// 经过一番深刻的讨论与思考，我发现：

// 我在类内部从创建的是个指针，然后外部实例化的时候也是先传递给这个静态成员指针。
// 然后后面调用实例的时候其实是将静态成员指针传递给其他的类指针，帮你如说这个eager1，
// 也就是说eager1并不是全局最早拿到实例地址的指针，只能说是外部第一个拿到实例的指针

// 并且为了避免外部访问这个静态成员空指针崩溃，
// 也为了避免外部修改所以直接这个静态成员指针就是一个私有变量