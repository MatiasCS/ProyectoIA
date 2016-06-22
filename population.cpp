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

void crossover(tour t1, tour t2){
	int crossover_point = rand() % (t1.get_number_of_trips());
	tour offspring;
	offspring.set_tmax(t1.get_tmax());
  	offspring.set_number_of_trips(t1.get_number_of_trips());


}