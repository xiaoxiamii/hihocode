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
#include<set>

using namespace std;
#define eps 1e-8
#define LL long long
const LL mod=12357;
const int MIN= -1e3;
const int MAX= 128 ;
const int MAX_N= 5e3 + 200;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;


struct edge{
	int to;
	int weight;
	int next;
}edge[MAX_M];

int head[MAX_N];
int cnt = 1;
bool vis[MAX_N];
int path_num =0;

void DFS(int now, int path[], int len, int vis_num) {
	vis[ now ] =  true;
	vis_num++;
	if(vis_num ==  N) {
		for(int i = head[now]; i!=0; i = edge[i].next) {
			int v = edge[i].to;
			if(v == 1) {
				path[len] = 1;
				/*
				for(int i=1; i<=N;++i) {
					cout << path[i] << endl;
				}
				*/

				path_num++;
				break;
			}
		}
	}
	else {
		for(int i = head[now]; i!=0 ; i= edge[i].next) {
			int v = edge[i].to;
			//cout <<"now" << now << "next" << v << "len"<<len <<endl;
			if(vis[ v ] == false) {
				path[len] = v;
				DFS(v, path, len+1, vis_num);
			}
		}
	}
	vis[now] = false;
	return;
}

void addEdge(int u, int v, int value) {
	edge[cnt].to =v;
	edge[cnt].weight = value;
	edge[cnt].next = head[u];
	head[u] = cnt++;
	return;
}



int main() {
	cin >> N >> M;
	// 0 potint to empty string
	while(M--) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u,v,0);
	}
	int *path = new int[N+2];
	DFS(1, path, 1, 0);
	
	
	cout << path_num << endl;


	delete path;
	system("pause");
	return 0;

}
