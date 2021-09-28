//Jack Lesemann, jwl4vg, 5/2/2021
//Pre-lab 11

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * A class that acts as a vertex in a graph
 */
class vertex {
public:
  vertex(string s); /** constructor */
  int indegree; /** int field for indegree */
  string data; /** string field for data held by vertex */

};

/**
 * Constructor for vertex object
 * @param s String that will be set as this vertex object's data field
 */
vertex::vertex(string s) {
  this->data = s;
  indegree = 0;
}

/**
 * A class that will act as a graph 
 * @see vertex
 */
class graph {
public:
  unordered_map<vertex*, vector<vertex*>> vertices; /** unordered_map field to hold vertices and their adjacent vertices */
  graph(); /** constructor */
  void addEdge(vertex* v1, vertex* v2); /** method to add an edge to graph */
  void pushVert(vertex* v1); /** method to push vert into vertices field */
  void topSort(); /** method to print a topologically sorted graph */
	
	
};

/**
 * @brief Graph constructor
 * sets vertices field to empty unordered_map
 */
graph::graph() {
  unordered_map<vertex*, vector<vertex*>> vertices;
}

/**
 * @brief function to add vertex to keys of vertices and any adjacent vertices to the vector in the second element of the pair
 * @param v1 Starting vertex of edge
 * @param v2 Ending vertex of edge
 */
void graph::addEdge(vertex* v1, vertex* v2) {
  pushVert(v1);
  pushVert(v2);
  int indeg = 0;
  for (auto itr = vertices.begin(); itr != vertices.end(); itr++) {
    if (itr->first->data == v2->data) {
      itr->first->indegree++;
      indeg = itr->first->indegree;
    }
    
  }


  for (auto itr2 = vertices.begin(); itr2 != vertices.end(); itr2++) {
    
    if (itr2->first->data == v1->data){
      v2->indegree = indeg;
      itr2->second.push_back(v2);
    } 
  }
}

/**
 * function to push a vertex into the keys of the vertices unordered_map
 * @param v Vertex to be pushed
 */
void graph::pushVert(vertex* v) {
  bool contains = false;

  for (auto itr = vertices.begin(); itr != vertices.end(); itr++) {
    if (itr->first->data == v->data) {
      contains = true; 
    }
  }

  if (!contains) {
    vector<vertex*> vec;
    vertices.emplace(v, vec);
  }
}

/**
 * function that uses a queue to implement Kahn's Algorithm to topologically sort the graph object
 * credit: adapted from code given in slides, https://uva-cs.github.io/pdr/slides/11-graphs.html#/4/7
 */
void graph::topSort() {
  queue<vertex*> q;
  int counter =0;
  vertex* v;
  vertex* w;

  for (auto itr1 = vertices.begin(); itr1 != vertices.end(); itr1++) {
    v = itr1->first;
    if(v->indegree == 0){
      //cout << v->data;
      q.push(v);
    }
  }

  while (!q.empty()) {
    v = q.front();
    q.pop();

    cout << v->data << " ";
    counter++;

    for(int i = 0; i < vertices[v].size(); i++) {
      
      
      w = vertices[v][i];
      w->indegree--;
      
      for(auto itr2 = vertices.begin(); itr2 != vertices.end(); itr2++) {
	  if(itr2->first->data == w->data && itr2->first->indegree != 0) {
	    itr2->first->indegree--;
	  }
      }


      
      // cout << "with edge to: " << w->data << " | " << w->indegree << endl;
      if (w->indegree == 0) {
	for(auto itr3 = vertices.begin(); itr3 != vertices.end(); itr3++) {
	  if(itr3->first->data == w->data) {
	   
	    q.push(itr3->first);
	  }
	}
	      
        
      }
    }
  }

  

  cout<< endl;
  if (counter != vertices.size())
    cout << "Cycle found: " << endl;
      
  


}

//credit: code adapted from fileio2.cpp in slides
int main (int argc, char** argv) {
  // verify the correct number of parameters
  if (argc != 2) {
    cout << "Must supply the input file name as the one and only parameter" << endl;
    exit(1);
  }

  // attempt to open the supplied file
  ifstream file(argv[1], ifstream::binary);
  // report any problems opening the file and then exit
  if (!file.is_open()) {
    cout << "Unable to open file '" << argv[1] << "'." << endl;
    exit(2);
  }
  
  // read in two strings
  string s1, s2;
  graph* g = new graph();

  while (file >> s1) {
    if (s1 != "0") {
      file >> s2;
      vertex* v1 = new vertex(s1);
      vertex* v2 = new vertex(s2);
      g->addEdge(v1, v2);
    }
    
  }
  /*
  for (auto itr = g->vertices.begin(); itr != g->vertices.end(); itr++) {
    cout << "vertex: " << itr->first->data << " | " << itr->first->indegree << endl;
    for (int i = 0; i < itr->second.size(); i++) {
      cout << "with edge to: " << itr->second[i]->data << " | " << itr->second[i]->indegree << endl;
    }
  }
  */
  
  g->topSort();
}
