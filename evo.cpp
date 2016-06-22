#include "trip.h"
#include "utilities.h"
#include <vector>
//for couts
#include <iostream>
using namespace std;

const int MAX_DISTANCE = 4;


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
	}
	return closests_pois_ids;
}

vector<float> get_closest_hotel(vector< vector<int> > poi_list, vector< vector<int> > hotel_list, trip t, float max_distance){
	vector<float> closest_hotel;
	float min_distance;
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
	
	closest_hotel.push_back(closest_hotel_id);
	closest_hotel.push_back(min_distance);

	return closest_hotel;
}

int select_max_score_poi(vector< vector<int> > poi_list, vector<int> pois_ids){
	int max_score, max_score_poi_id, score, id;
	for (int i = 0; i < (signed)pois_ids.size(); i++){
		if(i == 0){
			id = pois_ids[i];
			max_score = poi_list[id][2];
			max_score_poi_id = id;
		}
		else{
			id = pois_ids[i];
			score = poi_list[id][2];
			if(score > max_score){
				max_score = score;
				max_score_poi_id = id;
			}
		}
	}
	return max_score_poi_id;
}

void delete_until_factibility(trip& t, vector< vector<int> > poi_list, vector< vector<int> > hotel_list){
	int flag = 1;
	while(flag){
		int last_poi = t.get_last_poi();
		t.set_trip_length(t.get_trip_length() - t.get_last_poi_distance());
		t.set_trip_score(t.get_trip_score() - poi_list[last_poi][2]);
		t.pop_last_poi();

		vector<float> new_hotel = get_closest_hotel(poi_list, hotel_list, t, MAX_DISTANCE);
		if(t.get_trip_length() + new_hotel[1] < t.get_trip_max_length()){
			t.push_distance(new_hotel[1]);
			t.set_trip_length(t.get_trip_length() + new_hotel[1]);
			t.set_arrival_hotel(new_hotel[0]);
			flag = 0;
		}
	}
}

void add_vertices(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip &t){
	int flag = 1;
	int actual_poi, poi_to_add;
	vector<float> closest_hotel;
	int apx, apy, px, py;
	float distance_to_hotel, distance_to_poi;
	float length, max_length;

	max_length = t.get_trip_max_length();

	actual_poi = t.get_last_poi();
	while(flag){
		length = t.get_trip_length();
		vector<int> closests_pois = get_closests_pois(poi_list, t, MAX_DISTANCE);
		closest_hotel = get_closest_hotel(poi_list, hotel_list, t, MAX_DISTANCE);

		poi_to_add = select_max_score_poi(poi_list, closests_pois);
	
		apx = poi_list[actual_poi][0];
		apy = poi_list[actual_poi][1];

		px = poi_list[poi_to_add][0];
		py = poi_list[poi_to_add][1];

		distance_to_poi = euclidean_distance(apx, apy, px, py);
		distance_to_hotel = closest_hotel[1];
		
		if(max_length > length + distance_to_poi){
			t.push_poi(poi_to_add);
			t.push_distance(distance_to_poi);
			t.set_trip_length(length + distance_to_poi);
			t.set_trip_score(t.get_trip_score() + poi_list[poi_to_add][2]);
		}
		else if(max_length < length + distance_to_poi && max_length > length + distance_to_hotel){
			t.push_distance(distance_to_hotel);
			t.set_trip_length(length + distance_to_hotel);
			t.set_arrival_hotel(closest_hotel[0]);
			flag = 0;
		}

		else if(max_length < length + distance_to_poi && max_length < length + distance_to_hotel){
			delete_until_factibility(t,poi_list,hotel_list);
			flag = 0;
		}

	}
}

void build_trip(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip &t){
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
		t.push_distance(distance);
	}while(distance > tmax);

	add_vertices(hotel_list, poi_list, t);
	//return t;
}