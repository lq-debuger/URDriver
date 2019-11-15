#include "utils.h"

/**
 * 大小端存储模式的互换
 * @param p
 * @param size
 */
void reverseData(char *p, int size) {
    if (size == 4) {
        char tmp;
        tmp = p[0];
        p[0] = p[3];
        p[3] = tmp;

        tmp = p[1];
        p[1] = p[2];
        p[2] = tmp;
    } else if (size == 8) {
        char tmp;
        tmp = p[0];
        p[0] = p[7];
        p[7] = tmp;

        tmp = p[1];
        p[1] = p[6];
        p[6] = tmp;

        tmp = p[2];
        p[2] = p[5];
        p[5] = tmp;

        tmp = p[3];
        p[3] = p[4];
        p[4] = tmp;
    }
}

/**
 * 判断上一次指令是否执行完成
 * 判断上一次指令是否执行完
 * @param targetInstruction
 * @param urData
 * @return
 */
bool hasCompleteLastInstruction(Instruction targetInstruction, URData urData) {
    cout << "目标:" << "rx:" << targetInstruction.data[3] << "ry:" << targetInstruction.data[4] << "rz:"
         << targetInstruction.data[5] << endl;
    cout << "当前:" << "rx:" << urData.Tool_vector_actual[3] << "ry:" << urData.Tool_vector_actual[4] << "rz:"
         << urData.Tool_vector_actual[5] << endl;
    //目标数据
    double target[6];
    //当前数据
    double cur[6];

    memcpy(target, targetInstruction.data, 48);
    moveType type = targetInstruction.type;
    if (type == MOVEL) {
        memcpy(cur, urData.Tool_vector_actual, 48);
    } else if (type == MOVEJ) {
        memcpy(cur, urData.q_actual, 48);
    }

    //计算是哦否足够接近
    bool result = isNear(type, target, cur);
    return result;
}


/**
 * 判断当前点是否接近目标点，如果两点的方差小于0.018.就认为接近
 * @param type
 * @param target
 * @param cur
 * @return
 */
bool isNear(moveType type, double target[6], double cur[6]) {
    double total = 0;
    for (int i = 0; i < 6; ++i) {
        if (type == MOVEL || i >= 3) {
            total += pow(abs(target[i]) - abs(cur[i]), 2);
        } else {
            total += pow(target[i] - cur[i], 2);
        }
    }
    total /= 6;
    total = sqrt(total);
    cout << "total:" << total << endl;
    return total < 0.015;
}
