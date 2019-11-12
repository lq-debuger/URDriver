

#ifndef URDRIVERCPP_MAINWINDOW_H
#define URDRIVERCPP_MAINWINDOW_H

#include <QWidget>
#include "UrDriver.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <math.h>
class MainWindow: public QWidget {
private:
    //角度转换成弧度
    double DEGREETORAD = M_PI/180;
    QFormLayout *layout1;
    QLineEdit *ipedit;
    QLineEdit *portedit;
    QLabel *connectStatus;
    QPushButton *connectBtn;
    QPushButton *disconnectBtn;
    QLineEdit *joint1;
    QLineEdit *joint2;
    QLineEdit *joint3;
    QLineEdit *joint4;
    QLineEdit *joint5;
    QLineEdit *joint6;
    QPushButton *movejBtn;
    QLineEdit *xedit;
    QLineEdit *yedit;
    QLineEdit *zedit;
    QLineEdit *rxedit;
    QLineEdit *ryedit;
    QLineEdit *rzedit;
    QPushButton *movelBtn;
public:
    MainWindow(QWidget* parent = Q_NULLPTR);

    ~MainWindow();

    void initUI();

    //连接机械臂
    void connectToRobot();

    //断开连接
    void disConnectToRobot();

    //处理signal和slot函数
    void signalAndSlot();

    //设置回调函数
    void setCallback();

    //moveL
    void moveL();

    //moveJ
    void moveJ();
};


#endif //URDRIVERCPP_MAINWINDOW_H
