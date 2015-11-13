#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<stack>
#include<queue>
#include<limits.h>
#include<numeric>
#include<cstring>
#include<map>

using namespace std;
const int MAX_N = 1e3 + 10;
const int MAX_M = 1e4 + 10;

static int N, M, S, T;
int graph[MAX_N][MAX_N];
int prev_node[MAX_N];
/*
functino find the minst path in a undirected or directed graph
*/
int Dijkstra(int start, int terminal) {
	//dist�����start�� j����̾���
	bool mark[MAX_N];
	int dist[MAX_N];
	//init
	for(int i =1; i<= N; ++i) {
		dist[i] = graph[start][i];
		mark[i] = false;
		if(dist[i] == INT_MAX) {
			prev_node[i] = -1;
		}
		else {
			prev_node[i] = start;
		}
	}

	dist[start] = 0;
	mark[start] = true;
	for(int i =2; i<=N; ++i) {
		int min_dist = INT_MAX;
		int k = start;
		for(int j =1; j<=N;++j) {
			if(!mark[j] && dist[j] < min_dist) {
				k = j;
				min_dist = dist[j];
			}
		}

		if(k == terminal) {
			return min_dist;
		}
		mark[k] = true;

		//��S������Ľڵ㣬���¾���dist
		for(int j=1; j<=N; ++j){
			if((!mark[j]) && graph[k][j] < INT_MAX){
				if(dist[k] + graph[k][j] < dist[j]){
					dist[j] = dist[k] + graph[k][j];
					prev_node[j] = k;
				}
			}
		}

	}


}

int main (){
	scanf("%d %d %d %d", &N, &M, &S, &T);
	int u, v, len;
	for(int i =1; i<=N; ++i) {
		for(int j=1; j<=N;++j) {
			graph[i][j] = INT_MAX;
		}
	}
	while(M--) {
		scanf("%d %d %d",&u, &v, &len);
		graph[u][v] = graph[u][v] < len ? graph[u][v] : len;
		graph[v][u] = graph[u][v];
	}
	cout << Dijkstra(S,T) << endl;
	
	
	//system("pause");
	return 0;
	
}