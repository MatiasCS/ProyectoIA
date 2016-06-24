#ifndef POPULATION_H
#define POPULATION_H
#include "trip.h"
#include "generator.h"
#include "tour.h"
#include <vector>
using namespace std;
//Aplicacion del algoritmo greedy para generar soluciones iniciales
vector<tour> generate_initial_population(int size, vector< vector<int> > hotel_list,
 vector< vector<int> > poi_list, float tmax, vector<float> td);

//Retorna un vector con los scores de las soluciones de una poblacion
vector<int> get_scores(vector<tour> tour);

//Imprime en pantalla las soluciones de una poblacion
void print_solutions(vector<tour> population);

//Obtiene la suma de un vector con puntajes
int get_sum(vector<int> scores);

//Obtiene la lista con las probabilidades para cada solucion de ser seleccionada por ruleta
vector<float> get_prob_list(vector<int> scores);

//Reotrna los limites para detectar que solucion corresponde a cada rango de probabilidad
vector<float> get_prob_limits(vector<float> probabilities);

//Retorna el id de la solucion elegida
int roulette_operator(vector<tour> population);

//Aplica migracion entre poblaciones
void migration(vector<tour> population1, vector<tour> population2);

//Marca los pois de la lista pois como visitados (1) en la lista visited_list
void set_as_visited(vector<int> pois, int visited_list[]);

//Elimina los pois duplicados del tour
int delete_duplicates_pois(tour &t, int crossover_point, int visited_list[],vector< vector<int> >hotel_list , vector< vector<int> >pois_list);

//Aplica el operador de cruzamiento
tour crossover(tour t1, tour t2, vector< vector<int> > hotel_list, vector< vector<int> >poi_list);

//Aplicacion del algoritmo evolutivo
void evolutive(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, float tmax, vector<float> td, int iterations, string file_name);

//Aplicacion del operador de cruzamiento
vector<tour> xover_operator(vector<tour> population, vector< vector<int> > hotel_list, vector< vector<int> > poi_list);

//Reotrna la mejor solucion de la poblacion
tour select_best_solution(vector<tour> population);
#endif
