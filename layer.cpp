#include "nnpf.h"
#include <vector>
using namespace std;

Layer::Layer(vector<double> in, vector<Neuron> neu){
	inputs = in;
	neurons = neu;
	outputs.resize(neurons.size());
	this->update_outputs();
}

Layer::Layer(vector<double> in, int neuron_num){
	inputs = in;
	neurons.resize(neuron_num);
	for (int i=0;i<neuron_num;i++){
		neurons[i]=Neuron(inputs);
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
