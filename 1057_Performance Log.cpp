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
const int MAX_N = 2e5 + 10;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

struct fun{
	string name;
	string time;
	string status;
	long long difftime;
}F[MAX_N];

struct mytime{
	int hour;
	int min;
	int sec;
};

int timeToInt(string time) {
	int t[3];
	int index =0;
	int begin = 0;
	for(int i =0; i<time.size(); ++i) {
		if(time[i] == ':'){
			//const char* tmp = time.substr(begin, i-begin).c_str();
			//t[index ++] = atoi(tmp);
			t[index ++] = atoi(time.substr(begin, time.size()).c_str());
			begin = i+1;
		}
	}
	t[index ] = atoi(time.substr(begin, time.size()).c_str());
	mytime ret;
	long long count = 0;
	count = t[0]* 60 * 60 + t[1] * 60 + t[2];
	return count;


};

long long  time_cmp(string time1, string time2) {
	long long  t1 = timeToInt(time1);
	long long t2 = timeToInt(time2);

	return (t1 - t2);
	
};

int main() {
	cin >>N ;
	getchar();
	stack <fun> sta;
	vector<fun> outputlist;
	for(int i =0; i<N; ++i) {
		cin >> F[i].name;
		cin >> F[i].time;
		cin >> F[i].status;
	}
	for(int i =0; i < N; ++i) {

		if(i != 0){
			int difftime = time_cmp(F[i].time, F[i-1].time);
			if(difftime < 0) {
				cout <<"Incorrect performance log" << endl;
				return 0;
			}
		}
		if(F[i].status == "START"){
			sta.push(F[i]);
			outputlist.push_back(F[i]);
		}
		else {
			if(sta.empty()|| sta.top().name != F[i].name) {
				cout <<"Incorrect performance log" << endl;
				return 0;
			}
			fun top = sta.top();
			sta.pop();
			int difftime = time_cmp(F[i].time, top.time);
			if(difftime < 0){
				cout <<"Incorrect performance log" << endl;
				return 0;
			}
			for(int j =0; j<outputlist.size(); ++j) {
				if(outputlist[j].name == F[i].name){
					outputlist[j].difftime = difftime;
					break;
				}
			}
		}

	}
	if(!sta.empty()) {
		cout <<"Incorrect performance log" << endl;
		return 0;

	}
	for(int i =0; i< outputlist.size(); ++i) {
		int diff = outputlist[i].difftime;
		int s = diff %60; diff /=60;
		int m = diff %60; diff /=60;
		int h = diff ;
		//printf("%s %02d:%02d:%02d\n", outputlist[i].name, h ,m ,s);
		cout << outputlist[i].name;
		printf(" %02d:%02d:%02d\n", h ,m ,s);

	}

	
	//system("pause");
	return 0;

}

