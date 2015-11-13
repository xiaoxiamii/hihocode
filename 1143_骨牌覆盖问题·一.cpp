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
#define eps 1e-8
#define LL long long
const LL mod=19999997;
const int MIN= -1e3;
const int MAX= 1e3;
const int MAX_N = 1e5 + 10;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static LL N, M, K, T;

struct matrlc {
	LL mapp[2][2];
}ans, base;

matrlc unit = {1, 0, 0, 1};
matrlc mult(matrlc a, matrlc b){
	matrlc c;
	for(int i=0; i<2; ++i){
		for(int j=0; j<2; ++j){
			c.mapp[i][j] = 0;
			for(int k=0; k<2; ++k){
				c.mapp[i][j] = (c.mapp[i][j] + (a.mapp[i][k] * b.mapp[k][j])%mod) %mod;
			}
			c.mapp[i][j] %=mod;
		}
	}
	return c;
}

LL pow(LL n){
	base.mapp[1][1] = 0;
	base.mapp[0][0] = base.mapp[1][0] = base.mapp[0][1] = 1;
	ans.mapp[0][0] = ans.mapp[1][1] = 1;
	ans.mapp[1][0] =ans.mapp[0][1] =0;
	while(n){
		if(n&1) {
			ans =mult(ans, base);
		}
		base = mult(base, base);
		n>>=1;
	}
	return ans.mapp[0][1]%mod;
}


int main () {
	scanf("%lld", &N);
	cout << pow(N+1) << endl;
	system("pause");
	return 0;
	
}
