#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "C++ vector demo" << endl;

    // 1.创建vector
    vector<int>  vec1;
    vector<int>  vec2(5);
    vector<int>  vec3(5,10);
    vector<int>  vec4 = {1, 2, 3, 4, 5};
    vector<int>  vec5(vec4);
 
    //2.访问vector中的元素
    // 以vec4为例子
    for(auto i : vec4){
        cout << i << endl;
    }
    cout << vec4[0] << vec4[1] <<endl;
    cout << vec4.at(0) << vec4.at(4) << endl;
    cout << vec4.front() << "and " << vec4.back() << endl;
    cout << vec4.data() << endl;
    int* p = vec4.data();
    cout << p << "esfhui   " << *p << "   eihfio  " <<  &p << endl;

    //3.容量操作
    if(vec1.empty()){
        cout << "empty" << endl;
    } else {
        cout << "not empty" << endl;
    }

    cout << vec4.size() << endl;

    cout << vec1.capacity() << "uawgrdwi" << vec3.capacity() << "iwugfuyi" << vec4.capacity()<< "easfuh" << endl;
    
    vec3.clear();
    for(auto i : vec3){
         cout <<  i << "afughiq" << endl;
    }



    return 0;


}