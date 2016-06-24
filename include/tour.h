#ifndef TOUR_H
#define TOUR_H
#include "trip.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class tour{
	vector<trip> trips;
	float tmax;
	int number_of_trips;
	int total_score;

public:
	//Setters
	void set_trips(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, vector<float> td);
	void set_tmax(float tmax);
	void set_number_of_trips(int trips);
	void set_total_score();

	//Getters
	vector<trip> get_trips();
	float get_tmax();
	int get_number_of_trips();
	int get_total_score();
	trip get_trip(int trip_id);

	//Annade el trip t al final de la lista de trips
	void push_trip(trip t);
	//Retorna el id del hotel de llegada del ultimo trip
	int get_last_arrived_hotel();

	//Imprime el archivo con la solucion
	void print_tour(string file_name);
	
	//Setea la lista de trips con la lista trip entregada
	void reset_trips(vector<trip> trip);
};

#endif
