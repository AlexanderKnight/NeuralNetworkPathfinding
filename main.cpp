#include <string>
#include <vector>
#include <iostream>
#include <mpi.h>
using namespace std;

#include "nnpf.h"

int main(int argc, char **argv){
	string load_domain_filename = "20x20rand30.dat";
	int seeker_num = 8;
	int runtime = 100;


	Domain domain (1,1);
	domain.load_domain("20x20rand30.dat");
	domain.print_domain();

	MPI_Init(&argc, &argv);

	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	

	vector<Seeker> seekers;
	for(int i=0;i<(seeker_num/size);i++){
		seekers.push_back(Seeker(domain.domain));
	}

	for(int time=0;time<runtime;time++){
		for(int i=0;i<seekers.size();i++){
			seekers[i].move_seeker(domain.domain);
			seekers[i].check_collisions(domain.domain);
			seekers[i].calc_score(18,18);
			string pos_filename = "PositionalData/pos_proc%i_seek%i.dat",100*rank,i
			seekers[i].write_position(pos_filename);
		}
	}

	string filename;
	for(int i=0;i<seekers.size();i++){
		filename = "SeekerData/SeekerPos_Core%i_Seeker%i.dat",rank,i;
		seekers[i].write_position(filename);
	}


	MPI_Finalize();
	
}
