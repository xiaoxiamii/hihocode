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
const int MAX_N = 1e2 + 10;
const int MAX_M = 1e4 + 10;

static int N, M, S, T;
int graph[MAX_N][MAX_N] ={0};
int prev_node[MAX_N];
/*
functino find the minst path in a undirected or directed graph
*/
int Dijkstra(int start, int terminal) {
	//dist保存从start到 j的最短距离
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

		//对S集合外的节点，更新距离dist
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

/*
floyd
*/
void floyd(){
	for(int k=1; k<=N;++k){
		for(int i=1; i<=N;++i){
			for(int j=1; j<=N; ++j){
				graph[i][j] = min(graph[i][j],(graph[i][k]+graph[k][j]));
			}
		}
	}
}


int main (){
	scanf("%d %d", &N, &M);
	int u, v, len;
	for(int i =1; i<=N; ++i) {
		for(int j=1; j<=N;++j) {
			if(i !=j )
				graph[i][j] = 1e4+5;
		}
	}
	while(M--) {
		scanf("%d %d %d",&u, &v, &len);
		graph[u][v] = graph[u][v]<len?graph[u][v]:len;
		graph[v][u] = graph[u][v];
	}
	floyd();
	for(int i =1; i<=N; ++i) {
		for(int j=1; j<=N; ++j){
			printf("%d ",graph[i][j]);
		}
		printf("\n");
	}
	
	
	//system("pause");
	return 0;
	
}