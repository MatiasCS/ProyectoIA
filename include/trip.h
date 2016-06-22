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
	vector<float> distances;
public:
	trip();

	//Setters
	void set_departure_hotel(int hotel_id);
	void set_arrival_hotel(int hotel_id);
	void set_trip_max_length(float trip_length);
	void set_trip_score(int total_score);
	void set_trip_length(float trip_length);
	void set_distances(vector<float> distances);
	void set_poi_list(vector<int> poi_list);
	
	//Getters
	int get_departure_hotel();
	int get_arrival_hotel();
	float get_trip_max_length();
	int get_trip_score();
	float get_trip_length();
	vector<int> get_poi_list();
	vector<float> get_distances();
	
	//Retrona el ultimo poi de la poi_list
	int get_last_poi();

	float get_last_poi_distance();

	//Annade un poi a la poi_list
	void push_poi(int poi_id);
	//Vacia la poi_list
	void clear_poi_list();

	void push_distance(float distance);

	void pop_last_poi();

	void print_trip();

	void  calculate_distance_dhotel_poi(vector< vector<int> >hotel_list, vector< vector<int> >poi_list);

	float sum_distances();

	void reset_distances(vector< vector<int> >hotel_list, vector< vector<int> >poi_list);

	void set_to_erase_poi(int poi_position);

	void erase_pois();
};

#endif