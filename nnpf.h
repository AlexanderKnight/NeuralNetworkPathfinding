#ifndef NNPF_H
#define NNPF_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

class Domain{
	int width, height;
	vector<vector<int>> domain;
	public:
		Domain(int w, int h);
		Domain(int w, int h, int randChance);
		const int get_width(void);
		const int get_height(void);
		void set_loc_prop(int x,int y,int s);
		const int get_loc_prop(int x,int y);
		void clear_loc(int x, int y);
		void save_domain(string s);
		void load_domain(string s);
		const void print_domain(void);
		void reset(void);
};

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
};

class Network{
	vector<Layer> layers;
	vector<double> outputs, inputs;
	vector<double> weight_range, bias_range;
	public:
		void mutate(void);
		void reset(void);
};

class Seeker{
	double score, x, y;
	Network network;
	vector<double> input, outputs;
};

#endif
