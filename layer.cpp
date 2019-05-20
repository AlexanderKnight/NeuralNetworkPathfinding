#include <assert.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "nnpf.h"

/*	This class handles each layer of the neural network
	and allows the handling of the neurons without direct
	attention. 

	Layer creation is either with specific neurons, 
	or random creation, passing the number of neurons,
	and the allowed double ranges of biases and weights.
*/

Layer::Layer(vector<double> in, vector<Neuron> neu){
	inputs = in;
	neurons = neu;
	outputs.resize(neurons.size());
	this->update_outputs();
}

Layer::Layer(vector<double> in, int neuron_num,
		vector<double> w_range,
		vector<double> b_range){
	bias_range = b_range;
	weight_range = w_range;
	inputs = in;
	for (int i=0;i<neuron_num;i++){
		neurons.push_back(Neuron(inputs,bias_range,weight_range));
	}
	outputs.resize(neurons.size());
	this->update_outputs();
}

void Layer::set_inputs(vector<double> in){
	assert(inputs.size() == in.size());
	inputs = in;
}

const vector<double> Layer::get_outputs(void){
	return outputs;
}

void Layer::update_outputs(void){
	for (int i=0;i<neurons.size();i++){
		neurons[i].set_inputs(inputs);
		neurons[i].update_output();
		outputs[i] = neurons[i].get_output();
	}
}

void Layer::mutate(void){
	for (int i=0;i<neurons.size();i++){
		neurons[i].mutate();
	}
}

void Layer::reset(void){
	for(int i=0;i<neurons.size();i++){
		neurons[i].reset();
	}
}

const vector<vector<double>> Layer::get_genes(void){
	vector<vector<double>> layer_genes;
	for(int i=0;i<neurons.size();i++){
		layer_genes.push_back(neurons[i].get_genes());
	}
	return layer_genes;
}

void Layer::print_genes(void){
	for (int i=0;i<neurons.size();i++){
		cout << "Neuron " << i << endl;
		neurons[i].print_genes();
	}
}
