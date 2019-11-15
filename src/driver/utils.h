
#ifndef URDRIVERCPP_UTILS_H
#define URDRIVERCPP_UTILS_H

#include <memory.h>
#include "data.h"
#include <cmath>
#include <iostream>
using namespace std;

//大小端存储模式的互换
void reverseData(char *p,int size);

//判断上一次指令是否执行完成
bool hasCompleteLastInstruction(Instruction targetInstruction,URData urData);

//判断当前点是否接近目标点
bool isNear(moveType type, double target[6], double cur[6]);

#endif //URDRIVERCPP_UTILS_H
