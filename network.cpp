#include <vector>
#include "nnpf.h"
using namespace std;

Network::Network(int layer_num, int hl_neuron_num, 
		vector<double> in,
		vector<double> b_range, vector<double> w_range){

		
	bias_range = b_range;
	weight_range = w_range;
	inputs = in;
	layers.resize(layer_num)
	for (int i=0;i<layer_num-1;i++){
		if (i==0){
			layers[i] = Layer(inputs, hl_neuron_num, bias_range, weight_range);
		}
		else{
			layers[i] = Layer(layers[i-1],hl_neuron_num,bias_range,weight_range);
		}
	}
	layers[layer_num-1] = Layer(layers[layer_num-2],4,bias_range,weight_range);
	outputs = layers[layer_num-1].get_outputs();
}

void Network::set_inputs(vector<double> in){
	inputs = in;
}

const vector<double> Network::get_outputs(void){
	return outputs;
}

void Network::update_network(void){
	for (int i=0;i<layer_num;i++){
		if(i==0){
			layer[i].set_inputs(inputs);
			layer[i].update_outputs();
		}
		else{
			layer[i].set_inputs(layer[i-1].get_outputs);
			layer[i].update_outputs();
		}
	}
	outputs = layer[layer.size()-1].get_outputs();
}

void Network::mutate(void){
	for (int i=0;i<layers.size();i++){
		layers[i].mutate();
	}
}

void Network::reset(void)
	for (int i=0;i<layers.size();i++){
		layers[i].reset();
	}
}
