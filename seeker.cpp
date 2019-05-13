#include <vector>
using namespace std;

Seeker::Seeker(vector<double> in){
	x = 2.;
	y = 2.;
	input = in;
	input.push_back(x);
	input.push_back(y);
	Network network = new Network(4,15,input, fRand(-10.,10.),fRand(-5.,5.));
	isDead = false;
}

void Seeker::update_network(void){
	network.update_network();
	outputs = network.get_outputs();
}

void Seeker::move_seeker(void){
	double absXY = sqrt(pow(outputs[0]-outputs[1],2)+pow(outputs[2]-outputs[3],2));
	x += (outputs[0]-outputs[1])/absXY;
	y += (outputs[2]-outputs[3])/absXY;
}

void Seeker::check_collision(Domain domain){
	if (domain[x/1][y/1]==1){
		isDead = true;
	}
}


