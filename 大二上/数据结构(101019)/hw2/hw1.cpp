#include<iostream>
using namespace std;

int main()
{
	int input[100001] = { 0 }, output[100001] = { 0 }, len, k;
	cin >> len >> k;                  //���������鳤�Ⱥ���תλ����
	for (int i = 0; i < len; i++)
		cin >> input[i];             //��������Ԫ��
	for (int i = 0; i < len; i++)
		output[(i + k) % len] = input[i];
	for (int i = 0; i < len; i++)
		cout << output[i] << endl;;
	return 0;
}