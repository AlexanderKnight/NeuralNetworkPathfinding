#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "nnpf.h"

Network::Network(int layer_num, int hl_neuron_num, 
		vector<double> in,
		vector<double> w_range, vector<double> b_range){

		
	bias_range = b_range;
	weight_range = w_range;
	inputs = in;
	for (int i=0;i<layer_num-1;i++){
		if (i==0){
			Layer temp_layer(inputs,hl_neuron_num,weight_range,bias_range);
			layers.push_back(temp_layer);
		}
		else{
			Layer temp_layer(layers[i-1].get_outputs(),hl_neuron_num,weight_range,bias_range);
			layers.push_back(temp_layer);
		}
	}
	layers.push_back(Layer(layers[layer_num-2].get_outputs(),4,bias_range,weight_range));
	outputs = layers[layer_num-1].get_outputs();
}

void Network::set_inputs(vector<double> in){
	inputs = in;
}

const vector<double> Network::get_outputs(void){
	return outputs;
}

void Network::update_network(void){
	for (int i=0;i<layers.size();i++){
		if(i==0){
			layers[i].set_inputs(inputs);
			layers[i].update_outputs();
		}
		else{
			layers[i].set_inputs(layers[i-1].get_outputs());
			layers[i].update_outputs();
		}
	}
	outputs = layers[layers.size()-1].get_outputs();
}

void Network::mutate(void){
	for (int i=0;i<layers.size();i++){
		layers[i].mutate();
	}
	this->update_network();
}

void Network::reset(void){
	for (int i=0;i<layers.size();i++){
		layers[i].reset();
	}
	this->update_network();
}

const vector<vector<vector<double>>> Network::get_genes(void){
	vector<vector<vector<double>>> network_genes;
	for(int i=0;i<layers.size();i++){
		network_genes.push_back(layers[i].get_genes());
	}
	return network_genes;
}

void Network::print_genes(void){
	for (int i=0;i<layers.size();i++){
		cout << "Layer " << i << endl;
		layers[i].print_genes();
	}
}
