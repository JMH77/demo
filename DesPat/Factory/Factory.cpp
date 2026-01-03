#include <iostream>
#include <QPushButton>

//工厂抽象基类
class Factory {
public:
   virtual Button* createButton() = 0;
};

//具体的工厂实现 --Windows
class WindowsFactory : public Factory {
public:
   virtual Button* createButton() override {
    return new WindowsButton()
   }
};

// -Mac- 工厂
class MacFatory : public Factory {
public:
   virtual Button* createButton() override {
    return new MacButton();
   }
};


//产品抽象基类
class Button {
public:
   virtual ~Button {}
   virtual void render() = 0 
};

//具体产品 -Windows-
class WindowsButton : public Button{
public:
   void render() override {
    std::cout << "绘制Windows风格的按钮"  << std::endl;
   }
};

//具体产品 -Mac-
class MacButton : public Button{
public:
   void render() override {
    std::cout << "绘制Mac风格的按钮"  << std::endl;
   }
};