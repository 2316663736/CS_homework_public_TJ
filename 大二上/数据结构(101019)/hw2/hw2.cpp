#include<iostream>
#include<string>
using namespace std;

struct Student_no
{
	string name; //����
	string id; //ѧ��
	Student_no* next; //ָ����һλ��ָ��
};
void insert(Student_no* &head,int& len)
{
	/*
     head �������ͷ�ڵ�
     len  ����ǰ������
     �����������õķ�ʽ����ֵ
	 */

	
	/*
	 ���룺������Ҫ�����λ�á�ѧ�š����������ж���Ҫ�����λ���Ƿ�Ϸ���1��len+1�������Ϸ�������ʵ�ֲ���
     ʵ�֣���������Ӧ����λ�ã������ڴ棨����ʧ�����-1���˳�������������ָ��任������Ӧ�Ľڵ㣬�����ȼ�һ
     ���������ɹ����0���������-1
     */
	int place;
	string no, name;
	//���������ж�ʡ��
	Student_no* new_stu = new Student_no{ no, name, NULL };
	if (place == 1) {
		new_stu->next = head;
		head = new_stu;
	}
	else {
		Student_no* prev = head;
		for (int i = 1; i < place - 1; i++) {
			prev = prev->next;
		}
		new_stu->next = prev->next;
		prev->next = new_stu;
	}
	len++;
	//���ʡ��
}
void remove(Student_no* &head, int & len)
{
	/*
	 head �������ͷ�ڵ�
	 len  ����ǰ������
	 ����ͨ�����õķ�ʽ����ֵ
	 */

	/*
	���룺������Ҫɾ����λ�ã����ж��Ƿ�Ϸ�
	ʵ�֣���������ɾ���ڵ�ǰ������ָ��任ɾ�������б��Ϊi�Ľڵ㣬ͬʱ�ͷ��ڴ棬�����ȼ�
	һ
	�����ɾ���ɹ����0���������-1��û�в�ѯ������λѧ����
	*/
	int place;
	Student_no* toDelete ;
	//���������ж�ʡ��
	if (place == 1) {
		toDelete = head;
		head = head->next;
	}
	else {
		Student_no* prev = head;
		for (int i = 1; i < place - 1; ++i) {
			prev = prev->next;
		}
		toDelete = prev->next;
		prev->next = toDelete->next;
	}
	delete toDelete;
	len--;
	//���ʡ��
}
void checkName(Student_no* head, string name)
{
	/*
	head �����ͷ�ڵ�
	name Ҫ��ѯ��ѧ������
	*/
	/*
	ʵ�֣������б��������ÿһ���ڵ��д洢�������Ƿ�������������ͬ
	��������ҵ���λѧ����������Ϣ���������-1
	*/
	Student_no* current = head;
	int place = 1;
	while (current) {
		if (current->name == name) {
			cout << place<< " " << current->id << " " << current->name << endl;
			return;
		}
		current = current->next;
		place++;
	}
	cout << -1 << endl; // �Ҳ����������  
}




void _insert(string* name, string* no_id,int &now_num)
{
	int place;
	string tem_name, tem_no;
	cin >> place >>  tem_no>>tem_name;
	if (place >= 1 && place <= (now_num + 1))
	{
		int tem_place;
		for (tem_place = now_num ; tem_place != (place-1); tem_place--)
		{
			*(name + tem_place) = *(name + tem_place - 1);
			*(no_id + tem_place) = *(no_id + tem_place - 1);
		}
		*(name + place - 1) = tem_name;
		*(no_id + place - 1) = tem_no;
		cout << "0" << endl;
		now_num++;
	}
	else
		cout << "-1" << endl;

}

void _remove(string* name, string* no_id, int &now_num)
{
	int place;
	cin >> place;
	if (place >= 1 && place <= now_num)
	{
		int tem_place;
		for (tem_place = place - 1; tem_place != (now_num ); tem_place++)
		{
			*(name + tem_place) = *(name + tem_place + 1);
			*(no_id + tem_place) = *(no_id + tem_place + 1);
		}
		cout << "0" << endl;
		now_num--;
	}
	else
		cout << "-1" << endl;
}
void _check(string* name, string* no_id, int now_num)
{
	string chose, name_no;
	cin >> chose >> name_no;
	if (chose == "name")
	{
		int i;
		for (i = 0; i < now_num; i++)
			if (name_no == *(name + i))
			{
				cout << i + 1 << " " << no_id[i] << " " << name[i] << endl;
				return;
			}

	}
	else if (chose == "no")
	{
		int i;
		for (i = 0; i < now_num; i++)
			if (name_no == *(no_id + i))
			{
				cout << i + 1 << " " << no_id[i] << " " << name[i] << endl;
				return;
			}
	}
	cout << "-1" << endl;
}

int main()
{
	int now_num;
	string name[100000], no_id[100000];
	cin >> now_num;
	for (int i = 0; i < now_num; i++)
		cin >> no_id[i] >> name[i];

	string choice;
	while (1)
	{
		cin >> choice;
		if (choice == "insert")
			_insert(name, no_id, now_num);
		else if (choice == "remove")
			_remove(name, no_id, now_num);
		else if (choice == "check")
			_check(name,no_id,now_num);
		else if (choice == "end")
			break;
	}
	cout << now_num << endl;
	return 0;

}
/*#include<iostream>
#include<string>
#include <vector> 
using namespace std;   

vector<string> vec[2];
string no_name[1000][2];
int max_n=0;
void _insert()
{
	int place;
	string n_n[2];
	cin >> place>>n_n[0]>>n_n[1];
	if (place >= 1 && place <= int(vec[0].size()))
	{
		vec[0].insert(vec[0].begin() + place - 1, n_n[0]);
		vec[1].insert(vec[1].begin() + place - 1, n_n[1]);
		cout << "0" << endl;
		return;
	}
	else if (place == int(vec[0].size() + 1))
	{
		vec[0].push_back(n_n[0]);
		vec[1].push_back(n_n[1]);
		cout << "0" << endl;
		return;
	}
	cout << "-1" << endl;
}

void _remove()
{

	int place;
	cin >> place;
	if (place >= 1 && place <= int(vec[0].size()))
	{
		vec[0].erase(vec[0].begin() + place - 1);
		vec[1].erase(vec[1].begin() + place - 1);
		cout << "0" << endl;
		return;
	}
	cout << "-1" << endl;
}

void _check()
{
	string ss,n_n;
	cin >> ss>>n_n;
	int which = 0;
	if (ss == "name")
		which = 1;
	for (int i = 0; i < int(vec[0].size()); i++)
	{
		if (n_n == vec[which][i ])
		{
			cout <<i+1 << " " << vec[0][i ] << " " << vec[1] [i ]<< endl;
			return;
		}
	}
	cout << "-1" << endl;
}

int main()
{
	string n_n[2];
	cin >> max_n;
	vec[0].resize(max_n);
	vec[1].resize(max_n);
	for (int i = 0; i < max_n;i++)
		cin >> vec[0][i ] >> vec[1][i ];

	string choice ;
	while (1)
	{
		cin >> choice;
		if (choice == "insert")
			_insert();
		else if (choice == "remove")
			_remove();
		else if (choice == "check")
			_check();
		else if (choice == "end")
			break;
	}
	cout << vec[0].size() << endl;
	return 0;
}*/