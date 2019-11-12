

#ifndef URDRIVERCPP_URDRIVER_H
#define URDRIVERCPP_URDRIVER_H

#include <iostream>
#include <memory>
#include <QTcpSocket>
#include <QString>
#include <functional>
using namespace std;
class UrDriver: public QObject {
private:
    //连接成功的回调函数
    function<void()> connectCallback;
    QTcpSocket socket;
    static shared_ptr<UrDriver> instance;
public:
    //饿汉单例模式
    static shared_ptr<UrDriver> getInstance();

    UrDriver();

    ~UrDriver();

    //连接机械臂
    void connectTORobot(QString ip,int port);

    //接收连接的回调函数
    void setConnectCallback(function<void()> connectCallback);


};



#endif //URDRIVERCPP_URDRIVER_H
