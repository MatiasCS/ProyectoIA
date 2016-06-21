#include <stdlib.h>
#include <time.h>
//for couts
//#include <iostream>
#include "trip.h"

//Setters
void trip::set_departure_hotel(int hotel_id){
	departure_hotel = hotel_id;
}

void trip::set_arrival_hotel(int hotel_id){
	arrival_hotel = hotel_id;
}

void trip::set_trip_max_length(float trip_length){
	trip_max_length = trip_length;
}

void trip::set_initial_poi(int N){
	srand (time(NULL));
	int pois_number = N-2;
	int rpoi = rand() % (pois_number);
	push_poi(rpoi);

}

void trip::set_trip_score(int total_score){
	trip_score = total_score;
}

void trip::set_trip_length(float trip_length){
	trip_max_length = trip_length;
}


//Getters
int trip::get_departure_hotel(){
	return departure_hotel;
}

int trip::get_arrival_hotel(){
	return arrival_hotel;
}

int trip::get_trip_score(){
	return trip_score;
}

float trip::get_trip_max_length(){
	return trip_max_length;
}

float trip::get_trip_length(){
	return trip_length;
}

vector<int> trip::get_poi_list(){
	return poi_list;
}

int trip::get_last_poi(){
	return poi_list.back();
}

//Other functions

void trip::push_poi(int poi_id){
	poi_list.push_back(poi_id);
}

void trip::clear_poi_list(){
	poi_list.clear();
}