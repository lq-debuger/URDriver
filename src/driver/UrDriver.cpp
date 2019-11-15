

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

    //socket连接后返回数据时的信号和槽函数
    connect(&socket,&QTcpSocket::readyRead,[this]{
        QByteArray data = socket.readAll();
        //解析数据
        URData urData;
        parseData(data, urData);
        //判断是否要执行，从队列中获取第一个执行命令
        decideExcuteInstruction(urData);
    });
}

/**
 * 解析socket收到的数据，并复制给URData
 * @param data socket返回的数据
 * @param urData URdata 结构体
 */
void UrDriver::parseData(QByteArray array, URData &urData) {
    //定义char 数据接受array中的数据
    char rawData[1108];
    QByteArray temp;
    for (auto i = array.end() - 1108; i < array.end(); i ++){
        temp.push_back(*i);
    }
//    cout << temp.size() << endl;
    memcpy(rawData, temp.data(), temp.size());
    //先接收前四个字节，对应结构体urdata中的第一个数据，注意结构的内存对齐
    char *p = rawData;
    //rawdata中数据的存储时大端存储，而结构体中的数据时小端存储
    //把前四个字节的数据转换成小端
    reverseData(p, 4);
//    cout << p <<endl;
    //把前四个字节的数据复制给urData结构体的第一个数据类型中
    memcpy(&urData, p, 4);
    //检测一下是否解析正确
//    cout << urData.MsgSize << endl;
//    reverseData(p+4,8);
//    cout << *(double *)(p+4) << endl;

    //后边的数据都是double数据，8个字节，根据结构体的内存对齐，应从结构体的第八个数据开始
    for (char *q = p + 4; q < p + sizeof(rawData) - 8; q += 8) {
        //进行大小端转换
        reverseData(q, 8);
    }


    //将后边的数据整体复制给urData结构体
    memcpy((char *) (&urData) + 8, p + 4, temp.size() - 4);

}

/**
 * moveL
 * @param joints
 * @param acc
 * @param vel
 */
void UrDriver::moveL(double *pose, double acc, double vel) {
//    //替换脚本
//    scripts.moveL(pose, acc, vel);
//    //发送数据
//    sendscript();

    //添加指令
    addInstruction(MOVEL, pose, acc, vel);
}

/**
 * moveJ
 * @param pose
 * @param acc
 * @param vel
 */
void UrDriver::moveJ(double *pose, double acc, double vel) {
//    //替换脚本
//    scripts.moveJ(pose, acc, vel);
//    //发送数据
//    sendscript();

    //添加指令
    addInstruction(MOVEJ, pose, acc, vel);
}

/**
 * 加载脚本
 * @param path
 */
void UrDriver::loadScripts(string path) {
    scripts.loadScripts(path);
}

/**
 * 发送脚本数据
 */
void UrDriver::sendscript() {
    //获取脚本内容
    QString src = scripts.getCommandScript();
    qDebug()<< src << endl;
    //发送数据据
    socket.write(src.toUtf8());
}

/**
 * 给指令队列中添加指令
 * @param type
 * @param data
 * @param acc
 * @param vel
 */
void UrDriver::addInstruction(moveType type, double data[6], double acc, double vel) {

    Instruction instruction;
    instruction.type = type;
    memcpy(instruction.data, data, 48);
    instruction.acc = acc;
    instruction.vel = vel;
    instruction_queue.push(instruction);
}

/**
 * 判断是否执行队列中的命令
 * @param urData
 */
void UrDriver::decideExcuteInstruction(URData urData) {
//    cout << instruction_queue.size() << endl;
    //判断队列是否为空
    if (instruction_queue.size() == 0) {
        return;
    }

    //判断是否时第一次执行指令
    if (isFirst) {
        Instruction instruction = instruction_queue.front();
        //执行指令
        excuteInstruction(instruction);
        //让执行的指令出队
        instruction_queue.pop();
        return;
    }

//    cout << "是否完成" << hasCompleteLastInstruction(targetInstruction,urData) <<endl;
    //判断上一个指令是否执行完成
    if (hasCompleteLastInstruction(targetInstruction, urData)) {
        Instruction instruction = instruction_queue.front();
        //执行指令
        excuteInstruction(instruction);
        //让执行的指令出队
        instruction_queue.pop();
    }
}

/**
 * 执行指令
 * @param instruction
 */
void UrDriver::excuteInstruction(Instruction instruction) {
    moveType type = instruction.type;
    if (type == MOVEJ) {
        scripts.moveJ(instruction.data, instruction.acc, instruction.vel);
    } else if (type == MOVEL) {
        scripts.moveL(instruction.data, instruction.acc, instruction.vel);
    }
    //修改目标指令
    modifyTargetInstruction(instruction);
    //修改isfirst
    isFirst = false;
    //发送数据
    sendscript();
}

/**
 * 修改目标指令
 * @param instruction
 */
void UrDriver::modifyTargetInstruction(Instruction instruction) {
    targetInstruction.type = instruction.type;
    memcpy(targetInstruction.data, instruction.data, 48);
    targetInstruction.vel = instruction.vel;
    targetInstruction.acc = instruction.acc;
}


