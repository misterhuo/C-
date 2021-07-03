#pragma once
#include <iostream>
using namespace std;

// 选手类
class Speaker
{
public:
	string m_Name; //选手姓名
	double m_Score[2]; // 有些选手可能最多有两个分数（两轮比赛）

};