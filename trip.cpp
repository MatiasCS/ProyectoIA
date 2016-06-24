#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "trip.h"
#include "utilities.h"

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

void trip::set_distances(vector<float> distances){
	this->distances = distances;
}

void trip::set_poi_list(vector<int> poi_list){
	this->poi_list = poi_list;
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

void trip::print_trip(string file_name, float tmax){
	//cout<<"Trip Generado:\t Score: "<<trip_score<<"\tLength: "<<trip_length<<'\n';
	ofstream file;
	string file_path = "Solutions/" + file_name;
	file.open(file_path.c_str(), ios::app);
	file<<trip_max_length<<"\t"<<trip_length<<"\t";
	for (int i = 0 ; i < (signed)poi_list.size(); i ++){
		if(i == 0)
			file<<"h"<<departure_hotel<<"\tp"<<poi_list[i];
		else if(i+1 == (signed)poi_list.size())
			file<<"\tp"<<poi_list[i]<<"\th"<<arrival_hotel<<"\n";
		else
			file<<"\tp"<<poi_list[i];
	}
	if((signed)poi_list.size() == 1)
		file<<"\th"<<arrival_hotel<<"\n";
}

void  trip::calculate_distance_dhotel_poi(vector< vector<int> >hotel_list, vector< vector<int> >poi_list){
	int poi = this->poi_list.front();
	int dhx = hotel_list[departure_hotel][0];
	int dhy = hotel_list[departure_hotel][1];
	int px = poi_list[poi][0];
	int py = poi_list[poi][1];

	int distance = euclidean_distance(dhx,dhy,px,py);
	this->distances[0] = distance;
}

float trip::sum_distances(){
	float sum = 0;
	for(int i = 0; i < (signed)distances.size(); i++)
		sum += distances[i];
	return sum;
}

void trip::reset_distances(vector< vector<int> >hotel_list, vector< vector<int> >pois_list){
	this->distances.clear();

	int apx, apy, dpx, dpy;

	int dhx = hotel_list[departure_hotel][0];
	int dhy = hotel_list[departure_hotel][1];
	int ahx = hotel_list[arrival_hotel][0];
	int ahy = hotel_list[arrival_hotel][1];

	apx = pois_list[poi_list[0]][0];
	apy = pois_list[poi_list[0]][1];

	this->distances.push_back(euclidean_distance(dhx,dhy, apx, apy));

	for(int i = 0 ; i < (signed) poi_list.size()-1; i++){
		//cout<<poi_list[i]<<'\n';
		dpx = pois_list[poi_list[i]][0];
		dpy = pois_list[poi_list[i]][1];

		apx = pois_list[poi_list[i+1]][0];
		apy = pois_list[poi_list[i+1]][1];

		this->distances.push_back(euclidean_distance(dpx,dpy,apx,apy));

		if(i+2 == (signed) poi_list.size()){
			dpx = pois_list[poi_list[i+1]][0];
			dpy = pois_list[poi_list[i+1]][1];
			this->distances.push_back(euclidean_distance(dpx,dpy,ahx,ahy));
		}
	}
}

void trip::set_to_erase_poi(int poi_position){
	//cout<<"Borrando al POI: "<<poi_position<<'\n';
	this->poi_list[poi_position] = -1;

}

void trip::erase_pois(){
	vector<int> new_poi_list;
	for(int i = 0; i < (signed)poi_list.size(); i++){
		if(poi_list[i] != -1)
			new_poi_list.push_back(poi_list[i]);
	}

	this->poi_list.clear();
	this->poi_list = new_poi_list;
}
