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
		domain.at(i).resize(height);
		for (int j=0;j<height;j++){
			domain.at(i).at(j)=0.;
		}
	}
}

Domain::Domain (int w, int h, int randChance){
	width = w;
	height = h;
	domain.resize(width);
	for (int i=0;i<width;i++){
		domain.at(i).resize(height);
		for (int j=0;j<height;j++){
			domain.at(i).at(j)=0.;
		}
	}
	srand(time(0));
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			if ((rand()%100+1)<randChance){
				domain.at(i).at(j) = 1.;
			}
		}
	}
	this->clear_loc(2,2);
	this->clear_loc(width-2,height-2);
	for (int i=0;i<width;i++){
		domain.at(i).at(0) = 1.;
		domain.at(i).at(height-1) =1.;
	}
	for (int j=0;j<height;j++){
		domain.at(0).at(j) = 1.;
		domain.at(width-1).at(j) = 1.;
	}
	domain.at(1).at(1) = 2;
	domain.at(width-2).at(height-2) = 3.;
}

const int Domain::get_width(void){
	return width;
}

const int Domain::get_height(void){
	return height;
}

void Domain::set_loc_prop(int x,int y,double s){
	domain.at(x).at(y) = s;
}

const int Domain::get_loc_prop(int x,int y){
	return domain.at(x).at(y);
}

void Domain::set_zero(void){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			domain.at(i).at(j)=0.;
		}
	}
}

void Domain::reset_domain(int w, int h, int randChance){
	this->set_zero();
	width = w;
	height = h;
	domain.resize(width);
	for (int i=0;i<width;i++){
		domain.at(i).resize(height);
		for (int j=0;j<height;j++){
			domain.at(i).at(j)=0.;
		}
	}
	srand(time(0));
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			if ((rand()%100+1)<randChance){
				domain.at(i).at(j) = 1.;
			}
		}
	}
	this->clear_loc(2,2);
	this->clear_loc(width-2,height-2);
	for (int i=0;i<width;i++){
		domain.at(i).at(0) = 1.;
		domain.at(i).at(height-1) =1.;
	}
	for (int j=0;j<height;j++){
		domain.at(0).at(j) = 1;
		domain.at(width-1).at(j) = 1.;
	}

	domain.at(1).at(1) = 2;
	domain.at(width-2).at(height-2) = 3.;
}


void Domain::clear_loc(int x,int y){
	domain.at(x-1).at(y-1) = 0.;
	domain.at(x).at(y-1) = 0.;
	domain.at(x-1).at(y) = 0.;
	domain.at(x).at(y) = 0.;
}

void Domain::save_domain(string filename){
	ofstream outfile(filename);
	outfile << width << endl << height << endl;
	for (int i=0;i<width;i++){
		for (int j=0;j<height;j++){
			outfile << domain.at(i).at(j) << " ";
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
		domain.at(i).resize(height);
		for(int j=0;j<height;j++){
			infile >> domain.at(i).at(j);
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


/*int main(){
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
	double a = 15.5;
	cout << (int) a/1 << endl;
}*/
