#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Vertex {
public:
    map <char, Vertex *> child;
    string::iterator begin, end;
    Vertex * suff_link;
    set <int> number_string;
    Vertex(string::iterator begin, string::iterator end) : begin(begin), end(end), suff_link(nullptr) {};
    ~Vertex();
};

Vertex::~Vertex() {
    for (pair <char, Vertex *> node : child) {
        delete node.second;
    }
}

struct LCS { // longest common substring
    int length;
    vector <Vertex *> path_to_subs;
    Vertex * begining;
    Vertex * ending;
};

#endif
