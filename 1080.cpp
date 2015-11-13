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
static int N, M, Q;
int weight[MAX_N] ;
struct seg_tree_node
{
	int left;
	int right;
	int val; // value
	int addMark; // lazy mark;
	int setval;
} seg_tree[MAX_N*4];

/*
function:
*/
int seg_tree_opterator(int val1, int val2) {
	return val1 + val2;
	//return min(val1, val2);
}
/*
function: build segment tree, begin from zero;
root : index of root in current segment tree 
arr: arrary to build segment tree;
istart: the begin of arr;
iend: the end of arr;
*/
void seg_tree_build(int root, int arr[], int istart, int iend) {

	seg_tree[root].addMark = 0;
	seg_tree[root].setval = -1;
	seg_tree[root].
	if( istart == iend ) { // leaf node
		seg_tree[root].val = arr[istart];
	}
	else {
		int mid = istart + (iend - istart) / 2;
		//build left and right
		seg_tree_build(root*2 +1, arr, istart, mid);
		seg_tree_build(root*2 +2, arr, mid+1, iend);
		//update the val;
		seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
	}
}

/*
function: spread mark to child node
root: index of current segment tree
*/
void seg_tree_push_down(int root, int nstart, int nend) {
	//叶子节点返回
	if(nend == nstart) {
		return ;
	}
	int mid = nstart + (nend - nstart) /2;

	if(seg_tree[root].setval != -1 ) {
		//标志域可以根据题目的需求修改相关的值。
		seg_tree[root*2 +1].setval = seg_tree[root].setval;
		seg_tree[root*2 +2].setval =seg_tree[root].setval;

		seg_tree[root*2+1].addMark = seg_tree[root*2+2].addMark = 0;

		seg_tree[root*2 +1].val = seg_tree[root].setval * (mid - nstart +1);
		seg_tree[root*2 +2].val = seg_tree[root].setval * (nend - mid);

		seg_tree[root].setval = -1;
	}
	if(seg_tree[root].addMark != 0) {

		//懒惰标记下方
		seg_tree[root*2 +1].addMark += seg_tree[root].addMark;
		seg_tree[root*2 +2].addMark += seg_tree[root].addMark;

		//重新计算子节点维护的值
		seg_tree[root*2 +1].val += seg_tree[root].addMark * (mid - nstart +1);
		seg_tree[root*2 +2].val += seg_tree[root].addMark * (nend - mid);

		//移除
		seg_tree[root].addMark = 0;

	}

}
/*
function: query section in segment tree;
root: index of root in current segment tree;
[nstart, nend]: section of current node;
[qstart, qend]: section of query;
*/

int seg_tree_query(int root, int nstart, int nend, int qstart, int qend) {
	//whether has the intersection
	if(qstart > nend || qend < nstart) {
		return 0;
	}

	//whether the node section was included in query section
	if(qstart <= nstart && qend >= nend) {
		return seg_tree[root].val;
	}
	seg_tree_push_down(root, nstart, nend);

	//query left and query right, return the min num of query result;
	int mid = nstart + (nend - nstart) /2;
	int ret1 = seg_tree_query(root*2+1, nstart, mid, qstart, qend);
	int ret2 = seg_tree_query(root*2+2, mid+1, nend, qstart, qend);

	if(ret1 == 0) 
		return ret2;
	if(ret2 == 0)
		return ret1;
	//return min;
	//return min(ret1, ret2);
	return seg_tree_opterator(ret1, ret2);
}

/*
function:update the leaf node in segment tree;
root:  the index of current segment tree;
[nstart, nend]: the section of current node;
index: the index of update node in arr;
addval: (curVal + addVal)
*/

void seg_tree_update_one(int root, int nstart, int nend, int index, int addval){

	if(index == nstart && nstart == nend){
		//seg_tree[root].val += addval;
		seg_tree[root].val = addval;
		return;
	}

	int mid = nstart + (nend - nstart)/2;
	if(index <=mid)
		seg_tree_update_one(root*2+1, nstart, mid, index ,addval);
	else
		seg_tree_update_one(root*2+2, mid+1, nend, index, addval);

	//seg_tree[root].val = min(seg_tree[root*2+1].val, seg_tree[root*2 +2].val);
	seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
}
/*
function: update the section of segment tree;
root:index;
[nstart, nend]: the section of current root;
[ustart, uend]: section waiting to update
addVal: update value;
*/
void seg_tree_update_section(int root, int nstart, int nend, int ustart, int uend, int addVal, int op) {

	if(ustart > nend || uend < nstart) {
		return ;
	}

	if(ustart <= nstart && uend >= nend) {
		if(op == 0) {
			seg_tree[root].val += (nend -nstart + 1) * addVal;
			seg_tree[root].addMark += addVal;
		}
		else if(op == 1){
			seg_tree[root].val = (nend - nstart +1)*addVal;
			seg_tree[root].setval = addVal;
			seg_tree[root].addMark = 0;
		}
		return;
	}

	seg_tree_push_down(root, nstart, nend);

	int mid = nstart + (nend - nstart) / 2;
	seg_tree_update_section(root*2+1, nstart, mid, ustart, uend, addVal,op);
	seg_tree_update_section(root*2+2, mid+1, nend, ustart, uend, addVal, op);

	//
	seg_tree[root].val = seg_tree_opterator(seg_tree[root*2+1].val, seg_tree[root*2+2].val);
	//seg_tree[root].val = (seg_tree[root*2 +1].val + seg_tree[root*2+2].val);
}


int main (){
	scanf("%d %d", &N, &Q);
	for(int i =0; i<N; ++i) 
	{
		scanf("%d", &weight[i]);
	}
	seg_tree_build(0, weight, 0, N);

	for(int i =0; i<Q; ++i) 
	{
		int act, left, right, newp;
		scanf("%d %d %d %d", &act, &left, &right, &newp);
		int ret = seg_tree_query(0, 0, N, left-1, right-1);
		printf("%d\n", ret);
		//cout << seg_tree[0].val;
		//seg_tree_update_section(0, 0, N, left -1, right -1, newp,act);
	}
	
	system("pause");
	return 0;
	
}