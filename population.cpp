#include "trip.h"
#include "generator.h"
#include "tour.h"
#include "population.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

vector<tour> generate_initial_population(int size, vector< vector<int> > hotel_list, 
	vector< vector<int> > poi_list, float tmax, vector<float> td){
	
	vector<tour> population;
	for(int i = 0; i < size; i++){
		tour t;
  		t.set_tmax(tmax);
  		t.set_number_of_trips((signed)td.size());
  		t.set_trips(hotel_list, poi_list, td);
  		population.push_back(t);
  		cout<<"Solucion "<<i<<" generada\n";
	}

	return population;
}

vector<int> get_scores(vector<tour> population){
	vector<int> scores;
	for(int i= 0; i<(signed) population.size(); i++)
		scores.push_back(population[i].get_total_score());

	return scores;
}

void print_solutions(vector<tour> population){
	for(int i= 0; i<(signed) population.size(); i++){
		cout<<"Solution "<<i<<"\n";
		population[i].print_tour();
		cout<<"----------------------------------------\n";
	}

}

int get_sum(vector<int> scores){
	int sum = 0;
	for(int i = 0; i < (signed)scores.size(); i++)
		sum += scores[i];
	return sum;
}

vector<float> get_prob_list(vector<int> scores){
	int total = get_sum(scores);
	float p;
	vector<float> probabilities;
	for(int i = 0; i < (signed)scores.size(); i++){
		p = (float)scores[i]/(float)total;
		probabilities.push_back(p);
	}
	return probabilities;
}

vector<float> get_prob_limits(vector<float> probabilities){
	vector<float> prob_limits;
	prob_limits.push_back(0.0);
	for(int i = 0; i < (signed)probabilities.size(); i++)
		prob_limits.push_back(prob_limits.back() + probabilities[i]);
	return prob_limits;
}

int roulette_operator(vector<tour> population){
	vector<int> scores = get_scores(population);
	vector<float> probabilities = get_prob_list(scores);
	vector<float> prob_limits = get_prob_limits(probabilities);
	float p = (float)rand()/(float)(RAND_MAX);
	int selected_solution;

	for(int i = 0; i < (signed)prob_limits.size()-1; i++)
		if(p >prob_limits[i] && p<prob_limits[i+1]){
			selected_solution = i+1;
			break;
		}

	return selected_solution;
	
}

void migration(vector<tour> population1, vector<tour> population2){
	int chosen1 = roulette_operator(population1);
	int chosen2 = roulette_operator(population2);

	population1.push_back(population2[chosen2]);
	population2.erase(population2.begin()+chosen2-1);
	population2.push_back(population1[chosen1]);
	population1.erase(population1.begin()+chosen1-1);
}

void set_as_visited(vector<int> pois, int visited_list[]){
	for(int i = 0; i < (signed)pois.size(); i++){
		//cout<<"Marcando como visitado al POI: "<<pois[i]<<'\n';
		visited_list[pois[i]] = 1;
	}
}

int delete_duplicates_pois(tour &t, int crossover_point, int visited_list[],vector< vector<int> >hotel_list , vector< vector<int> >pois_list){
	int status = 1;
	vector<trip> trips;

	for(int i = 0; i < crossover_point; i ++){
		trip trip = t.get_trip(i);
		vector<int> poi_list = trip.get_poi_list();
		for(int j = 0; j < (signed)poi_list.size(); j++){
			//cout<<"Marca visitado para el poi "<<poi_list[j]<<" "<<visited_list[poi_list[j]]<<'\n';
			if(visited_list[poi_list[j]] == 1){
				//cout<<"ERASING POI "<<j<<"\n";
				trip.set_to_erase_poi(j);
				//cout<<"AQUI ESTA: "<<trip.get_poi_list()[j]<<"\n";
				trip.set_trip_score(trip.get_trip_score() - pois_list[j][2]);
			}
		}
		set_as_visited(poi_list, visited_list);
		trip.erase_pois();
		//cout<<"end if visited "<<"\n";
		if((signed)trip.get_poi_list().size() != 0){
			//cout<<"reseting distances "<<"\n";
			trip.reset_distances(hotel_list,pois_list);
			trip.set_trip_length(trip.sum_distances());
			//cout<<"reseted "<<"\n";
		}

		else
			status = 0;

		trips.push_back(trip);
		//cout<<"Hotel final"<<trip.get_arrival_hotel()<<'\n';
	}
	trips.push_back(t.get_trip(crossover_point));

	for(int i = crossover_point + 1; i < t.get_number_of_trips() ; i ++){
		trip trip = t.get_trip(i);
		vector<int> poi_list = trip.get_poi_list();
		for(int j = 0; j < (signed)poi_list.size(); j++){
			//cout<<"Marca visitado para el poi "<<poi_list[j]<<" "<<visited_list[22]<<'\n';
			if(visited_list[poi_list[j]] == 1){
				trip.set_to_erase_poi(poi_list[j]);
				trip.set_trip_score(trip.get_trip_score() - pois_list[j][2]);
			}
		}
		t.get_trip(i).erase_pois();
		if((signed)trip.get_poi_list().size() != 0){
			trip.reset_distances(hotel_list, pois_list);
			trip.set_trip_length(trip.sum_distances());
		}
		else
			status = 0;
		trips.push_back(trip);
	}

	t.reset_trips(trips);
	return status;
}

tour crossover(tour t1, tour t2, vector< vector<int> > hotel_list, vector< vector<int> >poi_list){
	int crossover_point = rand() % (t1.get_number_of_trips());
	cout<<"Cross point "<<crossover_point<<"\n";
	tour offspring;
	int  factibility = 1;
	offspring.set_tmax(t1.get_tmax());
  	offspring.set_number_of_trips(t1.get_number_of_trips());
  	trip xtrip1 = t1.get_trip(crossover_point);
  	trip xtrip2 = t2.get_trip(crossover_point);
  	int visited_list[poi_list.size()];
  	
  	for (int i; i < (signed)poi_list.size();i++){
  		visited_list[i] = 0;
  		cout<<visited_list[i];
  	}
  	
  	for(int i = 0; i <offspring.get_number_of_trips(); i++){
  		if(i == crossover_point){
  			trip xtrip  = xtrip1;
  			xtrip.clear_poi_list();
  			xtrip.set_arrival_hotel(xtrip2.get_arrival_hotel());
  			xtrip.set_trip_score(xtrip2.get_trip_score());
  			xtrip.set_trip_length(0);
  			xtrip.set_poi_list(xtrip2.get_poi_list());
  			xtrip.set_distances(xtrip2.get_distances());
  			xtrip.calculate_distance_dhotel_poi(hotel_list,poi_list);
  			xtrip.set_trip_length(xtrip.sum_distances());
  			offspring.push_trip(xtrip);
  			set_as_visited(xtrip2.get_poi_list(), visited_list);
  			if(xtrip.get_trip_max_length() < xtrip.get_trip_length())
  				factibility = 0;

  		}
  		else if(i>crossover_point){
  			trip t = t2.get_trip(i);
  			offspring.push_trip(t);
  		}
  		else if(i<crossover_point){
  			trip t = t1.get_trip(i);
  			offspring.push_trip(t);
  		}
  	}
  	offspring.print_tour();
  	if(factibility == 1){
   		int success = delete_duplicates_pois(offspring, crossover_point, visited_list, hotel_list, poi_list);
   		if(!success)
   			offspring.set_tmax(-1);
  	}
  	else
  		offspring.set_tmax(-1);

  	offspring.print_tour();
  	offspring.set_total_score();
  	return offspring;
}