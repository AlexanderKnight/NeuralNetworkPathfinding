#include <string>
#include <vector>
#include <iostream>
#include <mpi.h>

using namespace std;

#include "nnpf.h"

int main(int argc, char **argv){

	MPI_Init(&argc, &argv);

	string load_domain_filename = "20x20rand25.dat";
	int seeker_num = 50;
	int runtime = 100;
	int iterations = 200;
	int gridx = 20;
	int gridy = 20;



	Domain domain (1,1);
	domain.load_domain("20x20rand25.dat");
	//domain.print_domain();


	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	

	vector<Seeker> seekers;
	for(int i=0;i<(seeker_num/size);i++){
		seekers.push_back(Seeker(domain.domain));
	}
	for (int iter=0;iter<iterations;iter++){
		cout << "Time " << iter << " of " << iterations << endl;

		string pos_filename;
		for(int time=0;time<runtime;time++){
			for(int i=0;i<seekers.size();i++){
				seekers[i].move_seeker(domain.domain);
				seekers[i].check_collisions(domain.domain);
				seekers[i].calc_score(gridx-2,gridy-2);
				pos_filename = "PositionalData/pos_procseeker"+to_string(1000*rank+i)+"_Iter"+to_string(iter)+".dat";
				seekers[i].write_each_position(pos_filename);
			}
		string filename;
		}

		/*for (int i=0;i<seekers.size();i++){
			pos_filename = "PositionalData/pos_procseeker"+to_string(1000*rank+i)+"_Iter"+to_string(iter)+".dat";
			seekers[i].write_position(pos_filename);
		}*/
		string filename;
		for(int i=0;i<seekers.size();i++){
			filename = "SeekerData/SeekerPos_Core"+to_string(rank)+"_Seeker"+to_string(i)+".dat";
			seekers[i].write_seeker(filename);
		}

		if(rank != 0){
			double message[4];
			for (int i=0;i<seekers.size();i++){
				/*vector<double> message;
				message.push_back(seekers.at(i).get_score());
				message.push_back((double) rank);
				message.push_back((double) i);
				message.push_back(0.); // flag to mutate or reset, will be changed by 0 proc*/
				
				message[0] = seekers.at(i).get_score();
				message[1] = (double) rank;
				message[2] = (double) i;
				message[3] = 0.;
				int flag = 1000*rank+i;
				MPI_Send(&message,4,MPI_DOUBLE,0,flag,MPI_COMM_WORLD);

			}
		}
		else if (rank == 0){
			double messages[seeker_num][4];
			double message[4];
			//vector<vector<double>> messages;
			//vector<double> message;
			for (int i=0;i<seekers.size();i++){
				/*message.push_back(seekers[i].get_score());
				message.push_back((double) rank);
				message.push_back((double) i);
				message.push_back(0.);
				messages.push_back(message);*/
				message[0] = seekers.at(i).get_score();
				message[1] = (double) rank;
				message[2] = (double) i;
				message[3] = 0.;
				for (int j=0;j<4;j++){
					messages[i][j] = message[j];
				}

			}
			for(int core=1;core<size;core++){
				for(int seeker=0;seeker<seeker_num/size;seeker++){
					MPI_Recv(&message,4,MPI_DOUBLE,core,1000*core+seeker,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				//	messages.push_back(message);
					for (int j=0;j<4;j++){
						messages[core*(seeker_num/size)+seeker][j] = message[j];
					}
				}
			}
			vector<vector<double> >  to_sort;
			for (int i=0;i<seeker_num;i++){
				to_sort.push_back(vector<double>());
				for(int j=0;j<4;j++){
					to_sort.at(i).push_back(messages[i][j]);
				}
			}

			sort(to_sort.begin(),to_sort.end(), 
				[](const vector<double>&a,const vector<double>&b)
					{return a[0]<b[0];});
			for (int i=((int)(0.2*to_sort.size()));
					i<((int)(0.8*to_sort.size()));i++){
				to_sort[i][3] = 1.;
			}
			for (int i=((int)(0.8*to_sort.size()));i<to_sort.size();i++){
				to_sort[i][3] = 2.;
			}
			for (int i=0;i<seeker_num;i++){
				for (int j=0;j<4;j++){
					messages[i][j] = to_sort.at(i).at(j);
				}
			}
			for (int i=0;i<seeker_num;i++){
				if (messages[i][1]==0.){
					if(messages[i][3]==1.){
						seekers[(int)messages[i][1]].mutate_network();
					}
					else if(messages[i][3]==2.){
						seekers[(int)messages[i][1]].reset_network();
					}
				}
				else{
					int send_rank = (int) messages[i][1];
					int send_flag = (int) (1000.*messages[i][1]+messages[i][2]);
					MPI_Send(&messages[i],4,MPI_DOUBLE,send_rank,send_flag,MPI_COMM_WORLD);
				}
			}
		}
		if(rank != 0){
			double message[4];
			for(int i=0;i<seekers.size();i++){
				MPI_Recv(&message,4,MPI_DOUBLE,0,1000*rank+i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				if(message[3]==1.){
					seekers.at(i).mutate_network();
				}
				else if(message[3]==2.){
					seekers.at(i).reset_network();
				}
			}
		}
		for (int i=0;i<seekers.size();i++){
			seekers.at(i).reset_position(2.,2.);
		}
	}

	
	MPI_Finalize();
	
}
