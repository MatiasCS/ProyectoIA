#include "utilities.h"
#include "trip.h"
#include "evo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
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
			int* params = get_params(file);
  			float tmax = get_tmax(file);
  			vector<float> td = get_td(file);
  			vector< vector<int> > hotels = get_hotels(file, params[1]);
  			vector< vector<int> > pois = get_pois(file, params[0] ,params[1]);
  			trip trip1;
  			trip1.set_trip_max_length(td[0]);
  			trip1.set_departure_hotel(0);
  			build_trip(hotels,pois, trip1);
  			cout<<trip1.get_trip_length();
  		}
	}
}
