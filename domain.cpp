#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "nnpf.h"
using namespace std;

/*
	The domain class is build to create and handle the
	domain that the seekers (creatures) will travel through.
	It will create blockades randomly, and is adjustable in size.

	The value of the 2D matrix elements tell if the space is open or not.
	A value of 0 = space is open.
	Value of 1 = space is blocked.
*/
Domain::Domain (int w, int h){
	width = w;
	height = h;
	domain.resize(width);
	for (int i=0;i<width;i++){
		domain[i].resize(height);
		for (int j=0;j<height;j++){
			domain[i][j]=0;
		}
	}
}

const int Domain::get_width(void){
	return width;
}

const int Domain::get_height(void){
	return height;
}

void Domain::set_loc_prop(int x,int y,int s){
	domain[x][y] = s;
}

const int Domain::get_loc_prop(int x,int y){
	return domain[x][y];
}

/*int main(){
	srand(time(0));
	cout << "Random number is : " << rand() % 100+1 << endl;
	int wid = 10;
	int hei = 10;
	Domain domain (wid,hei);
	for (int i=0;i<wid;i++){
		for (int j=0;j<hei;j++){
			cout << domain.get_loc_prop(i,j) << " ";
		}
		cout << endl;
	}
	for (int i=0;i<wid;i++){
		for (int j=0;j<hei;j++){
			if ((rand()%100+1)<30){
				domain.set_loc_prop(i,j,1);
			}
		}
	}
	cout << endl;
	for (int i=0;i<wid;i++){
		for (int j=0;j<hei;j++){
			cout << domain.get_loc_prop(i,j) << " ";
		}
		cout << endl;
	}
}*/
