#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "nnpf.h"

/* The Neuron is the basis of the network, taking in input,
   scaling it by a weight, add up each input*weight, and then
   adding a bias, to finally get the output. 

   The output is scaled with ReLU (Rectified Linear Unit) or
   max(output, 0.).

   There are two constructors, depending on if the Neurons are 
   created before, or randomly when this is created
*/

Neuron::Neuron(vector<double> in, vector<double> w, double b){
	bias = b;
	assert(in.size()==w.size());
	inputs = in;
	weights = w;
	output=0.;
	for (int i=0;i<inputs.size();i++){
		output += inputs.at(i)*weights.at(i);
	}
	output += bias;
}

Neuron::Neuron(vector<double> in, 
		vector<double> w_range, 
		vector<double> b_range){
	weight_range = w_range;
	bias_range = b_range;
	bias = fRand(b_range.at(0),b_range.at(1));
	inputs = in;
	weights.resize(inputs.size());
	output=0.;
	for (int i=0;i<inputs.size();i++){
		weights.at(i) = fRand(w_range.at(0),w_range.at(1));
		output += inputs.at(i)*weights.at(i);
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

const vector<double> Neuron::get_genes(void){
	vector<double> genes(weights);
	genes.push_back(bias);
	return genes;
}

const double Neuron::get_output(void){
	return output;
}

void Neuron::update_output(void){
	output=0.;
	for (int i=0;i<inputs.size();i++){
		output += inputs.at(i)*weights.at(i);
	}
	output += bias;
	if (output <0.){
		output = 0.;
	}
	
}

void Neuron::mutate(void){
	for (int i=0; i<weights.size();i++){
		weights.at(i) *= 1+fRand(-0.05,0.05);
	}
	bias *= 1+fRand(-0.05,0.05);
}

void Neuron::reset(void){
	for (int i=0;i<weights.size();i++){
		weights.at(i) = fRand(weight_range.at(0),weight_range.at(1));
	}
	bias = fRand(bias_range.at(0),bias_range.at(1));
}

void Neuron::print_genes(void){
	cout << "Weights are : ";
	for (int i=0;i<weights.size();i++){
		cout << weights.at(i) << ", ";
	}
	cout << endl;
	cout << "Bias is " << bias << endl;
}
