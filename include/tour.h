#ifndef TOUR_H
#define TOUR_H
#include "trip.h"
#include <vector>
using namespace std;

class tour{
	vector<trip> trips;
	float tmax;
	int number_of_trips;
	int total_score;

public:
	//Setters
	void  set_trips(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, vector<float> td);
	void set_tmax(float tmax);
	void set_number_of_trips(int trips);
	void set_total_score();

	//Getters
	vector<trip> get_trips();
	float get_tmax();
	int get_number_of_trips();
	int get_total_score();

	void push_trip(trip t);

	int get_last_arrived_hotel();

	void print_tour();
};

#endif