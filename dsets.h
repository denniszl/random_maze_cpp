/*
This is the header file for the class DisjointSets.
*/
#ifndef _DISJOINTSETS_H_
#define _DISJOINTSETS_H_

#include "png.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <iostream>

using namespace std;
using std::vector;
//using std::stack;
using std::string;
using std::ostream;
using std::cout;
using std::endl;
using std::pair;

class DisjointSets
{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);
	
	private:
//		bool isBigger(int rootA, int rootB) const;
		vector<int> dset;
};

#endif
