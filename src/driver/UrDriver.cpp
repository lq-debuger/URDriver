

#include "UrDriver.h"

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::instance = shared_ptr<UrDriver>(new UrDriver);

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::getInstance() {
    return instance;
}

UrDriver::UrDriver() {
    cout << "创建内存" << endl;
}

UrDriver::~UrDriver() {
    cout << "释放内存" << endl;
}

/*
 * 连接机械臂
 * */
void UrDriver::connectTORobot() {
    cout << "连接成功" << endl;

}
