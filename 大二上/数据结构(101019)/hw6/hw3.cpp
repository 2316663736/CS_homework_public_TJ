



/**
 * @file    solution.cpp
 * @name    ����λ����������
 * @date    2024-12-16
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     ��������Ҫ�ύ�Ĵ���     */
/********************************/
class Solution {
public:
    int solve(vector<vector<string>>& old_chart, vector<vector<string>>& new_chart) {
        // ��ȡ��λ��ĳߴ�
        int n = old_chart.size();
        int m = old_chart[0].size();

        // ����ѧ�����ֵ�λ�õ�ӳ��
        map<string, pair<int, int>> student_pos;
        // ���ڱ���ѷ��ʵ�λ��
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        // ��¼�ܵĽ�������
        int total_swaps = 0;

        // ����ѧ����λ�õ�ӳ���ϵ
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                student_pos[old_chart[i][j]] = make_pair(i, j);
            }
        }

        // ����ÿ��λ�ã�Ѱ���û���
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // �����λ��δ��������Ҫ�ƶ�����ǰѧ��������ȷλ�ã�
                if (!visited[i][j] && old_chart[i][j] != new_chart[i][j]) {
                    int cycle_length = 0;  // ��¼��ǰ�û����ĳ���
                    int curr_i = i, curr_j = j;  // ��ǰ�����λ��

                    // ׷���û���
                    while (!visited[curr_i][curr_j]) {
                        // ��ǵ�ǰλ���ѷ���
                        visited[curr_i][curr_j] = true;
                        cycle_length++;

                        // �ҵ�Ӧ�����ڵ�ǰλ�õ�ѧ��
                        string target_student = new_chart[curr_i][curr_j];
                        // ��ȡ��ѧ����ԭ��λ���е�λ��
                        pair<int, int> next_pos = student_pos[target_student];
                        int next_i = next_pos.first;
                        int next_j = next_pos.second;

                        // ����ص���㣬˵���ҵ���һ���������û���
                        if (next_i == i && next_j == j) {
                            break;
                        }

                        // �ƶ�����һ��λ��
                        curr_i = next_i;
                        curr_j = next_j;
                    }

                    // ���ڳ���Ϊk���û�������Ҫk-1�ν���
                    if (cycle_length > 0) {
                        total_swaps += (cycle_length - 1);
                    }
                }
            }
        }

        return total_swaps;
    }
};
/********************************/
/*     ��������Ҫ�ύ�Ĵ���     */
/********************************/

int main() {
    // ��ȡ���������������
    int n, m;
    cin >> n >> m;

    // ��������ȡԭʼ��λ��
    vector<vector<string>> old_chart(n, vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> old_chart[i][j];
        }
    }

    // ��������ȡĿ����λ��
    vector<vector<string>> new_chart(n, vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> new_chart[i][j];
        }
    }

    // ����Solution���󲢽������
    Solution s;
    cout << s.solve(old_chart, new_chart) << endl;

    return 0;
}





































// 
// 
// 
// 
// 
// 
// 
// 
// #include<iostream>
//#include<string>
//using namespace std;
//
//
//
//class all_num {
//private:
//	struct BST_node {
//		string key;
//		BST_node* left;
//		BST_node* right;
//		BST_node(string k) :key(k), left(nullptr), right(nullptr)
//		{
//
//		}
//	};
//	int all_f;//�ܹ��ж���������λ��
//	int arroud;//��Щ���ܹ����Թ��ɶ��ٻ�����һȦ������λ�ûص��˵�һ���ˣ�
//	BST_node* root;
//public:
//	void insert(const string k);
//};
//
//struct Node {
//	string key;
//	string father ;
//};
//
//void all_num::insert(const string k)
//{
//	BST_node* now=root;
//	while (1)
//	{
//
//	}
//}
//int main()
//{
//	int all_different = 0, all_exchange = 0;
//	int n, m;
//	cin >> n >> m;
//	Node* old_chart = new(nothrow) Node[n * m];
//	Node* new_chart = new(nothrow) Node[n * m];
//	if (!old_chart || !new_chart)
//		exit(-999);
//	for (int i = 0; i < n * m; i++)
//	{
//		cin >> old_chart[i].key;
//		old_chart[i].father = old_chart[i].key;
//	}
//	for (int i = 0; i < n * m; i++)
//	{
//		cin >> new_chart[i].key;
//		new_chart[i].father = new_chart[i].key;
//	}
//
//	for (int tem_n = 0; tem_n < n; tem_n++)
//	{
//		for (int tem_m = 0; tem_m < m; tem_m++)
//		{
//			if (old_chart[tem_n * m + tem_m].key == new_chart[tem_n * m + tem_m].key)
//				continue;
//		}
//	}
//}