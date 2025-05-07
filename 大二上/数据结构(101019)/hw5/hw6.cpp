#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ʹ���ڽӱ�洢ͼ
class Edge {
public:
    int to, weight;
    Edge(int t, int w) : to(t), weight(w)
    {
    }
};

class Solution {
public:
    vector<vector<Edge>> graph;
    vector<int> grass_points;
    int n;

    // Dijkstra�㷨�����start���������������̾���
    vector<long long> dijkstra(int start) 
    {
        vector<long long> dist(n + 1, LLONG_MAX);
        dist[start] = 0;

        queue<int> pq;
        pq.push( start);

        while (!pq.empty()) 
        {
            int curr = pq.front();
            pq.pop();


            for (int i = 0; i < graph[curr].size(); i++) 
            {
                const Edge& edge = graph[curr][i];
                if (dist[edge.to] > dist[curr] + edge.weight) 
                {
                    dist[edge.to] = dist[curr] + edge.weight;
                    pq.push(edge.to);
                }
            }
        }
        return dist;
    }

    void solve()
    {
        int m;
        cin >> n >> m;

        graph.resize(n + 1);

        // ��ȡ��
        for (int i = 0; i < m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            graph[x].push_back(Edge(y, w));
            graph[y].push_back(Edge(x, w));
        }

        // ��ȡ�ݵص���������
        int h, r;
        cin >> h >> r;

        // ��ȡ�ݵص�
        grass_points.resize(h);
        for (int i = 0; i < h; i++) {
            cin >> grass_points[i];
        }

        // ����ÿƥ��
        for (int i = 0; i < r; i++) {
            int start, end;
            cin >> start >> end;

           
            vector<long long> from_start = dijkstra(start);    // �������㵽���е����̾���
            vector<long long> from_end = dijkstra(end);   // ������յ㵽���е����̾���

            // �ҵ���������ݵص�����·��
            long long min_dist = LLONG_MAX;
            for (int i = 0; i < grass_points.size(); i++) {
                int grass = grass_points[i];
                if (from_start[grass] != LLONG_MAX && from_end[grass] != LLONG_MAX) {
                    min_dist = min(min_dist, from_start[grass] + from_end[grass]);
                }
            }

            cout << min_dist << endl;
        }
    }
};

int main() {


    Solution solution;
    solution.solve();

    return 0;
}