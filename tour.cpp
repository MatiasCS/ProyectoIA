#include "trip.h"
#include <vector>
#include "generator.h"
#include "tour.h"
#include <iostream>
using namespace std;

//Setters
void tour::set_tmax(float tmax){
	this->tmax = tmax;
}
void tour::set_number_of_trips(int trips){
	this->number_of_trips = trips;
}

//Getters
vector<trip> tour::get_trips(){
	return this->trips;
}
float tour::get_tmax(){
	return this->tmax;
}
int tour::get_number_of_trips(){
	return this->number_of_trips;
}

void tour::push_trip(trip t){
		trips.push_back(t);
}

int tour::get_last_arrived_hotel(){
	int last_hotel = trips.back().get_arrival_hotel();
	return last_hotel;
}

void  tour::set_trips(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, vector<float> td){
	int visited_pois[(signed) poi_list.size()];
	for (int i;i < (signed)poi_list.size();i++)
  		visited_pois[i] = 0;
	for (int i = 0 ; i < (signed) td.size(); i++){
		if(i == 0){
			trip t;
			t.set_departure_hotel(0);
			t.set_trip_max_length(td[i]);
			build_trip(hotel_list,poi_list, t, 0, visited_pois);
			push_trip(t);
		}
		else if(i + 1== (signed) td.size()){
			trip t;
			t.set_departure_hotel(get_last_arrived_hotel());
			t.set_trip_max_length(td[i]);
			build_trip(hotel_list, poi_list, t, 1, visited_pois);
			t.set_arrival_hotel(1);
			push_trip(t);
		}
		else{
			trip t;
			t.set_departure_hotel(get_last_arrived_hotel());
			t.set_trip_max_length(td[i]);
			build_trip(hotel_list,poi_list, t, 0, visited_pois);
			push_trip(t);
		}
	}
	set_total_score();
}

void tour::print_tour(string file_name){
	cout<<"Mejor solucion encontrada con score "<<total_score<<"\n";
	cout<<"Escribiendo archivo de salida...\n";
	ofstream file;
	string file_path = "Solutions/" + file_name;
	file.open(file_path.c_str());
	file<<tmax<<"\n";
	file.close();
	for(int i= 0; i < (signed)trips.size(); i++){
		trips[i].print_trip(file_name,  tmax);
	}

	file.close();
}

void tour::set_total_score(){
	int score = 0;
	for (int i = 0; i < (signed) trips.size(); i++)
		score += trips[i].get_trip_score();

	this->total_score = score;
}

int tour::get_total_score(){
	return this->total_score;
}

trip tour::get_trip(int trip_id){
	return this->trips[trip_id];
}

void tour::reset_trips(vector<trip> trip_list){
	this->trips = trip_list;
}