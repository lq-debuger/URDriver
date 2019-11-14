

#ifndef URDRIVERCPP_URDRIVER_H
#define URDRIVERCPP_URDRIVER_H

#include <iostream>
#include <memory>
#include <QTcpSocket>
#include <QString>
#include <functional>
#include "URScripts.h"
#include <memory>
#include "utils.h"
#include <queue>
using namespace std;
class UrDriver: public QObject {
private:
    //指令的队列
    queue<Instruction> instruction_queue;
    //目标指令
    Instruction targetInstruction;
    URScripts scripts;
    //是否第一次执行
    bool isFirst = true;
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

    //加载脚本
    void loadScripts(string path);

    //moveL
    void moveL(double *pose, double acc = 1.2, double vel = 0.25);

    //moveJ
    void moveJ(double *pose, double acc = 1.4, double vel = 1.05);

    //发送脚本数据
    void sendscript();

    //解析数据
    void parseData(QByteArray array,URData urData);

    //给队列中添加指令
    void addInstruction(moveType type, double data[6], double acc, double vel);

    //决定是否执行队列中的命令
    void decideExcuteInstruction(URData urData);

    //执行指令
    void excuteInstruction(Instruction instruction);

    //修改目标指令
    void modifyTargetInstruction(Instruction instruction);
};



#endif //URDRIVERCPP_URDRIVER_H
