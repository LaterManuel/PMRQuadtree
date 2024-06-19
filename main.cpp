#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
// Point struct
struct point{
    float x;
    float y;
    point(float x, float y): x(x), y(y){}
};
// Euclidean distance between two points
float euclidean_distance(point p1, point p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
point middle_edge(point p1, point p2){
    return point((p1.x + p2.x)/2, (p1.y + p2.y)/2);
}
// Edge struct
struct edge{
    point p1;
    point p2;
    float size;
    point middle;
    edge(point p1, point p2): p1(p1), p2(p2), size(euclidean_distance(p1,p2)),middle(middle_edge(p1,p2)){}
    edge(float x1, float y1, float x2, float y2): p1(x1, y1), p2(x2, y2), size(euclidean_distance(p1,p2)),middle(middle_edge(p1,p2)){}
    void print(){
        cout << p1.x << " " << p1.y << " Dirigido a " << p2.x << " " << p2.y << " con punto intermedio " << middle.x << " " << middle.y << " y distancia de "<< size << endl;
    }
};
// Read csv file
vector<edge> read_csv(const std::string& filename){
    std::vector<edge> edges;
    std::ifstream file(filename);
    std::string line;
    getline(file, line);  // Skip the header
    while(getline(file, line)){
        std::stringstream ss(line);
        float x1, y1, x2, y2;
        char comma;
        ss >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2;
        edges.push_back(edge(x1, y1, x2, y2));
    }
    return edges;
}

// Node struct
struct node{
    point p;
    node* next;
    node(point p): p(p), next(nullptr){}
};
// Quadtree struct
struct quadtree{
    node *root;
    int fill_factor=3;
    quadtree(): root(nullptr){}
};


int main(){
    vector<edge> edges = read_csv("datapy.csv");
    int count = 0;
    for(auto e: edges){
        e.print();
        count++;
    }
    cout << "Total de aristas: " << count << endl;
    return 0;
    
}