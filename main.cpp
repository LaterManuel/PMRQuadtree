#include <iostream>
#include <cmath>
#include <string>

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
};
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

}