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
const int MAX_N = 1e5 + 10;
const int MAX_M = 1e6 + 10;

static int N, M, S, T;
struct edge{
	int to;
	int weight;
	int next;
} edge[MAX_M];

int used_mark[MAX_N] ={0} ;
int start_dist[MAX_N] = {MAX_M};
int head[MAX_N] = {0};
int prev_node[MAX_N];
int cnt;

/*
SPFA
*/
int spfa(int start, int terminal) {
	used_mark[start] = 1;
	for(int i =1; i<=N; ++i) {
		start_dist[i] = MAX_M;
	}
	start_dist[start] = 0;
	queue<int> Q;
	Q.push(start);
	int q;
	while(! Q.empty()) {
		q = Q.front();
		Q.pop();
		used_mark[q] = 0;
		//qµÄº¢×Ó
		for(int i = head[q]; i != 0 ; i = edge[i].next) {
			int u = edge[i].to;
			if(start_dist[q] + edge[i].weight < start_dist[u]) {
				start_dist[u] = start_dist[q] + edge[i].weight;
				if( used_mark[u] == 0) {
					used_mark[u] = 1;
					Q.push(u);
				}
			}
		}
	}
	return start_dist[terminal];

}

void add_edge(int u, int v, int value) {
	edge[cnt].to = v;
	edge[cnt].weight = value;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

int main (){
	scanf("%d %d %d %d", &N, &M, &S, &T);
	int u, v, len;
	while(M--) {
		scanf("%d %d %d",&u, &v, &len);
		add_edge(u, v, len);
		add_edge(v, u, len);
	}
	cout << spfa(S, T) << endl;
	
	
	system("pause");
	return 0;
	
}