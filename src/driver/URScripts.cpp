
#include "URScripts.h"

URScripts::URScripts() {}

URScripts::~URScripts() {}

/**
 * 加载脚本
 * @param path
 */
void URScripts::loadScripts(string path) {
    //IO操作
    //创建fstream
    fstream file;
    //打开
    file.open(path, ios_base::in);
    //如果打开成功，就读取数据
    if (file.is_open()) {
//        qDebug()<<"打开成功" << endl;
        //把文件指针移到最后
        file.seekg(0, ios_base::end);
        //获取当前位置，得到文件的长度
        int lenght = file.tellg();
        //字符数组
        char buf[lenght];
        //移动指针到最前面
        file.seekg(0, ios_base::beg);
        //读取
        file.read(buf, lenght);
        //保存脚本
        baseString = QString(buf);
//        qDebug()<< baseString << endl;
    }
}

/**
 * moveL
 * @param pose
 * @param acc
 */
void URScripts::moveL(double *pose, double acc, double vel) {
    changeScript(MOVEL, pose, acc, vel);
}

/**
 * 更换对应的脚本文件
 * @param type
 * @param data
 * @param acc
 * @param vel
 */
void URScripts::changeScript(moveType type, double *data, double acc, double vel) {
    QString param;
    if (type == moveType::MOVEJ) {
        param = "cmd_servo_q=[";
    } else if (type == moveType::MOVEL) {
        param = "cmd_servo_q=p[";
    }
    for (int i = 0; i < 6; ++i) {
        param += QString::number(data[i]);
        if (i != 5) {
            param += ",";
        }
    }
    param += "]";
    //关节角度
    arr[0] = param;
    //加速度
    arr[1] = acc;
    //速度
    arr[2] = vel;
    //重置发送的脚本内容
    commandString = baseString;
    //替换脚本中的ARG_CHANGE_Q ARG_CHANGE_A ARG_CHANGE_V
    commandString.replace("ARG_CHANGE_Q", arr[0]);
    commandString.replace("ARG_CHANGE_A", arr[1]);
    commandString.replace("ARG_CHANGE_V", arr[2]);

    //替换指定移动类型
    if (type == moveType::MOVEL && !commandString.contains("movel")) {
        commandString.replace("movej", "movel");
    } else if (type == moveType::MOVEJ && !commandString.contains("movej")) {
        commandString.replace("movel", "movej");
    }
}

/**
 * moveJ
 * @param pose
 * @param acc
 * @param vel
 */
void URScripts::moveJ(double *pose, double acc, double vel) {
    changeScript(MOVEJ, pose, acc, vel);
}


/**
 * 获取要发送的脚本
 * @return
 */
QString URScripts::getCommandScript() {
    return commandString;
}
