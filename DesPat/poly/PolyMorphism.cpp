#include <iostream>

//定义一个抽象基类
class Payment
{
public:
    virtual void processPayment(double amount) = 0;
    virtual ~Payment() {};
};

//实现支付宝子类  AliPay
class AliPay : public Payment
{
public:
     void processPayment(double amount) override {
        std::cout << "This is AliPay" << std::endl;
     };
};



//实现微信支付子类  WeChatPay
class WeChatPay : public Payment
{
public:
     void processPayment(double amount) override {
        std::cout << "This is WeChatPay" << std::endl;
     };
};


//实现高层管理类  PaymentManager
class PaymentManager
{

};


int main()
{
    AliPay* ali1 = new AliPay();
    WeChatPay* wch1 = new WeChatPay();
    ali1->processPayment(33.3);
    wch1->processPayment(66.66);
    return 1;
}