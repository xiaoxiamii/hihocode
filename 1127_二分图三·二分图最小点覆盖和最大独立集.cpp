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
const int MAX_M = 5e3 + 10;
const int MAX_T = 1e5+10;

static int N, M, S, T;

struct edge{
	int to;
	int next;
	int val;
}edge[MAX_M*2];

int head[MAX_N];
int mark[MAX_N];
int martch[MAX_N];
int cnt;



void addEdge(int u, int v) {
	edge[cnt].to =  v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}


int findPath(int u) {
	for(int i =head[u]; i!=0; i=edge[i].next){
		if(mark[edge[i].to] == 0){
			mark[edge[i].to] = 1;
			if(martch[edge[i].to] == 0 ||  findPath(martch[edge[i].to])){
				martch[edge[i].to] = u;
				//cout << " " << u <<" " << edge[i].to << endl;
				return 1;
			}
		}
	}
	return 0;

}

int visClear(){
	int res = 0;
	for(int i =1; i<=N;++i){
		for(int j =0; j<=N; ++j){
			mark[j] = 0;
		}
		res +=findPath(i);
	}
	return res/2;
}

int main (){
	cin >>N >> M;
	while(M--){
		int u,v;
		cin >> u >>v;
		addEdge(u, v);
		addEdge(v, u);
	}
	int res = visClear();
	cout << res << endl;
	cout << (N-res) << endl;

	
	system("pause");
	return 0;
	
}