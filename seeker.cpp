#include <vector>
using namespace std;

Seeker::Seeker(vector<double> in){
	score = 0.;
	x = 2.;
	y = 2.;
	vector<vector<double>> position;
	position.push_back(vector<double> {x,y})
	input = flatten_int_array(in);
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

void Seeker::move_seeker(void){
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

void Seeker::check_collision(Domain domain){
	if (domain[(int) x][(int) y]==1){
		isDead = true;
	}
}

void Seeker::calc_score(int goal_x,int goal_y){
	score += 1./(pow((double)goal_x-x,2)+pow((double) goal_y-y),2);


