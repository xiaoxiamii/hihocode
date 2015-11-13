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
const int MAX_M = 1e4 + 10;

static int N, M, S, T;

struct edge {
	int u, v, w;
	edge(int _u, int _v, int _w):u(_u), v(_v), w(_w) {};
	bool operator<(const edge &x) const {
		return w < x.w;

	}
};

vector<edge> e;

struct unionFindSet {
	int st[MAX_N];
	void init(){
		for(int i =1; i<=N; ++i) st[i] = i;
	}
	int findSet(int x) {
		if(x == st[x]) return x;
		return st[x] = findSet(st[x]);
	}
	void unionSet(int x, int y) {
		int sx = findSet(x), sy = findSet(y);
		st[sx] = sy;
	}

}ufs;

int kruscal() {
	sort(e.begin(), e.end());
	int ans = 0 ;
	ufs.init();
	for(int i =0; i<e.size() ; ++i) {
		int su = ufs.findSet(e[i].u), sv = ufs.findSet(e[i].v);
		if(su != sv){
			ufs.unionSet(su, sv);
			ans+=e[i].w;
		}
	}
	return ans;
}

int main (){
	while(cin >> N >> M){
		e.clear();
		while(M--){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			e.push_back(edge(u,v,w));
		}
		cout << kruscal() << endl;
	}
	
	system("pause");
	return 0;
	
}