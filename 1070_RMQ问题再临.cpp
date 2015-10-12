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
#include<limits>
#include<numeric>
#include<cstring>
#include<map>

using namespace std;
static int N, M, Q;
const int MAX_N = 10010;
int weight[MAX_N] ;

int main (){
	scanf("%d", &N);
	for(int i =0; i<N; ++i) 
	{
		scanf("%d", &weight[i]);
	}
	scanf("%d", &Q);
	int min_q;
	for(int i =0; i<Q; ++i) 
	{
		int act, begin, end;
		min_q = -1;
		scanf("%d %d %d", &act, &begin, &end);
		if(act == 1) 
		{
			weight[begin-1] = end;
		}
		else
		{
			for(int j = begin-1; j<=(end-1); ++j)
			{
				if(min_q != -1){
					min_q = min(min_q, weight[j]);
				}
				else{
					min_q = weight[j];
				}
			}
			cout << min_q << endl;
		}
	}
	
	//system("pause");
	return 0;
	
}