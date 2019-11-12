

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
    //断开连接的回调函数
    function<void()> disConnectCallback;
    QTcpSocket socket;
    static shared_ptr<UrDriver> instance;
public:
    //饿汉单例模式
    static shared_ptr<UrDriver> getInstance();

    UrDriver();

    ~UrDriver();

    //处理连接和断开连接的信号和槽
    void signalAndSlot();

    //连接机械臂
    void connectTORobot(QString ip,int port);

    //断开连接
    void disConnectToRobot();

    //接收连接的回调函数
    void setConnectCallback(function<void()> connectCallback);

    //接受断开连接的回调函数
    void setDisconnectCallback(function<void()> disConnectCallback);


};



#endif //URDRIVERCPP_URDRIVER_H
