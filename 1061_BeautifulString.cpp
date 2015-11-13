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

int main() {
	cin >> N;
	while (N--)
	{
		int len;
		string in_str;
		cin >> len;
		cin >> in_str;
		int *count = new int[len];
		int *c = new int[len];
		int index = 0;
		int begin =0;
		for(int i =0 ; i<len; ++i) {
			if(in_str[begin] != in_str[i]){
				//cout << index << in_str[i];
				c[index] = in_str[begin];
				count[index++] = i - begin;
				begin = i;
			}
		}

		c[index] = in_str[begin];
		count[index] = len - begin;

		int flag =0;
		for(int i =1; i<index; ++i) {
			//cout << c[i] << " " << count[i] << endl;
			if(c[i] +1 == c[i+1] && c[i] - 1 == c[i-1] && 
				(count[i-1] >= count[i] && count[i+1]  >= count[i])) {
					flag = 1;
					break;
			}
		}
		if(flag == 1) {
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}
	system("pause");
	return 0;

}

