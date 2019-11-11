

#ifndef URDRIVERCPP_MAINWINDOW_H
#define URDRIVERCPP_MAINWINDOW_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class MainWindow: public QWidget {
private:
    QFormLayout *layout1;
    QLineEdit *ip;
    QLineEdit *port;
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
};


#endif //URDRIVERCPP_MAINWINDOW_H
