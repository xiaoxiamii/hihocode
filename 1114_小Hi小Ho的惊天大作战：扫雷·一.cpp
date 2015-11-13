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
const int MAX_M = 1e6 + 10;
const int MAX_T = 1e5+10;

static int N, M, S, T;
int mine10[MAX_N];
int mine11[MAX_N];
int mine2[MAX_N];
int yes_id[MAX_N];
int no_id[MAX_N];

bool Sub(int x, int *mine1x){
	mine1x[0] = 0;
	mine1x[1] = x;
	for(int i=2;i<=N; ++i){
		mine1x[i] = mine2[i-1] - mine1x[i-1] - mine1x[i-2];
		//cout << mine1x[i] << endl;
		if(mine1x[i] != 0 && mine1x[i] != 1) {
			//cout <<"yi" << mine1x[i] << " " << i <<endl;
			return false;
		}
	}

	if(mine1x[N] + mine1x[N-1] != mine2[N]){
		//cout <<"er" << endl;
		return false;
	}
	return true;
}
void Solve(){
	bool ans0 = Sub(0, mine10);
	bool ans1 = Sub(1, mine11);
	//cout << "   "<<ans0 <<" " << ans1 << endl;
	int yes_num = 0, no_num =0;

	if(ans0 && !ans1){
		for(int i =1; i<= N;++i){
			if(mine10[i] == 1){
				yes_id[yes_num++] = i;
			}
			else{
				no_id[no_num++] = i;
			}
		}
	}

	else if(!ans0 && ans1) {
		for(int i =1; i<=N; ++i){
			if(mine11[i] == 1){
				yes_id[yes_num++] = i;
			}
			else{
				no_id[no_num++] =i;
			}
		}
	}
	else if(ans0 && ans1){
		for(int i=1; i<=N;++i){
			if(mine10[i] == mine11[i]){
				if(mine10[i] == 1){
					yes_id[yes_num++] = i;
				}
				else{
					no_id[no_num++] = i;
				}
			}
		}
	}

	printf("%d ", yes_num);
	for(int i =0; i< yes_num;++i){
		printf("%d ", yes_id[i]);
	}
	printf("\n");

	printf("%d ", no_num);
	for(int i=0;i<no_num;++i){
		printf("%d ", no_id[i]);
	}
	printf("\n");
}
int main (){
	cin >> M;
	while(M--){
		cin >> N;
		for(int i =1; i<=N;++i){
			cin >> mine2[i];
			//cout << mine2[i] << endl;
		}
		Solve();
	}
	
	system("pause");
	return 0;
	
}