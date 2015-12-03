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

struct row {
	int childId;
	int expandLength;
	row(): childId(-1), expandLength(0) {};
	row(int _id):childId(_id), expandLength(0) {};
};

struct section {
	vector< row > rows;
	int selfLength;
	int expandLength;
	int delta;
	section(): selfLength(0), expandLength(0), delta(0) {};
};

struct panel
{
	vector< section > sections;
	vector< int > rowIds;
};

panel panels[ MAX_N ];

void dealPanel(panel &p) {
	if( (int)p.rowIds.size() == 0) return;

	p.sections.push_back(section());
	int sectionId = 0;

	p.rowIds.push_back(0);

	//deal with every section
	for(int i =0; i!=(int)p.rowIds.size();++i) {
		if(p.rowIds[i] !=0) {
			p.sections[ sectionId ].rows.push_back( row(p.rowIds[i]));
		}
		else {
			p.sections.push_back(section());
			sectionId++;
		}
	}
	return;
}

bool sortByExpandLength(row x, row y) {
	return x.expandLength >  y.expandLength;
}

bool sortByDelta(section x, section y) {
	return x.delta > y.delta;
}

int getExpandLength(panel &p) {
	int ret =0;

	for (int i=0; i !=(int) p.sections.size(); ++i) {
		//row  menu
		for(int j=0; j!=(int)p.sections[i].rows.size();++j) {
			p.sections[i].rows[j].expandLength = getExpandLength( panels[ p.sections[i].rows[j].childId]);
		}
		sort(p.sections[i].rows.begin(), p.sections[i].rows.end(), sortByExpandLength);

		p.sections[i].selfLength = (int) p.sections[i].rows.size();
		p.sections[i].expandLength = p.sections[i].selfLength;

		//
		for (int j=0; j != (int)p.sections[i].rows.size();++j) {
			if(p.sections[i].expandLength < j+ p.sections[i].rows[i].expandLength) {
				p.sections[i].expandLength = j+ p.sections[i].rows[i].expandLength;
			}
		}
		p.sections[i].delta = p.sections[i].expandLength - p.sections[i].selfLength;

		ret += p.sections[i].selfLength;
	}

	sort(p.sections.begin(), p.sections.end(), sortByDelta);

	int now = 0;

	for(int i=0; i!=(int) p.sections.size(); ++i) {
		if (ret < now + p.sections[i].expandLength) {
			ret = now + p.sections[i].expandLength;
		}
		now += p.sections[i].selfLength;
	}
	return ret;
}

int main() {
	cin >>N;
	int id, numOfIds;
	for (int i = 0; i<= N; ++i) {
		cin >> numOfIds;
		while (numOfIds--) {
			cin >> id;
			if( id == 0) {
				++numOfIds;
			}
			panels[i].rowIds.push_back(id);
		}
		dealPanel( panels[i]);
	}
	cout << getExpandLength( panels[0]) << endl;


	system("pause");
	return 0;

}
