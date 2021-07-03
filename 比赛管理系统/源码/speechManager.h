// 防止头文件重复编译
#pragma once
// 标准输入输出流
#include <iostream>
// 引用标准命名空间
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include<deque>
#include<functional>
#include <numeric> 
#include<fstream>

// 设计演讲管理类
class SpeechManager
{
public:
	// 构造函数
	SpeechManager();

	// 菜单功能
	void show_Menu();

	//退出系统功能
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void initSpeech();

	//创建12名选手
	void createSpeaker();

	//开始比赛，整个流程的控制函数
	void startSpeech();

	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showScore();
	//保存分数
	void saveRecord();

	//读取记录
	void loadRecord();
	//显示记录
	void showRecord(); 
	// 判断文件是否为空
	bool fileIsEmpty;
	// 存放往届记录的容器
	map<int, vector<string>> m_Record;
	//清空记录
	void clearRecord();



	//成员属性
	//保存第一轮比赛选手编号容器
	vector<int>v1;

	//保存第一轮比赛晋级选手编号容器
	vector<int>v2;

	//最后胜出的前三名
	vector<int>vVictory;

	//存放编号以及对应选手的容器
	map<int, Speaker>m_Speaker;

	//存放比赛的轮数
	int m_Index;

};