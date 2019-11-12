
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent):QWidget(parent){
    initUI();

    //处理信号和槽
    this->signalAndSlot();

    //处理回调函数
    this->setCallback();
}

/*
 * 初始化界面
 * */
void MainWindow::initUI() {//初始化界面
    layout1 = new QFormLayout();
    setLayout(layout1);

    ipedit = new QLineEdit("127.0.0.1");
    portedit = new QLineEdit("30003");
    connectStatus = new QLabel("未连接");
    connectBtn = new QPushButton("连接机械臂");
    disconnectBtn = new QPushButton("断开连接");
    layout1->addRow("ip", ipedit);
    layout1->addRow("port", portedit);
    layout1->addRow("连接状态 ", connectStatus);
    layout1->addRow(connectBtn);
    layout1->addRow(disconnectBtn);

    joint1 = new QLineEdit();
    joint2 = new QLineEdit();
    joint3 = new QLineEdit();
    joint4 = new QLineEdit();
    joint5 = new QLineEdit();
    joint6 = new QLineEdit();
    movejBtn = new QPushButton("moveJ");
    layout1->addRow("关节1：", joint1);
    layout1->addRow("关节2：", joint2);
    layout1->addRow("关节3：", joint3);
    layout1->addRow("关节4：", joint4);
    layout1->addRow("关节5：", joint5);
    layout1->addRow("关节6：", joint6);
    layout1->addRow(movejBtn);

    xedit = new QLineEdit();
    yedit = new QLineEdit();
    zedit = new QLineEdit();
    rxedit = new QLineEdit();
    ryedit = new QLineEdit();
    rzedit = new QLineEdit();
    movelBtn = new QPushButton("moveL");
    layout1->addRow("x:", xedit);
    layout1->addRow("y:", yedit);
    layout1->addRow("z:", zedit);
    layout1->addRow("rx:", rxedit);
    layout1->addRow("ry:", ryedit);
    layout1->addRow("rz:", rzedit);
    layout1->addRow(movelBtn);
}

MainWindow::~MainWindow() {}

//连接机械臂
void MainWindow::connectToRobot() {
    //获取ip和port
    QString ip = ipedit->text();
    int port = portedit->text().toInt();
    //调用URDriver 中调用connectToRobot的方法
    UrDriver::getInstance()->connectTORobot(ip,port);

}

//设置回调函数
void MainWindow::setCallback() {
    //设置连接成功的回调函数
    UrDriver::getInstance()->setConnectCallback([this]{
        //cout<<"连接成功" << endl;
        connectStatus->setText("已连接");
    });

    //设置断开连接的回调函数
    UrDriver::getInstance()->setDisconnectCallback([this]{
        connectStatus->setText("断开连接");
    });
}



/**
 * 处理signal和slot函数
 */
void MainWindow::signalAndSlot() {
    //连接机械臂的信号和槽
    connect(connectBtn, &QPushButton::clicked, this, &MainWindow::connectToRobot);

    //断开连接的信号和槽
    connect(disconnectBtn,&QPushButton::clicked,this,&MainWindow::disConnectToRobot);
}

/**
 * 断开连接
 */
void MainWindow::disConnectToRobot() {
    //调用driver的方法
    UrDriver::getInstance()->disConnectToRobot();
}
