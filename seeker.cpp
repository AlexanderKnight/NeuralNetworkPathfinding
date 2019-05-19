#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

Seeker::Seeker(vector<vector<int>> in){
	score = 0.;
	x = 2.;
	y = 2.;
	vector<vector<double>> position;
	position.push_back(vector<double> {x,y});
	vector<vector<double>> inp(in.begin(), in.end());
	input = flatten_int_array(inp);
	input.push_back(x);
	input.push_back(y);
	Network network = new Network(4,15,input, fRand(-10.,10.),fRand(-5.,5.));
	isDead = false;
}

void Seeker::update_network(void){
	network.set_inputs(input);
	network.update_network();
	outputs = network.get_outputs();
}

void Seeker::move_seeker(vector<vector<int>> domain){
	if not (isDead){
		this->update_network();
		double absXY = sqrt(pow(outputs[0]-outputs[1],2)+pow(outputs[2]-outputs[3],2));
		x += (outputs[0]-outputs[1])/absXY;
		y += (outputs[2]-outputs[3])/absXY;
		input[input.size()-2] = x;
		input[input.size()-1] = y;
		position.push_back(vector<double> {x,y});
		if (domain[(int)x][(int)y]==3){
			isDead = true;
		}
	}
}

void Seeker::check_collision(vector<vector<int>> domain){
	if (domain[(int) x][(int) y]==1){
		isDead = true;
	}
}

void Seeker::calc_score(int goal_x,int goal_y){
	score += 1./(pow((double)goal_x-x,2)+pow((double) goal_y-y),2);

void Seeker::write_seeker(string filename){
	ofstream seeker_file(filename);
	seeker_file.write((char *) & Seeker, sizeof(Seeker));
	seeker_file.close();
}

void Seeker::read_seeker(string filename){
	ifstream seeker_file(filename);
	seeker_file.read((char *) & Seeker; sizeof(Seeker));
}

void Seeker::write_position(string filename){
	ofstream pos_file(filename);
	for(int i=0;i<position.size();i++){
		pos_file << position[i][0] << " " << position[i][1] << endl;
	}
	pos_file.close();
}

	


