

#ifndef URDRIVERCPP_MAINWINDOW_H
#define URDRIVERCPP_MAINWINDOW_H

#include <QWidget>
#include "UrDriver.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class MainWindow: public QWidget {
private:
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
};


#endif //URDRIVERCPP_MAINWINDOW_H
