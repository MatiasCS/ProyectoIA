#ifndef TRIP_H
#define TRIP_H
#include <vector>
using namespace std;

class trip{
	int departure_hotel;
	int arrival_hotel;
	float trip_max_length;
	int trip_score;
	float trip_length;
	vector<int> poi_list;

public:
	//Setters
	void set_departure_hotel(int hotel_id);
	void set_arrival_hotel(int hotel_id);
	void set_trip_max_length(float trip_length);
	void set_initial_poi(int N);
	void set_trip_score(int total_score);
	void set_trip_length(float trip_length);
	
	//Getters
	int get_departure_hotel();
	int get_arrival_hotel();
	float get_trip_max_length();
	int get_trip_score();
	float get_trip_length();
	vector<int> get_poi_list();
	//Retrona el ultimo poi de la poi_list
	int get_last_poi();

	//Annade un poi a la poi_list
	void push_poi(int poi_id);
	//Vacia la poi_list
	void clear_poi_list();
};

#endif