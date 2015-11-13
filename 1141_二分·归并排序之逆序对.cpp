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
const int MAX_M = 1e5 + 10;
const int MAX_K = 1e4+10;

static int N, M, K, T;
vector<int> arr;

long long merge(vector<int>:: iterator beginIt, int num) {
	if(num < 2) {
		return 0;
	}

	int mid = num/2;

	int indexFirst = 0;
	int indexSecond = mid;

	vector<int> arr_tmp;
	long long count = 0;
	int index =0;
	while( (indexFirst < mid) && (indexSecond < num)) {
		int tmpFirst = *(beginIt + indexFirst);
		int tmpSecond = *(beginIt + indexSecond);

		if(tmpFirst > tmpSecond) {
			arr_tmp.push_back(tmpSecond);
			count += indexSecond - index;
			indexSecond++;
			index++;
		}
		else {
			arr_tmp.push_back(tmpFirst);
			indexFirst++;
			index++;
		}
	}

	while(indexFirst < mid) {
		arr_tmp.push_back(*(beginIt + indexFirst++));
	}
	while(indexSecond < num){
		arr_tmp.push_back(*(beginIt + indexSecond++));
	}

	for(int i =0 ; i<num;++i){
		*(beginIt++) = arr_tmp[i];
	}
	return count;

}

long long mergeSort(vector<int>::iterator beginIt, int num){
	if (num < 2) {
		return 0;
	}

	int mid = num/2;
	long long count =0 ;

	count += mergeSort(beginIt, mid);
	count += mergeSort(beginIt + mid, num - mid);
	count += merge(beginIt, num);

	return count;
}
int main (){
	cin >>N ;
	int index =0 ;
	while(index ++ < N){
		int tmp = 0;
		cin >> tmp;
		arr.push_back(tmp);
	}
	cout << mergeSort(arr.begin(), N) << endl;


	system("pause");
	return 0;
	
}
