#include "trip.h"
#include "utilities.h"
#include <vector>
//for couts
//#include <iostream>
using namespace std;

trip build_trip(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip t){
	int departure_hotel = t.get_departure_hotel();
	int dh_x = hotel_list[departure_hotel][0];
	int dh_y = hotel_list[departure_hotel][1];
	float tmax = t.get_trip_max_length();
	float distance;
	int ap_x, ap_y;
	do{
		if((signed)t.get_poi_list().size() == 0)
			t.clear_poi_list();
		
		t.set_initial_poi((signed)poi_list.size());
		int arrival_poi = t.get_last_poi();
		
		ap_x = poi_list[arrival_poi][0];
		ap_y = poi_list[arrival_poi][1];

		distance = euclidean_distance(dh_x,dh_y,ap_x,ap_y);
		t.set_trip_length(distance);
		t.set_trip_score(poi_list[arrival_poi][2]);
	}while(distance > tmax);

	return t;
}

vector<int> get_closests_pois(vector< vector<int> > poi_list, trip t, float max_distance){
	vector<int> closests_pois_ids;
	int departure_poi = t.get_last_poi();

	int dp_x = poi_list[departure_poi][0];
	int dp_y = poi_list[departure_poi][1];

	int ap_x, ap_y;

	for (int i = 0; i < (signed)poi_list.size(); i++){
		if(i != departure_poi){
			ap_x = poi_list[i][0];
			ap_y = poi_list[i][1];
			float distance = euclidean_distance(dp_x,dp_y,ap_x,ap_y);
			if(distance < max_distance)
				closests_pois_ids.push_back(i);
		}
	//cout<<"Id poi mas inicial: "<<departure_poi<<'\n';
	//cout<<"Id poi mas cercano: "<<closest_poi_id<<'\n';
	}
	return closests_pois_ids;
}

int get_closest_hotel(vector< vector<int> > poi_list, vector< vector<int> > hotel_list, trip t, float max_distance){
	int min_distance;
	int closest_hotel_id = -1;
	int worst_case_hotel_id;
	int departure_poi = t.get_last_poi();

	int dp_x = poi_list[departure_poi][0];
	int dp_y = poi_list[departure_poi][1];

	int ah_x, ah_y;

	for (int i = 0; i < (signed)hotel_list.size(); i++){
		if(i==0){
			ah_x = hotel_list[i][0];
			ah_y = hotel_list[i][1];
			min_distance = euclidean_distance(dp_x,dp_y,ah_x,ah_y);
			worst_case_hotel_id = i;
			if(min_distance <= max_distance)
				closest_hotel_id = i;
		}
		else{
			ah_x = hotel_list[i][0];
			ah_y = hotel_list[i][1];
			float distance = euclidean_distance(dp_x,dp_y,ah_x,ah_y);

			if(distance <= max_distance && distance <= min_distance)
				closest_hotel_id = i;
			
			if(distance <= min_distance){
				min_distance = distance;
				worst_case_hotel_id = i;
			}
		}
	}
	if(closest_hotel_id == -1)
		closest_hotel_id = worst_case_hotel_id;
	
	return closest_hotel_id;
}