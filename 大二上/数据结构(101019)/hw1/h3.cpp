#include<iostream>
using namespace std;

//������ǰ��һ�������꣬����0������ԣ�1��������
long long output[100000][2] = { {1,0} };
void fun(int& max_year, int year)
{
	if (year <= max_year)
		return;
	for (; max_year < year; max_year++)
		output[max_year + 1][0] = output[max_year][1] + 1, output[max_year + 1][1] = output[max_year][0] + output[max_year][1];

}

int main()
{
	int year[100000], max_year = 0, i;
	for (i = 0; i==0||year[i - 1] != -1; i++)
		cin >> year[i];
	i--;
	for (int t = 0; t < i; t++)
	{
		fun(max_year, year[t]);
		cout << output[year[t]][1] << " " << output[year[t]][1] + output[year[t]][0] << endl;
		
	}
	return 0;
}