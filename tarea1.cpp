#include "utilities.h"
#include "trip.h"
#include "generator.h"
#include "tour.h"
#include "population.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

int main(int argc, char *argv[]){
	const string INSTANCES_PATH = "Instances/";

	if (argc < 3){
		cout<<"Por favor indique el set  y el nombre de la instancia a utilizar \n";
		cout<<"Ejemplo: ./tarea1 SET1 64-50-1-2.ophs \n";
	}

	else{
		string file = INSTANCES_PATH + argv[1] + '/' + argv[2];
		if(!instance_checker(file))
			error_message();
		
		else{
			srand (time(0));
			int* params = get_params(file);
  			float tmax = get_tmax(file);
  			vector<float> td = get_td(file);
  			vector< vector<int> > hotels = get_hotels(file, params[1]);
  			vector< vector<int> > pois = get_pois(file, params[0] ,params[1]);
  			vector<tour> population1 = generate_initial_population(10, hotels, pois, tmax, td);
  			vector<tour> population2 = generate_initial_population(50, hotels, pois, tmax, td);
  			//print_solutions(population1);
  			//migration(population1,population2);
  			tour offspring = crossover(population1[0], population1[1],hotels,pois);
  			//offspring.print_tour();
  		}
	}
}
