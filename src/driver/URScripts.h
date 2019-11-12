
#ifndef URDRIVERCPP_URSCRIPTS_H
#define URDRIVERCPP_URSCRIPTS_H

#include <iostream>
#include <QString>
#include <fstream>
#include <QDebug>
#include "data.h"
using namespace std;

class URScripts {
private:
    //初始脚本内容
    QString baseString;
    //最后的脚本内容
    QString commandString;
    //数组保存 ARG_CHANGE_Q ARG_CHANGE_A ARG_CHANGE_V数据
    QString arr[3];
public:
    URScripts();

    ~URScripts();

    //加载脚本额
    void loadScripts(string path);

    //moveJ
    void moveJ(double *pose, double acc, double vel);

    //moveL
    void moveL(double *pose, double acc, double vel);

    //获取发送的脚本
    QString getCommandScript();

private:
    void changeScript(moveType type, double data[6], double acc = 1.4, double vel = 1.05);
};


#endif //URDRIVERCPP_URSCRIPTS_H
