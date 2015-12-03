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
const int MAX= 14 ;
const int MAX_N= 5e3 + 200;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

int edge[ MAX ];
int p[ 1<<MAX];
int cnt =0;

void dfs(int now, int unused) {
	if(! unused) {
		cnt += (edge[now] & 1);
		return ;
	}
	int rest = unused & edge[ now ];  
	while (rest)
	{
		int tp = rest & (-rest);
		dfs(p[ tp ], unused - tp);
		rest -= tp;
	}
	return ;
}


int main() {
	cin >> N >> M;
	// 0 potint to empty string
	for (int i =0; i< N; ++i) {
		p[ 1<<i ]  = i + 1;
	}
	while(M--) {
		int u, v;
		scanf("%d %d", &u, &v);
		edge[ u ] |= 1 << (v-1);
	}
	dfs(1, (1 << N)-2);
	cout << cnt << endl;

	system("pause");
	return 0;

}
