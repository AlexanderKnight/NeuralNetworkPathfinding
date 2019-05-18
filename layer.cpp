#include "nnpf.h"
#include <vector>
using namespace std;


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
		vector<double> b_range,
		vector<double> w_range){
	bias_range = b_range;
	weight_range = w_range;
	inputs = in;
	neurons.resize(neuron_num);
	for (int i=0;i<neuron_num;i++){
		neurons[i]=Neuron(inputs,bias_range,weight_range);
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
		neuron[i].set_inputs(inputs);
		neuron[i].update_output();
		outputs[i] = neuron[i].get_output();
	}
}

void Layer::mutate(void){
	for (int i=0;i<neurons.size();i++){
		neuron[i].mutate()
	}
}

void Layer::reset(void){
	for(int i=0;i<neurons.size;i++){
		neurons[i].reset();
	}
}

const vector<vector<double>> get_genes(void){
	vector<vector<double>> layer_genes;
	for(int i=0;i<neurons.size();i++){
		layer_genes.push_back(neurons[i].get_genes());
	}
	return layer_genes;
}
