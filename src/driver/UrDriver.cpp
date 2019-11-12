

#include "UrDriver.h"

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::instance = shared_ptr<UrDriver>(new UrDriver);

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::getInstance() {
    return instance;
}

UrDriver::UrDriver() {
    connect(&socket, &QTcpSocket::connected, [this] {
        //调用回调函数
        connectCallback();
    }
    );
}

UrDriver::~UrDriver() {
    cout << "释放内存" << endl;
}

/*
 * 连接机械臂
 * */
void UrDriver::connectTORobot(QString ip,int port) {
//    cout << "连接成功" << endl;
    socket.connectToHost(ip, port);
}

/*
 * 接收连接的回调函数
 * */
void UrDriver::setConnectCallback(function<void()> connectCallback) {
    this->connectCallback = connectCallback;
}


