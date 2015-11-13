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
vector<int> arr;


int ltc(int left, int right,int k) {
	//cout << left << " " << right << endl;
	if(left > right)
		return 0;
	int l = left, r = right, mid = left + (right - left)/2;
	int p = arr[l];
	while(l < r){ 
		while(l  <r && arr[r]> p){
			r--;
		}
		arr[l] = arr[r];
		while(l < r && arr[l] < p){
			l++;
		}
		arr[r] = arr[l];
	}
	arr[l] = p;

	if(l == k){
		//cout << l << endl;
		return arr[l];
	}
	else if(l < k)
		return ltc(l+1, right,k);
	else
		return ltc(left, l-1, k);
}


int main (){
	cin >>N >> M;
	for(int i=0; i<N;++i){
		int a;
		cin >> a;
		arr.push_back(a);
	}
	if(M > N){
		printf("-1\n");
	}
	else{
		printf("%d\n", ltc(0,N-1, M-1));
	}



	
	system("pause");
	return 0;
	
}
