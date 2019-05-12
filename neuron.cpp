#include <iostream>
#include <string>
#include <vector>
#include <assert>
using namespace std;

Neuron::Neuron(vector<double> in, vector<double> w, double b){
	bias = b;
	assert(in.size()==w.size());
	inputs = in;
	weights = w;
	output=0.;
	for (int i=0;i<inputs.size();i++){
		output += inputs[i]*weights[i];
	}
	output += bias;
}

Neuron::Neuron(vector<double> in){
	bias = fRand(-10.,10.);
	inputs = in;
	weights.resize(inputs.size());
	output=0.;
	for (int i=0;i<inputs.size();i++){
		weights[i] = fRand(-5.,5.);
		output += inputs[i]*weights[i];
	}
	output += bias;
}

const vector<double> Neuron::get_inputs(void){
	return inputs;
}
void Neuron::set_inputs(vector<double> in){
	assert(in.size()==weights.size());
	inputs = in;
}

const vector<double> Neuron::get_weights(void){
	return weights;
}

void Neuron::set_weights(vector<double> w){
	assert(w.size()==inputs.size());
	weights = w;
}

const double Neuron::get_bias(void){
	return bias;
}

void Neuron::set_bias(double b){
	bias = b;
}

const double Neuron::get_ouput(void){
	return output;
}

void Neuron::update_output(void){
	output=0.;
	for (int i=0;i<inputs.size();i++){
		output += inputs[i]*weights[i];
	}
	output += bias;
	if (output <0.){
		output = 0.;
	}
	
}



