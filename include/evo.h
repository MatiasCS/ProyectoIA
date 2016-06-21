#ifndef EVO_H
#define EVO_H
#include "trip.h"
#include <vector>
using namespace std;

//Metodo utilizado para construir una solución inicial.
trip build_trip(vector< vector<int> > hotel_list, vector< vector<int> > poi_list, trip t);

//Retorna el conjunto de pois separados a lo mas por una distancia max_distance
//del último poi visitado en el trip t.
vector<int> get_closests_pois(vector< vector<int> > poi_list, trip t, float max_distance);

//Retorna el hotel mas cercano al último POI visitado
//a una distancia maxima de max_distance. Sino se encuentra un hotel
//entonces se retorna el mas cercano sin considerar la restricción anterior.
int get_closest_hotel(vector< vector<int> > poi_list, vector< vector<int> > hotel_list, trip t, float max_distance);
#endif