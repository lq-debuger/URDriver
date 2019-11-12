

#include "UrDriver.h"

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::instance = shared_ptr<UrDriver>(new UrDriver);

//使用只能指针释放内存
shared_ptr<UrDriver> UrDriver::getInstance() {
    return instance;
}

UrDriver::UrDriver() {
    //处理信号和槽
    signalAndSlot();
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

/**
 * 接受连接的回调函数
 * @param connectCallback
 */
void UrDriver::setConnectCallback(function<void()> connectCallback) {
    this->connectCallback = connectCallback;
}

/**
 * 断开连接
 */
void UrDriver::disConnectToRobot() {
    socket.close();
}

/**
 * 接受断开连接的回调函数
 * @param disConnectCallback
 */
void UrDriver::setDisconnectCallback(function<void()> disConnectCallback) {
    this->disConnectCallback = disConnectCallback;
}

/**
 * 处理连接和断开连接的信号和槽
 */
void UrDriver::signalAndSlot() {
    //连接成功的信号和槽函数
    connect(&socket, &QTcpSocket::connected, [this] {
        //调用回调函数
        connectCallback();
    });

    //断开连接的信号和槽函数
    connect(&socket,&QTcpSocket::disconnected,[this]{
        disConnectCallback();
    });
}


