#ifndef NNPF_H
#define NNPF_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;


inline double fRand(double fMin, double fMax)
{
	srand(time(0));
	double f = (double)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);
}

inline vector<int> flatten_int_array(vector<vector<int> > v){
	vector<int> new_v;
	new_v.resize(v.size()*v[0].size());
	for(int i=0;i<v.size();i++){
		for(int j=0;j<v[i].size();j++){
			new_v[i*v[i].size()+j]=v[i][j];
		}
	}
	return new_v;
}

inline vector<double> flatten_double_array(vector<vector<double> > v){
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
	public:
		vector<vector<double> > domain;
		Domain(int w, int h);
		Domain(int w, int h, int randChance);
		const int get_width(void);
		const int get_height(void);
		void set_loc_prop(int x,int y,double s);
		const int get_loc_prop(int x,int y);
		void clear_loc(int x, int y);
		void save_domain(string s);
		void load_domain(string s);
		const void print_domain(void);
		void set_zero(void);
		void reset_domain(int w,int h,int randChance);
};

class Neuron{
	vector<double> inputs;
	vector<double> weights;
	vector<double> weight_range, bias_range;
	double bias, output;
	public:
		Neuron(vector<double> in,vector<double> w, double b);
		Neuron(vector<double> in,vector<double> w,vector<double> b);
		const vector<double> get_inputs(void);
		void set_inputs(vector<double> in);
		const vector<double> get_weights(void);
		void set_weights(vector<double> w);
		const double get_bias(void);
		void set_bias(double b);
		const double get_output(void);
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
		Layer(vector<double> in,int neuron_num,vector<double> w_range,vector<double> b_range);
		void set_inputs(vector<double> in);
		const vector<double> get_outputs(void);
		void update_outputs(void);
		void mutate(void);
		void reset(void);
		const vector<vector<double> > get_genes(void);
};

class Network{
	vector<Layer> layers;
	vector<double> outputs, inputs;
	vector<double> weight_range, bias_range;
	public:
		Network(int layer_num,int hl_neuron_num,vector<double> in,vector<double> b_range,vector<double> w_range);
		void mutate(void);
		void reset(void);
		void set_inputs(vector<double> in);
		const vector<double> get_outputs(void);
		void update_network(void);
		const vector<vector<vector<double> > > get_genes(void);
		const int layer_num(void);  
};

class Seeker{
	double score, x, y;
	vector<double> input, outputs;
	vector<vector<double > > position;
	bool isDead;
	Network* network;
	public:
		Seeker(vector<vector<double> > domain);
		void update_network(void);
		void move_seeker(vector<vector<double> > domain);
		void check_collisions(vector<vector<double> > domain);
		void calc_score(int goal_x,int goal_y);
		void write_seeker(string filename);
		void read_seeker(string filename);
		void reset_position(double x, double y);
		void write_position(string filename);
		void reset_network(void);
		void mutate_network(void);
};

#endif
