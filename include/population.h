#ifndef POPULATION_H
#define POPULATION_H
#include "trip.h"
#include "generator.h"
#include "tour.h"
#include <vector>
using namespace std;

vector<tour> generate_initial_population(int size, vector< vector<int> > hotel_list,
 vector< vector<int> > poi_list, float tmax, vector<float> td);

vector<int> get_scores(vector<tour> tour);

void print_solutions(vector<tour> population);

int get_sum(vector<int> scores);

vector<float> get_prob_list(vector<int> scores);

vector<float> get_prob_limits(vector<float> probabilities);

int roulette_operator(vector<tour> population);

void migration(vector<tour> population1, vector<tour> population2);

void crossover(tour t1, tour t2);
#endif