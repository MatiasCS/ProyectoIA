#ifndef GENERATOR_H
#define GENERATOR_H
#include "trip.h"
#include <vector>
using namespace std;

//Metodo utilizado para construir una solución inicial.
void build_trip(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip &t, int is_last, int visited_pois[]);

//Retorna el conjunto de pois separados a lo mas por una distancia max_distance
//del último poi visitado en el trip t.
vector<int> get_closests_pois(vector< vector<int> > poi_list, trip t, int visited_pois[], float max_distance);

//Retorna el hotel mas cercano al último POI visitado
//a una distancia maxima de max_distance. Sino se encuentra un hotel
//entonces se retorna el mas cercano sin considerar la restricción anterior.
vector<float> get_closest_hotel(vector< vector<int> > poi_list, vector< vector<int> > hotel_list, trip t, float max_distance);

//Retorna el poi con el mayor score de la lista de pois_ids
int select_max_score_poi(vector< vector<int> > pois_list, vector<int> pois_ids);

//Funcion para generar el recorrido de pois y el hotel final
void add_vertices(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip &t, int *visited_pois);

//Funcion que permite eliminar pois para obtener una solución factible al momento de crear el recorrido
void delete_until_factibility(trip& t, vector< vector<int> > poi_list, vector< vector<int> > hotel_list);
#endif