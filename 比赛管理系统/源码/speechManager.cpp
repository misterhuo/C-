#include "speechManager.h"
#include<string>
#include<deque>
#include <iostream>
#include<functional>
using namespace std;

//���캯��
SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->initSpeech();

	//����ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();

}

//�˵�����
void SpeechManager::show_Menu()
{
	cout << "*************************************************" << endl;
	cout << "**************��ӭ�μ��ݽ�����*******************" << endl;
	cout << "************** 1.��ʼ�ݽ����� *******************" << endl;
	cout << "************** 2.�鿴�����¼ *******************" << endl;
	cout << "************** 3.��ձ�����¼ *******************" << endl;
	cout << "************** 0.�˳��������� *******************" << endl;
	cout << "*************************************************" << endl;
	cout << endl;

}

void  SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
};

void SpeechManager::initSpeech()
{
	//������Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ����������
	this->m_Index = 1;
	this->m_Record.clear();

};

//����12��ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ�� ";
		name += nameSeed[i];

		
		Speaker sp; // ��������ѡ��
		sp.m_Name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ�Ų��ҷŵ�V1������
		this->v1.push_back(i + 10001);
		// ѡ�ֱ���Լ���Ӧѡ�ַ���map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

//��ʼ�������������̵Ŀ��ƺ���
void SpeechManager::startSpeech()
{
	//�������� ��һ�֣�1.��ǩ 2.���� 3.��ʾ�������
	//         �ڶ��� ��1.��ǩ 2.���� 3.���ս�� 4.����������ļ���  
	this->speechDraw();
	this->speechContest();
	this->showScore();

	//�ڶ���
	this->m_Index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();

	//�������
	this->saveRecord();
	cout << "�������������" << endl;
	system("pause");
	system("cls");
	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeech();

	this->createSpeaker();

	//���������¼

	this->loadRecord();
}

//��ǩ
void SpeechManager::speechDraw()
{
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------" << endl;
	cout << "��ǩ����ݽ�˳��Ϊ��" << endl;
	if (this->m_Index == 1)
	{ 
		//��һ�ֱ���
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

//����
void SpeechManager::speechContest()
{
	cout << "----��<<" << this->m_Index << ">>�ֱ���ѡ����ʽ��ʼ---" << endl;
	cout << "-------------------------------------" << endl;

	multimap<double, int, greater<double>>groupScore; //��ʱ���������С��ɼ�

	int num = 0; //��¼��Ա������ 6��һ��
	vector<int>v_Src; //����ѡ������
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	// ��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for(int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			// cout << score << "";
			d.push_back(score);
			
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//ȥ����߷ֺ���ͷ�
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		//��ƽ���ַ���map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		groupScore.insert(make_pair(avg, *it)); //key�ǵ÷֣�value�Ǿ���ѡ�ֱ��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end();it++)
			{
				cout << "��ţ�" << it->second << "������" << this->m_Speaker[it->second].m_Name << "�ɼ���" <<
					this->m_Speaker[it->second].m_Score[this -> m_Index - 1] << endl;
			}
			//ȡ��ǰ����
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
			groupScore.clear();//С���������
		}
	}
	cout << "------------��" << this->m_Index << "�ֱ�����ϣ�---------" << endl;
	system("pause");
}

//��ʾ�÷�
void SpeechManager::showScore()
{
	cout << "---------��" << this->m_Index << "�ֽ���ѡ����Ϣ����---------" << endl;
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
		cout << "������" << this->m_Speaker[*it].m_Name << "�ɼ���" <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //��׷�ӵķ�ʽд�ļ�
	//��ÿ��ѡ������д��
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "������¼�ѱ���" << endl;
	//���ļ�¼״̬��Ϊ��
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

	//�ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
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
				//û���ҵ������
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
		cout << "�����¼�����ڣ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��"
				<< "�ھ���ţ�" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
				<< "�ھ���ţ�" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " "
				<< "�ھ���ţ�" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << " " << endl;
		}
	}
	system("pause");
	system("cls");
	
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();

		//����ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;

	}
	system("pause");
	system("cls");
}

// ��������
SpeechManager::~SpeechManager()
{

}