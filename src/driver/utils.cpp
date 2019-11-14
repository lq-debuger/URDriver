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
 * @param targetInstruction
 * @param urData
 * @return
 */
bool hasCompleteLastInstruction(Instruction targetInstruction, URData urData) {
    return false;
}
