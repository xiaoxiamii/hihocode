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
const int MAX_N= 1e3 + 10;
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;

struct carInfo{
	int id;
	int in;
	int out;
	int speed;
	double time;
};
vector<carInfo> car;
map<int, carInfo> mapcar;


bool sortByCarIn(carInfo x, carInfo y){
	return x.in > y.in;
}

bool sortByCarOut(carInfo x, carInfo y) {
	return x.out < y.out;
}

bool sortByCarId(carInfo x, carInfo y) {
	return x.id < y.id;
}

int main() {
	cin >>N;
	for(int i= 0; i< N; ++i){
		carInfo info;
		cin >> info.in >> info.out >> info.speed;
		info.id = i;
		info.time =0;
		car.push_back(info);
	}
	vector<carInfo> p = car;
	//out Y small to large
	sort(p.begin(), p.end(), sortByCarOut);
	//in X large to small

	sort(car.begin(), car.end(), sortByCarIn);
	for(int i =0; i <N; ++i) {
		int nowPos = car[i].in;
		double t = 0;

		for(int j=0; j<N; ++j) {
			if(p[j].out > car[i].in) {
				t += double((p[j].out - nowPos) / double(car[i].speed));
				t = max(p[j].time, t);
				p[j].time = t;
				nowPos = p[j].out;
				if(p[j].out == car[i].out) {
					car[i].time = t;
					break;
				}
			}
		}
	}

	sort(car.begin(), car.end(), sortByCarId);

	for(int i =0 ; i<N; ++i) {
		printf("%.2f\n" , car[i].time);
	}



	system("pause");
	return 0;

}
