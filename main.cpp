#include <string>
#include <vector>
#include <iostream>
#include <mpi>
using namespace std;

#include "nnpf.h"
#include "dom.h"

int main(){
	string load_domain_filename = "20x20rand30.dat";
	int seeker_num = 100;
	int runtime = 100;


	Domain domain (1,1);
	domain.load_domain("20x20rand30.dat");
	domain.print_domain();

	MPI_Init();

	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	vector<Seeker> seekers (seeker_num/size);
	for(int i=0;i<seekers.size();i++){
		seekers[i] = Seeker(domain);
	}

	for(int time=0;time<runtime;time++){
		for(int i=0;i<seekers.size();i++){
			seekers[i].move_seeker();
		}
	}

	}





	MPI_Finalize();
	
}
