#include <iostream>

class TaskQueue
{
public:
//TaskQueue()  = delete;   //由于同名函数的原因所以必须在这里注释掉，才能在下面private中实现
  TaskQueue(const TaskQueue & t) = delete;
  TaskQueue& operator = (const TaskQueue& t) = delete;
//获取一个TaskQueue的getInstance静态方法
  static TaskQueue* getInstance(){
        if (m_taskQ == nullptr) {
        m_taskQ = new TaskQueue(); // 必须有私有构造，这行才生效
    }
    return m_taskQ;
  }

  void printAddress(){
    std::cout << "Address:  " << this << std::endl;
  }

private:
//下面这两行也是禁止外部使用构造函数
//   TaskQueue() = default;
//   TaskQueue(const TaskQueue & t) = default;
//   TaskQueue& operator = (const TaskQueue& t) = default;
//只能通过类名访问静态属性或者方法
//先定义一个私有构造函数
    TaskQueue() {
        std::cout << "私有构造函数被调用，创建唯一实例" << std::endl;
    }
     static TaskQueue* m_taskQ; 
};

// 关键：类外初始化静态指针为nullptr（必须加！）
TaskQueue* TaskQueue::m_taskQ = nullptr;

int main ()
{
    TaskQueue* taskq = TaskQueue::getInstance();
    taskq->printAddress();
    return 1;
}