

#ifndef URDRIVERCPP_URDRIVER_H
#define URDRIVERCPP_URDRIVER_H

#include <iostream>
#include <memory>
using namespace std;
class UrDriver {

    static shared_ptr<UrDriver> instance;
public:
    //饿汉单例模式
    static shared_ptr<UrDriver> getInstance();

    UrDriver();

    ~UrDriver();

    //连接机械臂
    void connectTORobot();
};



#endif //URDRIVERCPP_URDRIVER_H
