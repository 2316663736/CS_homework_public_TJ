#include <iostream>
#include<vector>
using namespace std;

void bfs(int row, int the_id, vector<vector<bool>>& connected, vector<int>& father_,const int num_country)
{
	father_[row] = the_id;
	for (int i = 0; i < num_country; i++)
	{
		if (connected[row] [i]&& father_[i] == -1)//��i����the_id�������ˣ���Ŀ�и��ģ��Ѿ������ţ��ҵ�i����û�н��г�ʼ��
		{
			bfs(i, the_id, connected, father_, num_country);
		}
	}
}

int main()
{
	int num_country = 0, num_bridge = 0;
	cin >> num_country;
	vector<vector<int>> all(num_country, vector<int>(num_country));
	for (int i = 0; i < num_country; i++)
		for (int j = 0; j < num_country; j++)
			cin >> all[i][j];
	//��ʾ�ڵ��Ƿ���ͨ
	vector<vector<bool>> connected(num_country, vector<bool>(num_country, false));

	cin >> num_bridge;
	for (int i = 0; i < num_bridge; i++)
	{
		int u, v;
		cin >> u >> v;
		connected[u-1][v-1] = connected[v-1][u-1] = true;
	} 

	vector<int> father_(num_country, -1);
	int the_id = 0;
	for (the_id = 0; the_id < num_country; the_id++)
	{
		if (father_[the_id] == -1)//û�г�ʼ����
		{
			bfs(the_id, the_id, connected, father_, num_country);
		}
	}
	int all_const = 0;

	while (1)
	{
		int minDist = 0x0ffff;
		int bestA = -1, bestB = -1;

		// ����
		for (int i = 0; i < num_country; i++)
		{
			for (int j = i + 1; j < num_country; j++)
			{
				// ������������ڲ�ͬ����ͨ����
				if (father_[i] != father_[j])
				{
					// �ҵ��˸��̵ı�
					if (all[i][j] < minDist)
					{
						minDist = all[i][j];
						bestA = i;
						bestB = j;
					}
				}
			}
		}
		if (bestA != -1 && bestB != -1)
		{
			all_const += minDist;

			// ��bestB���ڵ���ͨ�����ϲ���bestA����ͨ������
			int old = father_[bestB];
			for (int i = 0; i < num_country; i++)
				if (father_[i] == old)
					father_[i] = father_[bestA];



			bool con = true;
			for (int i = 0; i < num_country; i++)
			{
				if (father_[i] != father_[0])//��һ���͵�һ��û������
				{
					con = false;
					break;
				}
			}
			if (con)
			{
				cout << all_const << endl;
				return 0;
			}
		}


	}

}


