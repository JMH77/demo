#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "C++ Vector 使用示例：" << endl;
    
    // 1. 创建vector的不同方式
    vector<int> vec1;                    // 创建空的int类型vector
    vector<int> vec2(5);                 // 创建包含5个元素的vector，初始值为0
    vector<int> vec3(5, 10);            // 创建包含5个值为10的元素的vector
    vector<int> vec4 = {1, 2, 3, 4, 5}; // 使用初始化列表创建vector
    
    cout << "vec2的初始内容: ";
    for(int i = 0; i < vec2.size(); i++) {
        cout << vec2[i] << " ";
    }
    cout << endl;
    
    cout << "vec3的初始内容: ";
    for(auto it = vec3.begin(); it != vec3.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "vec4的初始内容: ";
    for(int val : vec4) {  // 范围for循环(C++11)
        cout << val << " ";
    }
    cout << endl;
    
    // 2. 向vector添加元素
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    
    cout << "\n添加元素后的vec1: ";
    for(int val : vec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // 3. 访问vector元素
    cout << "\nvec1的第一个元素: " << vec1.front() << endl;
    cout << "vec1的最后一个元素: " << vec1.back() << endl;
    cout << "vec1的第二个元素(索引1): " << vec1[1] << endl;
    cout << "vec1的第二个元素(使用at): " << vec1.at(1) << endl;
    
    // 4. 修改vector元素
    vec1[1] = 25;
    cout << "\n修改第二个元素后vec1: ";
    for(int val : vec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // 5. vector大小相关操作
    cout << "\nvec1的大小: " << vec1.size() << endl;
    cout << "vec1的容量: " << vec1.capacity() << endl;
    cout << "vec1是否为空: " << (vec1.empty() ? "是" : "否") << endl;
    
    // 6. 删除元素
    vec1.pop_back();  // 删除最后一个元素
    cout << "\n删除最后一个元素后vec1: ";
    for(int val : vec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // 7. 插入元素
    vec1.insert(vec1.begin() + 1, 15);  // 在索引1的位置插入15
    cout << "\n在索引1位置插入15后vec1: ";
    for(int val : vec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // 8. 删除指定位置元素
    vec1.erase(vec1.begin() + 1);  // 删除索引为1的元素
    cout << "\n删除索引1位置元素后vec1: ";
    for(int val : vec1) {
        cout << val << " ";
    }
    cout << endl;
    
    // 9. 清空vector
    vec1.clear();
    cout << "\n清空vec1后大小: " << vec1.size() << endl;
    cout << "清空vec1后是否为空: " << (vec1.empty() ? "是" : "否") << endl;
    
    // 10. 二维vector示例
    cout << "\n二维vector示例:" << endl;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}