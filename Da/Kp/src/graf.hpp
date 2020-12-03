#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

class Graf {
public:
    Graf() = default;
    Graf(int size) : size(size), nodes(size) {}

    void print() {
        for (int i = 0; i < size; i++) {
            cout << i << " " << "d: " << nodes[i].d << " h: " << nodes[i].h << "\n";
            cout << '\t';
            for (pair <int, Edge> child : nodes[i].edges) {
                cout << child.first << " ";
            }
            cout << "\n";
        }
    }

    pair <int, vector <int>> Dijkstra(int from, int to) {
        vector <int> res;
        int distance = 0;
        nodes[from].h = 0;
        map <int, Node *> q;
        pair <int, Node *> curr;
        vector <bool> visited(size, false);
        int min_curr;
        q[from] = &nodes[from];
        while (q.size() != 0) {
            min_curr = __INT_MAX__;
            // find minimum from open
            for (pair <int, Node *> elem : q) {
                if (elem.second->h < min_curr) {
                    curr = elem;
                    min_curr = elem.second->h;
                }
            }

            if (curr.first == to) {
                res.push_back(to);
                int p = curr.second->parent;
                distance = nodes[curr.first].h;
                while (p != -1) {
                    res.push_back(p);
                    p = nodes[p].parent;
                }
                break;
            }
            // for its child add them to open
            // remake childs h paremetr
            for (pair <int, Edge> child : curr.second->edges) {
                if (visited[child.first] != true) {
                    // add child to open q
                    q[child.first] = &nodes[child.first];
                    // if less h make new
                    int h_min = curr.second->h + curr.second->edges[child.first].waight;
                    if (h_min < nodes[child.first].h) {
                        nodes[child.first].h = h_min;
                        nodes[child.first].parent = curr.first;
                    }
                }
            }
            // delete curr from q
            q.erase(curr.first);
            visited[curr.first] = true;
        }
        if (res.size() != 0) {
            reverse(res.begin(), res.end());
        } else {
            res.push_back(-1);
        }
        pair <int, vector <int>> r(distance, res);
        return r;
    }

    pair <int, vector <int>>  aStar(int from, int to) {
        vector <int> res;
        int distance = 0;
        vector <bool> visited(size, false);
        nodes[from].d = 0;
        nodes[from].h = (int)sqrt(pow(nodes[to].x - nodes[from].x, 2) + pow(nodes[to].y - nodes[from].y, 2));
        // cout << nodes[from].h << "\n";
        map <int, Node *> q;
        pair <int, Node *> curr;
        int min_curr;
        if (nodes[from].h != __INT_MAX__) {
            q[from] = &nodes[from];
        }
        while (q.size() != 0) {
            min_curr = __INT_MAX__;
            // find minimum from open q
            // cout << "q: ";
            for (pair <int, Node *> elem : q) {
                // cout << elem.first << " ";
                int d_h_curr = elem.second->d + elem.second->h; // d + h of some in q
                if (d_h_curr < min_curr) {
                    curr = elem;
                    min_curr = d_h_curr; // new min d + h
                }
            }
            // cout << "\n";

            if (curr.first == to) {
                // cout << "hello!\n";
                res.push_back(to);
                distance = nodes[curr.first].d;
                int p = curr.second->parent;
                while (p != -1) {
                    res.push_back(p);
                    p = nodes[p].parent;
                }
                break;
            }
            // for its child add them to open
            // if h ==  max int we wont add it to open q !!!

            // remake childs d paremetr
            for (pair <int, Edge> child : curr.second->edges) {
                if (visited[child.first] != true) {
                    // add child to open q
                    Node * curr_child = child.second.node;
                    curr_child->h = (int)sqrt(pow(nodes[to].x - nodes[child.first].x, 2) + pow(nodes[to].y - nodes[child.first].y, 2));
                    if (curr_child->h != __INT_MAX__) {
                        q[child.first] = &nodes[child.first];
                    }
                    // if less d + h
                    if (curr_child->parent == -1) {
                        curr_child->parent = curr.first;
                        curr_child->d = child.second.waight + nodes[curr_child->parent].d;
                    } else {
                        if (curr_child->d > child.second.waight + nodes[curr.first].d) {
                            curr_child->parent = curr.first;
                            curr_child->d = child.second.waight + nodes[curr_child->parent].d;
                        }
                    }
                }
            }
            // delete curr from q
            q.erase(curr.first);
            visited[curr.first] = true;
        }

        if (res.size() != 0) {
            reverse(res.begin(), res.end());
        } else {
            res.push_back(-1);
        }
        pair <int, vector <int>> r(distance, res);
        return r;
    }

    void setCoord(int node, int x, int y) {
        nodes[node].x = x;
        nodes[node].y = y;
    }

    void changeEdge(const int from, const int to, const int waight) {
        if (waight == 0) {
            nodes[from].edges.erase(to);
            nodes[to].edges.erase(from);
        } else {
            nodes[from].edges[to] = Edge(&nodes[to], waight);
            nodes[to].edges[from] = Edge(&nodes[from], waight);
        }
    }

    void clearGraf() {
        for (int i = 0; i < size; i++) {
            nodes[i].d = __INT_MAX__;
            nodes[i].h = __INT_MAX__;
            nodes[i].parent = -1;
        }
    }

    ~Graf() = default;

private:
    struct Node;
    struct Edge {
        Edge() = default;
        Edge(Node * node, const int waight) : node(node), waight(waight) {}
        Node * node;
        int waight;
        ~Edge() = default;
    };
    struct Node {
        Node() : d(__INT_MAX__), h(__INT_MAX__), parent(-1), x(0), y(0) {}
        unordered_map <int, Edge> edges;
        int d;
        int h;
        int parent;
        int x, y;
        ~Node() = default;
    };
    int size;
    vector <Node> nodes;
};
