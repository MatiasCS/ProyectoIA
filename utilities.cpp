#include <utilities.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;

static string FILE_NOT_FOUND_ERROR = "No se pudo abrir el archivo. Por favor verifique que la ruta es valida\n";

int * to_int_params(string line){
  static int params[3];
  stringstream ss(line);
  string token;
  int i = 0;
  while(getline(ss,token,'\t')){
      params[i] = (atoi(token.c_str()));
      i++;
  }
  return params;
}

vector<int> to_int_vdetails(string line){
  vector<int> v;
  stringstream ss(line);
  string token;
  while(getline(ss,token,'\t')){
      v.push_back(atoi(token.c_str()));
  }
  return v;
}

vector<float> to_float_tlengths(string line){
  vector<float> v;
  stringstream ss(line);
  string token;
  while(getline(ss,token,'\t')){
      v.push_back(atof(token.c_str()));
  }
  return v;
}

  int * get_params (string instance_name){
	string line;
  static int * params;
	ifstream instance (instance_name.c_str());
  getline (instance,line);
  params = to_int_params(line);
  instance.close();

  return params;
}

float get_tmax (string instance_name){
  string line;
  int tmax;
  ifstream instance (instance_name.c_str());
  for(int i = 0; i < 2; i++)
    getline (instance,line);
    
  tmax = atof(line.c_str());
  instance.close();

  return tmax;
}

vector<float> get_td (string instance_name){
  string line;
  vector<float> td;
  ifstream instance (instance_name.c_str());
  for(int i = 0; i < 3; i++)
    getline (instance,line);
  
  td = to_float_tlengths(line);
  instance.close();

  return td;
}

int instance_checker(string instance_name){
  int success = 1;
  ifstream instance (instance_name.c_str());
  if (!instance.is_open())
    success = 0;

  return success; 
}

vector< vector<int> > get_hotels(string instance_name, int H){
  string line;
  vector< vector<int> > hotels (H + 2, vector<int>(3));
  ifstream instance (instance_name.c_str());
  vector<int> hotel;
  for(int i = 0; i < 4; i++)
    getline (instance,line);

  for(int i = 0; i < H +2; i++){
    getline(instance,line);
    hotel = to_int_vdetails(line);
    hotels[i][0] = hotel[0];
    hotels[i][1] = hotel[1];
    hotels[i][2] = hotel[2];
  }

  return hotels;  
}

vector< vector<int> > get_pois(string instance_name, int N ,int H){
  string line;
  vector< vector<int> > pois (N - 2, vector<int>(3));
  ifstream instance (instance_name.c_str());
  vector<int> poi;
  for(int i = 0; i < 6 + H; i++)
    getline (instance,line);

  for(int i = 0; i < N - 2; i++){
    getline(instance,line);
    poi = to_int_vdetails(line);
    pois[i][0] = poi[0];
    pois[i][1] = poi[1];
    pois[i][2] = poi[2];
  }

  return pois;  
}

float euclidean_distance(int xi , int yi, int xf, int yf){
  float distance;
  int delta_x = xf - xi;
  int delta_y = yf - yi;
  distance = sqrt(delta_x*delta_x + delta_y*delta_y);
  return distance;
}

void error_message(){
  cout << FILE_NOT_FOUND_ERROR; 
}
