#include <iostream>
#include <string>

class person {
public:
  std::string name = "jmh" ;
  int age = 20;
};

int main() 
{
    //1.表达式必须是可修改的左值
   const int max_speed = 120;
    //max_speed = 150;         会报错

    //2.修饰指针
    // (1)  const在 * 前面         保护对象中的内容
    // 禁忌：不能修改p1的成员变量
    // 灵活：可与修改p1指针的指向
    const person* p1 = new person();

    // (2)  const在 * 后面         保护指针变量存储的地址
    // 禁忌：p2不能再指向别处，只能存这一个地址
    // 灵活：可以修改p2指向的对象的内容
    person* const p2 = new person();
    
    std::cout << "p1  " << p1->name << "and" << p1->age << std::endl;
    std::cout << "p2  " << p2->name << "and" << p2->age << std::endl;

    // 尝试修改对象内容   
    // p1->age = 100;   报错：左值应该是可修改的
    p2->age = 100;
    std::cout << "修改对象内容" << std::endl;
    std::cout << "p1  " << p1->name << "and" << p1->age << std::endl;
    std::cout << "p2  " << p2->name << "and" << p2->age << std::endl;
    

    //尝试切换指针
    person* p3 = new person();
    p3->age = 10;

    p1 = p3;
    // p2 = p3;   报错：左值应该是可修改的    
    std::cout << "尝试切换指针" << std::endl;
    std::cout << "p1  " << p1->name << "and" << p1->age << std::endl;
    std::cout << "p2  " << p2->name << "and" << p2->age << std::endl;
 
    return 0;
}