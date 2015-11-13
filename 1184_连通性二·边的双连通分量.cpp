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
const int MAX_N = 1e5 + 10;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

int head[MAX_N];
struct edge{
	int to;
	int next;
	int val;
}edge[MAX_M*2];

int cnt = 1;
static int counter = 0;
int vis[MAX_N];
int dfn[MAX_N];
int low[MAX_N];
stack <int> group;
int num_group =0 ;

set<int> vertex;
vector< pair<int, int> > ans_edge;
int ans[MAX_N];


bool cmp(pair<int, int> a , pair<int, int> b ){
	if(a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}

void addEdge(int u, int v){
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

void tarjan(int u, int father){
	dfn[u] = low[u] = ++counter;
	int children = 0;
	group.push(u);
	for(int i = head[u]; i != 0; i = edge[i].next){
		int v = edge[i].to;
		if(v == father) {
			continue;
		}
		if(! dfn[v]){
			children ++;
			tarjan(v, u);
			low[u] = min(low[u], low[v]);

			if((father == u && children > 1) || 
				(father != u && low[v] >= dfn[u])){
			//根结点， 并且子树多余1
			//非根结点，子树的祖先不大于u，即必没有子树指向u的祖先节点
				vertex.insert(u);
			}

			if(low[v] > dfn[u]){
				ans_edge.push_back(make_pair(min(v, u), max(v,u)));
			}
		}
		else {
			low[u] = min(low[u], dfn[v]);
		}
	}

	vector<int> tmp;
	if(low[u] == dfn[u]) {
		while ( ! group.empty())
		{
			int front = group.top();
			group.pop();
			if(front == u){
				tmp.push_back(front);
				break;
			}
			else {
				tmp.push_back(front);
			}
		}
	}
	if(tmp.size() != 0){
		num_group ++;
		int minst = INT_MAX;
		for(int i =0; i<tmp.size() ; ++i){
			minst = min(minst, tmp[i]);
		}
		for(int i =0 ; i<tmp.size();++i){
			ans[tmp[i]] = minst;
		}
	}

}

int main () {
	cin >> N >> M;

	for(int i =0; i<M; ++i){
		int u, v;
		cin >> u >> v;
		addEdge(u, v);
		addEdge(v, u);
	}

	tarjan(1,1);

	/*
	sort(ans_edge.begin(), ans_edge.end(), cmp);
	if(vertex.size() == 0) cout <<"Null" << endl;
	else{
		auto it = vertex.begin();
		for(; it != vertex.end(); ++it){
			printf("%d ", *it);
		}
		printf("\n");
	}
	for(int i =0; i<ans_edge.size(); ++i){
		printf("%d %d\n", ans_edge[i].first, ans_edge[i].second);
	}
	*/

	cout << num_group << endl;
	for(int i =1; i<=N; ++i){
		printf("%d ", ans[i]);
	}
	cout << endl;


	system("pause");
	return 0;
	
}
