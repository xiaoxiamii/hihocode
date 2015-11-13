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
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;
struct edge{
	int to;
	int next;
	int weight;
}edge[MAX_M *2];

int head[MAX_N];
vector<bool> vis;
int cnt=1;

void addEdge(int u, int v, int val){
	edge[cnt].to = v;
	edge[cnt].weight = val;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

bool BFS(int power){
	vis.clear();
	vis.resize(N+1, false);
	queue<int> Q;
	Q.push(1);
	Q.push(-1);
	int u, v, len = 0;
	vis[1] = true;
	while(!Q.empty() && len < K){
		u = Q.front();
		//cout << "ad" << u << endl;
		Q.pop();
		if(u == -1){
			if(Q.empty()){
				return false;
			}
			else{
				len ++;
				Q.push(-1);
				continue;
			}
		}

		for(int i= head[u]; i!=0; i = edge[i].next){
			v = edge[i].to;
			if(!vis[v] && edge[i].weight <= power){
				if(v == T){
					return true;
				}
				vis[v] = true;
				Q.push(v);
			}
		}
	}
	return false;


}

int main (){
	cin >>N >> M >>K >>T;
	int low = 1e7+10, high = -1;
	for(int i=0; i<M;++i){
		int u,v,w;
		cin >> u >> v >> w;
		low = min(low, w);
		high = max(high, w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}

	while(low +1 < high){
		int mid = (high + low)/2;
		if(BFS(mid))
			high = mid;
		else
			low = mid;
	}
	cout << high << endl;

	system("pause");
	return 0;
	
}
