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

map <string ,int> lastvisit;


int main() {
	cin >> N >> M;
	int s = 1, cacheNum = 0;
	vector<string> str_in;
	// 0 potint to empty string
	str_in.push_back("");
	for(int i = 1; i<=N; ++i) {
		string in;
		cin >> in;
		str_in.push_back(in);
	}


	for(int i =1; i<=N; ++i) {
		int index = lastvisit[ str_in[i] ];
		if(  index != 0 && index >=s && index <=i) {
			cout << "Cache" << endl;
		}
		//in cache
		// update cache
		else {
			//update
			cacheNum += 1;
			if(cacheNum > M) {
				// full
				s ++;
				cacheNum --;
			}
			cout <<"Internet" << endl;
		}
		lastvisit[ str_in[i] ] = i;
		while(lastvisit[ str_in[s]] != s) {
			s ++;
		}
	} 

	system("pause");
	return 0;

}
