#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#include "middleearth.h"

float computeDistance(MiddleEarth me, const string& start, vector<string> dests);
void printRoute(const string& start, const vector<string>& dests);

int main(int argc, char** argv) {
    // check the number of parameters
    if (argc != 6) {
        cout << "Usage: " << argv[0] << " <world_height> <world_width> "
             << "<num_cities> <random_seed> <cities_to_visit>" << endl;
        exit(0);
    }

    // we'll assume the parameters are all well-formed
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    int num_cities = stoi(argv[3]);
    int rand_seed = stoi(argv[4]);
    int cities_to_visit = stoi(argv[5]);

    // create the world, and select your itinerary
    MiddleEarth me(width, height, num_cities, rand_seed);
    vector<string> dests = me.getItinerary(cities_to_visit);

    /*
    for (int i = 0; i < dests.size(); i++) {
      cout << dests[i] << endl;
    }
    */

    me.printTable();
    
    string start = dests[0];
    dests.erase(dests.begin());

    sort(dests.begin(), dests.end());

    unordered_map<float, vector<string>> distances_map;

    do {
      vector<string> temp;
      temp = dests;
      float total_distance;
      total_distance = computeDistance(me, start, temp);
      distances_map.emplace(total_distance, temp);
    } while (next_permutation(dests.begin(), dests.end()));

    float shortest = distances_map.begin()->first;
    vector <string> shortest_path = distances_map[shortest];
    for (auto itr = distances_map.begin(); itr != distances_map.end(); itr++) {
      if (itr->first < shortest) {
	shortest = itr->first;
	shortest_path = itr->second;
      }
    }

    cout << "Minimum path has distance " << shortest << ": ";
    printRoute(start, shortest_path);
    /*
    printRoute(start, dests);
    
    float total_distance;
    total_distance = computeDistance(me, start, dests);
    */

    return 0;
}

// This method will compute the full distance of the cycle that starts
// at the 'start' parameter, goes to each of the cities in the dests
// vector IN ORDER, and ends back at the 'start' parameter.
float computeDistance(MiddleEarth me, const string& start, vector<string> dests) {
  float total;
  
  for(int i = 0; i < dests.size(); i++) {
    if (i == 0)
      total += me.getDistance(start, dests[0]);
    if (i == dests.size() - 1) {
      total += me.getDistance(dests[i], start);
    } else {
      total += me.getDistance(dests[i], dests[i+1]);
    }
  }

  return total;
    
}

// This method will print the entire route, starting and ending at the
// 'start' parameter.
// The output should be similar to:
// Erebor -> Khazad-dum -> Michel Delving -> Bree -> Cirith Ungol -> Erebor
void printRoute(const string& start, const vector<string>& dests) {
  cout << start << " -> ";

  for (int i = 0; i < dests.size(); i++) {
    if (i == (dests.size() -1 )) {
      cout << dests[i] << " -> " << start;
    } else {
      cout << dests[i] << " -> ";
    }
    
  }

  cout << endl;
      
}
