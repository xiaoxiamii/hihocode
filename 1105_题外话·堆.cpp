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
const int MAX_M = 1e4 + 10;

static int N, M, S, T;

class maxHeap {
public:
	//funtion:
	bool max_heap_insert(int v) {
		heap_size++;
		heap_arr[heap_size] =v;
		int i = heap_size;
		//shift up
		while(i > 1 && heap_arr[i/2] < heap_arr[i]) {
			swap(heap_arr[i/2], heap_arr[i]);
			i/=2;
		}
		return true;
	}

	//adjust max heap
	bool max_heap_adjust(int i) {
		int l = i*2, r = i*2 +1;
		int largest = i;
		if(l <= heap_size && heap_arr[l] > heap_arr[largest]) {
			largest = l;
		}
		if(r <= heap_size && heap_arr[r] > heap_arr[largest]){
			largest = r;
		}

		if(largest != i) {
			swap(heap_arr[largest], heap_arr[i]);
			max_heap_adjust(largest);
		}
		return true;
	}

	int max_heap_get_max(){
		int ans = heap_arr[1];
		heap_arr[1] = heap_arr[heap_size];
		heap_size --;
		max_heap_adjust(1);
		return ans;
	}
	int get_heap_size() {
		return heap_size;
	}


	//¹¹Ôìº¯Êý
	maxHeap(int _heap_size) {
		heap_size = _heap_size;
	};
	maxHeap(){
		heap_size = 0;
	};

private:
	int heap_size;
	int heap_arr[MAX_N];
};

int main (){
	while(cin >> N ){
		char op;
		int weight;
		maxHeap max_heap;
		while(N--){
			cin >> op;

			if(op == 'A'){
				cin >> weight;
				max_heap.max_heap_insert(weight);

			}
			else if(op == 'T'){
				cout << max_heap.max_heap_get_max() << endl;

			}
		}
	}
	
	system("pause");
	return 0;
	
}