#ifndef NNPF_H
#define NNPF_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Domain{
	int width, height;
	vector<vector<int>> domain;
	public:
		Domain(int w, int h);
		const int get_width(void);
		const int get_height(void);
		void set_loc_prop(int x,int y,int s);
		const int get_loc_prop(int x,int y);
};



#endif
