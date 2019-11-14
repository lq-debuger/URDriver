
#ifndef URDRIVERCPP_UTILS_H
#define URDRIVERCPP_UTILS_H

#include "data.h"

//大小端存储模式的互换
void reverseData(char *p,int size);

//判断上一次指令是否执行完成
bool hasCompleteLastInstruction(Instruction targetInstruction,URData urData);


#endif //URDRIVERCPP_UTILS_H
