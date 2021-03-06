#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include "nnpf.h"

Seeker::Seeker(vector<vector<double> > in){
	score = 0.;
	x = 2.;
	y = 2.;
	vector<double> w_range = {-10.,10.};
	vector<double> b_range = {-5.,5.};
	vector<double> new_position {x,y};
	position.push_back(new_position);
	input = flatten_double_array(in);
	input.push_back(x);
	input.push_back(y);
	network = new Network(4,15,input, w_range,b_range);
	isDead = false;
	this->update_network();
}

void Seeker::update_network(void){
	network->set_inputs(input);
	network->update_network();
	outputs = network->get_outputs();
}

void Seeker::move_seeker(vector<vector<double> > domain){
	if (!isDead){
		update_network();
		if (outputs.at(0)==0. and outputs.at(1)==0. and outputs.at(2)==0. and outputs.at(3)==0.){
			outputs.at(0)=1;
			outputs.at(2)=1;
		}
		double absXY = 2.*sqrt(pow(outputs.at(0)-outputs.at(1),2)+pow(outputs.at(2)-outputs.at(3),2));
		x += (outputs.at(0)-outputs.at(1))/absXY;
		y += (outputs.at(2)-outputs.at(3))/absXY;
		input.at(input.size()-2) = x;
		input.at(input.size()-1) = y;
		if (domain.at((int)x).at((int)y)==3.){
			isDead = true;
		}
	}
	vector<double> new_position {x,y};
	position.push_back(new_position);
}

void Seeker::check_collisions(vector<vector<double> > domain){
	if (domain.at((int) x).at((int) y)==1.){
		isDead = true;
	}
}

void Seeker::calc_score(int goal_x,int goal_y){
	score += 1./(pow((double)goal_x-x,2)+pow((double) goal_y-y,2));
}

void Seeker::write_seeker(string filename){
	ofstream seeker_file;
	seeker_file.open(filename);
	seeker_file.write((char*)this, sizeof(this));
	seeker_file.close();
}

void Seeker::read_seeker(string filename){
	ifstream seeker_file;
	seeker_file.open(filename);
	seeker_file.read((char*)this, sizeof(this));
	seeker_file.close();
}

void Seeker::reset_position(double xx, double yy){
	input.at(input.size()-2)=xx;
	x = xx;
	input.at(input.size()-1)=yy;
	y = yy;
	isDead = false;
}

void Seeker::write_position(string filename){
	ofstream pos_file(filename, ios::out | ios::app);
	for(int i=0;i<position.size();i++){
		pos_file << position.at(i).at(0) << " " << position.at(i).at(1) << endl;
	}
	pos_file.close();
}

void Seeker::write_each_position(string filename){
	ofstream pos_file(filename, ios::out | ios::app);
	pos_file << position.at(position.size()-1).at(0) << " " << position.at(position.size()-1).at(1) << endl;
	pos_file.close();
}

void Seeker::reset_network(void){
	network->reset();
}

void Seeker::mutate_network(void){
	network->mutate();
}

void Seeker::print_genes(void){
	network->print_genes();
}

const double Seeker::get_score(void){
	return score;
}

