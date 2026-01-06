#include <iostream>

// 先写一个部门类
class Department {
public:
    explicit Department(int capacity) {        //capacity是部门人数
     this->capacity = capacity;
     this->employees = "aabb";
     std::cout << "创建了一个拥有 " << capacity << " 个工位的部门" << std::endl;
    }

    int capacity;
    std::string employees;
};

void printDepartmentInfo(const Department& p) {
    std::cout << "show us Info " 
              << p.capacity 
              << " and " 
              << p.employees 
              << std::endl;
}


int main()
{
    // printDepartmentInfo(999);      //此处你要是不防隐式转换 这个地方传入999999也能跑，
                                     // 因为编译器会玩匹配游戏
                                    //  编译器会将999传给此处理想的那个  Department参数  的构造函数
                                    // 然后构造出一个有999甚至999999个员工的部门，可能造成崩溃。
    

    // printDepartmentInfo(999);        会报错，说不存在从 int  转换为 Departme 的构造函数

    Department p(7);
    printDepartmentInfo(p);
    
    return 0;
}