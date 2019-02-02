#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <xmmintrin.h>

using namespace std;

const int k_maxn = 1e4, k_maxm = 1e5, k_inf = 1e9;

vector <vector <pair <int, int>>> edges;
int dist[k_maxn][2];
bool used[k_maxn][2];

void dijkstra(int start_node, int size) {
	for (int i = 0; i < size; ++i) {
		dist[i][0] = dist[i][1] = k_inf;
	}
	dist[start_node][0] = dist[start_node][1] = 0;

	for (int i = 0; i < 2 * size; ++i) {
		int node = -1, trans = -1;
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < 2; ++k) {
				if (!used[j][k] && (node == -1 || dist[j][k] < dist[node][trans])) {
					node = j;
					trans = k;
				}
			}
		}
		if (dist[node][trans] == k_inf)
			break;
		used[node][trans] = true;
		for (int j = 0; j < edges[node].size(); ++j){
			int req_trans = edges[node][j].second, to = edges[node][j].first;
			dist[to][req_trans] = min(dist[to][req_trans], dist[node][trans] + (trans == req_trans ? 0 : 1));
		}
	}
}

int main() {
#ifndef  ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif // ! ONLINE_JUDGE	
	int n, m, start, end;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		edges.emplace_back(vector < pair<int, int>>());
	for (int i = 0; i < m; ++i) {
		int fst, snd;
		scanf("%d%d", &fst, &snd);
		edges[fst - 1].emplace_back(snd - 1, 1);
		edges[snd - 1].emplace_back(fst - 1, 0);
	}
	scanf("%d%d", &start, &end);
	dijkstra(start - 1, n);
	printf("%d", min(dist[end - 1][0], dist[end - 1][1]));
	return 0;
}