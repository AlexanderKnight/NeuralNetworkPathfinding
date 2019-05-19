#include <iostream>
#include <vector>
using namespace std;

#include "nnpf.h"

int main(){
	int width = 20;
	int height = 20;
	int randChance = 25;
	string domain_savefile = "20x20rand30.dat";
	Domain domain (width,height,randChance);
	cout << "Seekers will start at top left corner and aim for bottom right corner.\n Walls are 1's and open space are 0's.\n Please ensure that there is a path between the start and finish" << endl;
	domain.print_domain();
	bool map_is_good = false;
	string user_input;
	while (!map_is_good){
		cout << "Is the map solvable? [Y/N]" << endl;
		cin >> user_input;
		if (user_input == "Y"){
			map_is_good=true;
		}
		else if (user_input == "N"){
			domain.reset_domain(width,height,randChance);
			domain.print_domain();
		}
		else{
			cout << "Please type Y or N" << endl;
		}
	}
	domain.save_domain(domain_savefile);
}




