#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "shapefil.h"

using namespace std;

// Point struct
struct point {
    int id;
    float x;
    float y;
    point(int id, float x, float y): id(id), x(x), y(y) {}
};

// Euclidean distance between two points
float euclidean_distance(point p1, point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

point middle_edge(point p1, point p2) {
    return point(-1, (p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
}

// Edge struct
struct edge {
    point p1;
    point p2;
    float size;
    point middle;
    edge(point p1, point p2) : p1(p1), p2(p2), size(euclidean_distance(p1, p2)), middle(middle_edge(p1, p2)) {}
};

// Function to read nodes_v2.dbf
unordered_map<int, point> read_nodes(const string& filename) {
    unordered_map<int, point> nodes;
    DBFHandle dbf = DBFOpen(filename.c_str(), "rb");
    if (dbf == nullptr) {
        cerr << "Error opening " << filename << endl;
        exit(1);
    }

    int numRecords = DBFGetRecordCount(dbf);
    for (int i = 0; i < numRecords; i++) {
        int id = DBFReadIntegerAttribute(dbf, i, 0); // Reading ID
        double y = DBFReadDoubleAttribute(dbf, i, 1); // Reading Y
        double x = DBFReadDoubleAttribute(dbf, i, 2); // Reading X
        if (nodes.find(id) == nodes.end()) {
            nodes[id] = point(id, x, y);
        } else {
            cerr << "Duplicate node id found: " << id << endl;
        }
    }

    DBFClose(dbf);
    return nodes;
}

// Function to read edges.dbf
vector<edge> read_edges(const string& filename, const unordered_map<int, point>& nodes) {
    vector<edge> edges;
    DBFHandle dbf = DBFOpen(filename.c_str(), "rb");
    if (dbf == nullptr) {
        cerr << "Error opening " << filename << endl;
        exit(1);
    }

    int numRecords = DBFGetRecordCount(dbf);
    for (int i = 0; i < numRecords; i++) {
        int u = DBFReadIntegerAttribute(dbf, i, 0); // Reading start node ID
        int v = DBFReadIntegerAttribute(dbf, i, 1); // Reading end node ID
        if (nodes.find(u) != nodes.end() && nodes.find(v) != nodes.end()) {
            edges.push_back(edge(nodes.at(u), nodes.at(v)));
        } else {
            cerr << "Edge with non-existent nodes found: " << u << " -> " << v << endl;
        }
    }

    DBFClose(dbf);
    return edges;
}

// Struct QuadTree
struct QuadTree {
    point p1;
    point p2;
    QuadTree* NW;
    QuadTree* NE;
    QuadTree* SW;
    QuadTree* SE;
    vector<edge> edges;
    QuadTree(point p1, point p2) : p1(p1), p2(p2), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
};

int main() {
    // Read nodes and edges
    unordered_map<int, point> nodes = read_nodes("../../nodes.dbf");
    vector<edge> edges = read_edges("../../edges.dbf", nodes);

    // Open a CSV file for writing
    ofstream csvFile("edges.csv");

    // Write the header
    csvFile << "Node1_x,Node1_y,Node2_x,Node2_y,Distance\n";

    // Output edges
    for (const auto& e : edges) {
        csvFile << e.p1.x << "," << e.p1.y << ","
                << e.p2.x << "," << e.p2.y << ","
                << e.size << "\n";
    }

    // Close the file
    csvFile.close();

    // Output debug information
    for (const auto& node : nodes) {
        cout << "Node ID: " << node.first << " - (" << node.second.x << ", " << node.second.y << ")\n";
    }

    for (const auto& e : edges) {
        cout << "Edge from (" << e.p1.x << ", " << e.p1.y << ") to ("
             << e.p2.x << ", " << e.p2.y << ") with middle point ("
             << e.middle.x << ", " << e.middle.y << ") and size " << e.size << endl;
    }

    return 0;
}
