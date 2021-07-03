#include "speechManager.h"
#include<string>
#include<deque>
#include <iostream>
#include<functional>
using namespace std;

//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();

}

//菜单功能
void SpeechManager::show_Menu()
{
	cout << "*************************************************" << endl;
	cout << "**************欢迎参加演讲比赛*******************" << endl;
	cout << "************** 1.开始演讲比赛 *******************" << endl;
	cout << "************** 2.查看往届记录 *******************" << endl;
	cout << "************** 3.清空比赛记录 *******************" << endl;
	cout << "************** 0.退出比赛程序 *******************" << endl;
	cout << "*************************************************" << endl;
	cout << endl;

}

void  SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
};

void SpeechManager::initSpeech()
{
	//容器都为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;
	this->m_Record.clear();

};

//创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手 ";
		name += nameSeed[i];

		
		Speaker sp; // 创建具体选手
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号并且放到V1容器中
		this->v1.push_back(i + 10001);
		// 选手编号以及对应选手放入map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

//开始比赛，整个流程的控制函数
void SpeechManager::startSpeech()
{
	//比赛流程 第一轮：1.抽签 2.比赛 3.显示晋级结果
	//         第二轮 ：1.抽签 2.比赛 3.最终结果 4.保存分数到文件中  
	this->speechDraw();
	this->speechContest();
	this->showScore();

	//第二轮
	this->m_Index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();

	//保存分数
	this->saveRecord();
	cout << "本届比赛结束！" << endl;
	system("pause");
	system("cls");
	//重置比赛并获取记录
	//初始化容器和属性
	this->initSpeech();

	this->createSpeaker();

	//加载往届记录

	this->loadRecord();
}

//抽签
void SpeechManager::speechDraw()
{
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-------------------------------------" << endl;
	cout << "抽签后的演讲顺序为：" << endl;
	if (this->m_Index == 1)
	{ 
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛
void SpeechManager::speechContest()
{
	cout << "----第<<" << this->m_Index << ">>轮比赛选手正式开始---" << endl;
	cout << "-------------------------------------" << endl;

	multimap<double, int, greater<double>>groupScore; //临时容器，存放小组成绩

	int num = 0; //记录人员个数， 6人一组
	vector<int>v_Src; //比赛选手容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	// 遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for(int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << "";
			d.push_back(score);
			
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//去掉最高分和最低分
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		//将平均分放入map容器里
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it)); //key是得分，value是具体选手编号
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++)
			{
				cout << "编号：" << it->second << "姓名：" << this->m_Speaker[it->second].m_Name << "成绩：" <<
					this->m_Speaker[it->second].m_Score[this -> m_Index - 1] << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//小组容器清空
		}
	}
	cout << "------------第" << this->m_Index << "轮比赛完毕！---------" << endl;
	system("pause");
}

//显示得分
void SpeechManager::showScore()
{
	cout << "---------第" << this->m_Index << "轮晋级选手信息如下---------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "姓名：" << this->m_Speaker[*it].m_Name << "成绩：" <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //用追加的方式写文件
	//将每个选手数据写入
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "比赛记录已保存" << endl;
	//更改记录状态不为空
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{ 
	ifstream ifs("speech.csv", ios::in);
	  
	if (!ifs.is_open())
	{ 
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件清空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 0;

	while (ifs >> data)
	{
		// cout << data << endl;
		vector<string>v;

		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//没有找到的情况
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "往届记录不存在！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "界"
				<< "冠军编号：" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
				<< "冠军编号：" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
				<< "冠军编号：" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << " " << endl;
		}
	}
	system("pause");
	system("cls");
	
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;

	}
	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager()
{

}