#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "trip.h"

trip::trip(){
	departure_hotel = -1;
	arrival_hotel = -1;
	trip_max_length = 0;
	trip_length = 0;
}

//Setters
void trip::set_departure_hotel(int hotel_id){
	this->departure_hotel = hotel_id;
}

void trip::set_arrival_hotel(int hotel_id){
	this->arrival_hotel = hotel_id;
}

void trip::set_trip_max_length(float trip_length){
	this->trip_max_length = trip_length;
}

void trip::set_trip_score(int total_score){
	this->trip_score = total_score;
}

void trip::set_trip_length(float trip_length){
	this->trip_length = trip_length;
}


//Getters
int trip::get_departure_hotel(){
	return this->departure_hotel;
}

int trip::get_arrival_hotel(){
	return this->arrival_hotel;
}

int trip::get_trip_score(){
	return this->trip_score;
}

float trip::get_trip_max_length(){
	return this->trip_max_length;
}

float trip::get_trip_length(){
	return this->trip_length;
}

vector<int> trip::get_poi_list(){
	return this->poi_list;
}

vector<float> trip::get_distances(){
	return this->distances;
}

int trip::get_last_poi(){
	return this->poi_list.back();
}

float trip::get_last_poi_distance(){
	return this->distances.back();
}

//Other functions

void trip::push_poi(int poi_id){
	this->poi_list.push_back(poi_id);
}

void trip::clear_poi_list(){
	this->poi_list.clear();
}

void trip::push_distance(float distance){
	this->distances.push_back(distance);
}

void trip::pop_last_poi(){
	this->distances.pop_back();
	this->poi_list.pop_back();
}

void trip::print_trip(){
	cout<<"Trip Generado:\t Score: "<<trip_score<<"\tLength: "<<trip_length<<'\n';
	for (int i = 0 ; i < (signed)poi_list.size(); i ++){
		if(i == 0)
			cout<<"h"<<departure_hotel<<"-p"<<poi_list[i];
		else if(i+1 == (signed)poi_list.size())
			cout<<"-p"<<poi_list[i]<<"-h"<<arrival_hotel<<"\n";
		else
			cout<<"-p"<<poi_list[i];
	}
}