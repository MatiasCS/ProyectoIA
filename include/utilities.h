#ifndef UTILITIES_H
#define UTILITIES_H
#include <vector>
#include <string>
using namespace std;

//Transforma los valores de N, H y D de string a int
int * to_int_params(string line);

//Transforma los valores de x, y y Si de un vertice de string a int
vector<int> to_int_vdetails(string line);

//Transforma el valor del trip d de string a float
vector<float> to_float_tlengths(string line);

//Extrae los parametros N, H y D de la instancia del problema
int * get_params (string instance_name);

//Extrae el parametro tmax de la instancia del problema
float get_tmax (string instance_name);

//Extrae el parametro td para cada trip de la instancia del problema
vector<float> get_td (string instance_name);

//Chequea si el archivo asociado a la instancia existe
int instance_checker(string instance_name);

//Extrae los parametros x, y y Si para cada hotel de la instancia del problema
vector< vector<int> > get_hotels(string instance_name, int H);

//Extrae los parametros x, y y Si para cada poi de la instancia del problema
vector< vector<int> > get_pois(string instance_name, int N ,int H);

//Calcula la distancia euclideana entre dos pares de vertices
float euclidean_distance(int xi , int yi, int xf, int yf);

//Imprime en consola errores por falta de parametros en la ejecucion del archivo
void error_message();
#endif
