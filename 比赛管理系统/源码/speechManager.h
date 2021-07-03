// ��ֹͷ�ļ��ظ�����
#pragma once
// ��׼���������
#include <iostream>
// ���ñ�׼�����ռ�
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include<deque>
#include<functional>
#include <numeric> 
#include<fstream>

// ����ݽ�������
class SpeechManager
{
public:
	// ���캯��
	SpeechManager();

	// �˵�����
	void show_Menu();

	//�˳�ϵͳ����
	void exitSystem();

	//��������
	~SpeechManager();

	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ�������������̵Ŀ��ƺ���
	void startSpeech();

	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showScore();
	//�������
	void saveRecord();

	//��ȡ��¼
	void loadRecord();
	//��ʾ��¼
	void showRecord(); 
	// �ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	// ��������¼������
	map<int, vector<string>> m_Record;
	//��ռ�¼
	void clearRecord();



	//��Ա����
	//�����һ�ֱ���ѡ�ֱ������
	vector<int>v1;

	//�����һ�ֱ�������ѡ�ֱ������
	vector<int>v2;

	//���ʤ����ǰ����
	vector<int>vVictory;

	//��ű���Լ���Ӧѡ�ֵ�����
	map<int, Speaker>m_Speaker;

	//��ű���������
	int m_Index;

};