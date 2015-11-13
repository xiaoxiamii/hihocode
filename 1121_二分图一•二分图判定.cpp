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
const int MAX_N = 1e4 + 10;
const int MAX_M = 4e4 + 10;
const int MAX_T = 1e5+10;

static int N, M, S, T;

struct edge{
	int to;
	int next;
	int val;
}edge[MAX_M*2];

int head[MAX_N];
int color[MAX_N];
int cnt;


void addEdge(int u, int v) {
	edge[cnt].to =  v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

bool BFS(int start){
	color[start] = 1;
	queue<int> q;
	q.push(start);
	while( !q.empty()) {
		int cur = q.front();
		q.pop();
		for(int k = head[cur]; k!= 0; k = edge[k].next){
			if(color[edge[k].to] == -1){
				color[edge[k].to] = 1 - color[cur];
				q.push(edge[k].to);
			}
			else {
				if(color[edge[k].to] + color[cur] != 1){
					return false;
				}
			}

		}
	}
	return true;
}

bool check(){
	for(int i=1;i<=N;++i){
		if(color[i] == -1){
			if(!BFS(i)){
				return false;
			}
		}
	}
	return true;
}
int main (){
	cin>> T;
	while(T--){
		cin>> N >> M;
		memset(color , -1 , sizeof(color));
		memset(head, 0, sizeof(head));
		memset(edge, 0, sizeof(edge));
		cnt = 0;
		int u, v;
		for(int i =1; i<=M;++i){
			cin >> u >> v;
			addEdge(u, v);
			addEdge(v, u);
		}
		if(check()){
			cout << "Correct" << endl;
		}
		else {
			cout << "Wrong" << endl;
		}
		

	}
	
	system("pause");
	return 0;
	
}