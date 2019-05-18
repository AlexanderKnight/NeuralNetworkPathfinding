#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

#include "nnpf.h"

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

Domain::Domain (int w, int h, int randChance){
	width = w;
	height = h;
	domain.resize(width);
	for (int i=0;i<width;i++){
		domain[i].resize(height);
		for (int j=0;j<height;j++){
			domain[i][j]=0;
		}
	}
	srand(time(0));
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			if ((rand()%100+1)<randChance){
				domain[i][j] = 1;
			}
		}
	}
	this->clear_loc(2,2);
	this->clear_loc(width-2,height-2);
	for (int i=0;i<width;i++){
		domain[i][0] = 1;
		domain[i][height-1] =1;
	}
	for (int j=0;j<height;j++){
		domain[0][j] = 1;
		domain[width-1][j] = 1;
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

void Domain::reset(void){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			domain[i][j]=0;
		}
	}
}

void Domain::clear_loc(int x,int y){
	domain[x-1][y-1] = 0;
	domain[x][y-1] = 0;
	domain[x-1][y] = 0;
	domain[x][y] = 0;
}

void Domain::save_domain(string filename){
	ofstream outfile(filename);
	outfile << width << endl << height << endl;
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			outfile << domain[i][j] << " ";
		}
		outfile << endl;
	}
	outfile.close();
}

void Domain::load_domain(string filename){
	ifstream infile(filename);
	infile >> width;
	infile >> height;
	domain.resize(width);
	for(int i=0;i<width;i++){
		domain[i].resize(height);
		for(int j=0;j<height;j++){
			infile >> domain[i][j];
		}
	}
	infile.close();
}

const void Domain::print_domain(void){
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			cout << this->get_loc_prop(i,j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}



int main(){
	srand(time(0));
	cout << "Random number is : " << rand() % 100+1 << endl;
	int wid = 10;
	int hei = 10;
	int randChance = 30;
	Domain domain (wid,hei,randChance);
	domain.print_domain();
	//domain.save_domain("TestDomain.txt");
	domain.load_domain("TestDomain.txt");
	domain.print_domain();
}
