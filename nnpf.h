#ifndef NNPF_H
#define NNPF_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "dom.h"

double fRand(double fMin, double fMax)
{
	    double f = (double)rand() / RAND_MAX;
	        return fMin + f * (fMax - fMin);
}

vector<int> flatten_int_array(vector<vector<int>> v){
	vector<int> new_v;
	new_v.resize(v.size()*v[0].size());
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v[i].size();j++){
			new_v[i*v[i].size()+j]=v[i][j];
		}
	}
	return new_v;
}

vector<double> flatten_double_array(vector<vector<double>> v){
	vector<double> new_v;
	new_v.resize(v.size()*v[0].size());
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v[i].size();j++){
			new_v[i*v[i].size()+j]=v[i][j];
		}
	}
	return new_v;
}


class Neuron{
	vector<double> inputs;
	vector<double> weights;
	vector<double> weight_range, bias_range;
	double bias, output;
	public:
		Neuron(vector<double> in,vector<double> w,double b);
		Neuron(vector<double> in);
		const vector<double> get_inputs(void);
		void set_inputs(vector<double> in);
		const vector<double> get_weights(void);
		void set_weights(vector<double> w);
		const double get_bias(void);
		void set_bias(double b);
		double get_output(void);
		void update_output(void);
		void mutate(void);
		void reset(void);
		const vector<double> get_genes(void);
};

class Layer{
	vector<Neuron> neurons;
	vector<double> outputs, inputs;
	vector<double> weight_range, bias_range;
	public:
		Layer(vector<double> in, vector<Neuron> neu);
		Layer(vector<double> in, int neuron_num);
		void set_inputs(vector<double> in);
		const vector<double> get_outputs(void);
		void update_outputs(void);
		void mutate(void);
		void reset(void);
		const vector<vector<double>> get_genes(void);
};

class Network{
	vector<Layer> layers;
	vector<double> outputs, inputs;
	vector<double> weight_range, bias_range;
	public:
		void mutate(void);
		void reset(void);
		void set_inputs(vector<double> in);
		void update_network(void);
		const vector<vector<vector<double>>> get_genes(void);
		const int layer_num(void);  
};

class Seeker{
	double score, x, y;
	Network network;
	vector<double> input, outputs;
	public:
		Seeker(vector<vector<int>> domain);
		void update_nework(void);
		void move_seeker(void);
		void check_collisions(Domain domain);
		void calc_score(int goal_x,int goal_y);
		void write_seeker(string filename);
		void read_seeker(string filename);
		void write_position(string filename);
};

#endif
