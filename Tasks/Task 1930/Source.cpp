#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1e4, MAXM = 1e5, INF = 1e9;

int graph[MAXN][MAXN], dist[MAXN][2];
bool used[MAXN][2];

void dijkstra(int start_node_, int size_) {
	for (int i = 0; i < size_; ++i) {
		dist[i][0] = dist[i][1] = INF;
	}
	dist[start_node_][0] = dist[start_node_][1] = 0;

	for (int i = 0; i < 2*size_; ++i) {
		int node = -1, trans = -1;
		for (int j = 0; j < size_; ++j) {
			for (int k = 0; k < 2; ++k) {
				if (!used[j][k] && (node == -1 || dist[j][k] < dist[node][trans])) {
					node = j;
					trans = k;
				}
			}
		}
		if (dist[node][trans] == INF)
			break;
		used[node][trans] = true;
		for (int j = 0; j < size_; ++j) {
			if (graph[node][j] == -1) {
				dist[j][0] = min(dist[j][0], dist[node][trans] + trans == 1 ? 1 : 0);
			}
			else if (graph[node][j] == 1) {
				dist[j][1] = min(dist[j][1], dist[node][trans] + trans == 1 ? 0 : 1);
			}
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
	for (int i = 0; i < m; ++i) {
		int fst, snd;
		scanf("%d%d", &fst, &snd);
		graph[fst - 1][snd - 1] = 1;
		graph[snd - 1][fst - 1] = -1;
	}
	scanf("%d%d", &start, &end);
	dijkstra(start - 1, n);
	printf("%d", min(dist[end - 1][0], dist[end - 1][1]));
	return 0;
}