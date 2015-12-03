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
const int MAX_N= 2e3 + 200;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

int dp[MAX_N][MAX_N] ;
int f[MAX_N][MAX_N] ;

int main() {
	string strA;
	string strB;

	cin >> strA;
	cin >> strB;
	strA.insert(strA.begin(), '#');
	strB.insert(strB.begin(), '*');

	//cout << strA[1] << endl;
	for(int i =1; i<strA.size(); ++i) {
		for(int j =1; j< strB.size(); ++j) {
			if(strA[i] == strB[j]) {
				f[i][j] = f[i-1][j-1] +1;
			}
			else{
				f[i][j] =0;
			}
		}
	}
	
	for(int i =1; i <strA.size(); ++i) {
		for(int j =1; j < strB.size(); ++j){ 
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if(f[i][j] >= 3) {
				for(int k =3; k<=f[i][j]; ++k){
					dp[i][j] = max(dp[i][j], dp[i-k][j-k]+k);
				}
			}
		}
	}
	cout << dp[strA.size()-1][strB.size()-1]<< endl;
	system("pause");
	return 0;

}

