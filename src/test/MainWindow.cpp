
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    //加载脚本
    UrDriver::getInstance()->loadScripts("../data/UrDriverScript/Driver7");

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

    joint1 = new QLineEdit("-6");
    joint2 = new QLineEdit("-30");
    joint3 = new QLineEdit("12");
    joint4 = new QLineEdit("0");
    joint5 = new QLineEdit("-180");
    joint6 = new QLineEdit("18");
    movejBtn = new QPushButton("moveJ");
    layout1->addRow("关节1：", joint1);
    layout1->addRow("关节2：", joint2);
    layout1->addRow("关节3：", joint3);
    layout1->addRow("关节4：", joint4);
    layout1->addRow("关节5：", joint5);
    layout1->addRow("关节6：", joint6);
    layout1->addRow(movejBtn);

    xedit = new QLineEdit("-0.321");
    yedit = new QLineEdit("-0.03468");
    zedit = new QLineEdit("-0.3656");
    rxedit = new QLineEdit("2.4198");
    ryedit = new QLineEdit("2.2844");
    rzedit = new QLineEdit("2.0809");
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
    connect(disconnectBtn, &QPushButton::clicked, this, &MainWindow::disConnectToRobot);

    //moveL的信号与槽函数
    connect(movelBtn, &QPushButton::clicked, this, &MainWindow::moveL);
    //moveJ的信号与槽函数
    connect(movejBtn, &QPushButton::clicked, this, &MainWindow::moveJ);
}

/**
 * 断开连接
 */
void MainWindow::disConnectToRobot() {
    //调用driver的方法
    UrDriver::getInstance()->disConnectToRobot();
}

/**
 * movel的函数
 */
void MainWindow::moveJ() {
    //获取六个关节的值
    double j1 = joint1->text().toDouble()*DEGREETORAD;
    double j2 = joint2->text().toDouble()*DEGREETORAD;
    double j3 = joint3->text().toDouble()*DEGREETORAD;
    double j4 = joint4->text().toDouble()*DEGREETORAD;
    double j5 = joint5->text().toDouble()*DEGREETORAD;
    double j6 = joint6->text().toDouble()*DEGREETORAD;
    double  arr[6]={j1,j2,j3,j4,j5,j6};
    //调用driver的方法
    UrDriver::getInstance()->moveJ(arr);
}

/**
 * moveJ的函数
 */
void MainWindow::moveL() {
    //获取位置和姿态的数据
    double x = xedit->text().toDouble();
    double y = yedit->text().toDouble();
    double z = zedit->text().toDouble();
    double rx = rxedit->text().toDouble();
    double ry = ryedit->text().toDouble();
    double rz = rzedit->text().toDouble();
    double pose[6] = {x, y, z, rx, ry, rz};
    UrDriver::getInstance()->moveL(pose);
}
