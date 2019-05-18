
#ifndef DOM_H
#define DOM_H
#include <vector>
#include <string>
using namespace std;

class Domain{
	int width, height;
	vector<vector<int>> domain;
	public:
		Domain(int w, int h);
		Domain(int w, int h, int randChance);
		const int get_width(void);
		const int get_height(void);
		void set_loc_prop(int x,int y,int s);
		const int get_loc_prop(int x,int y);
		void clear_loc(int x, int y);
		void save_domain(string s);
		void load_domain(string s);
		const void print_domain(void);
		void set_zero(void);
		void reset_domain(int w,int h,int randChance);
};

#endif
