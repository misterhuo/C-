#include <iostream>
#include "speechManager.h"
#include<string>
#include<ctime>
using namespace std;

int main()
{

	//创建管理类的对象
	SpeechManager sm;
	//随机数种子
	srand((unsigned int)time(NULL));

	int choice = 0; //接受用户输入
	while (true)
	{
		sm.show_Menu();
		cout << "请输入要执行的功能" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2: //查看往届记录
			sm.showRecord();
			break;
		case 3: //清空比赛记录
			sm.clearRecord();
			break;
		case 0: //退出系统
			sm.exitSystem();
			break;
		default:
			system("cls"); //清屏操作
			break;
		}
	}
	system("pause");
	return 0;
}