#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

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

    void dijkstra(int target) {
        nodes[target].h = 0;
        map <int, Node *> q;
        pair <int, Node *> curr;
        vector <bool> visited(size, false);
        int min_curr;
        q[target] = &nodes[target];
        while (q.size() != 0) {
            min_curr = __INT_MAX__;
            // find minimum from open
            for (pair <int, Node *> elem : q) {
                if (elem.second->h < min_curr) {
                    curr = elem;
                    min_curr = elem.second->h;
                }
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
                    }
                }
            }
            // delete curr from q
            q.erase(curr.first);
            visited[curr.first] = true;
        }
    }

    vector <int> aStar(int from, int to) {
        vector <int> res;
        vector <bool> visited(size, false);
        nodes[from].d = 0;
        map <int, Node *> q;
        pair <int, Node *> curr;
        int min_curr;
        if (nodes[from].h != __INT_MAX__) {
            q[from] = &nodes[from];
        }
        while (q.size() != 0) {
            min_curr = __INT_MAX__;
            // find minimum from open q
            for (pair <int, Node *> elem : q) {
                int d_h_curr = elem.second->d + elem.second->h; // d + h of some in q
                if (d_h_curr < min_curr) {
                    curr = elem;
                    min_curr = d_h_curr; // new min d + h
                }
            }

            if (curr.first == to) {
                res.push_back(to);
                int p = curr.second->parent;
                while (p != -1) {
                    res.push_back(p);
                    p = nodes[p].parent;
                }
            }
            // for its child add them to open
            // if h ==  max int we wont add it to open q !!!

            // remake childs d paremetr
            for (pair <int, Edge> child : curr.second->edges) {
                if (visited[child.first] != true) {
                    // add child to open q
                    Node * curr_child = child.second.node;
                    if (curr_child->h != __INT_MAX__) {
                        q[child.first] = &nodes[child.first];
                    }
                    // if less d + h
                    if (curr_child->parent == -1 || curr_child->d > child.second.waight) {
                        curr_child->d = child.second.waight;
                        curr_child->parent = curr.first;
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
        return res;
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

    pair <vector <int>, int> /*vector <int> - order of nodes; int - min waight*/ findShortestPath (const int from, const int to) {
        queue <pair <int, Node *>> q; // main queue
        vector <bool> visited(size, false); // vector for visited nodes
        pair <int, Node *> current; // curent value
        vector <int> parent(size, -1); // for each node u have parent node and it index
        pair <vector <int>, int> res({}, 0); // final res data arr of number of noder and min C

        q.push(pair <int, Node *> (from, &nodes[from]));
        visited[from] = true;
        while(!q.empty()) {
            current = q.front(); //make current node in front
            q.pop();    // delete it from queue
            for (pair <int, Edge> edge : (*current.second).edges) {
                // for all next in current node
                // edge.first - number of next node
                // edge.second - edge himself
                if (!visited[edge.first]) {
                    // next node not in visited
                    visited[edge.first] = true;
                    parent[edge.first] = current.first;
                    if (edge.first == to) {
                        // we meet final
                        res.first.push_back(to); // add to res final node
                        res.second = __INT_MAX__; // now min C eq max int (infinity)

                        while (res.first.back() != from) {
                            int curr = res.first.back(), /*current form last*/
                                parent_curr = parent[curr], /*parent of current*/
                                parent_curr_waight = nodes[parent_curr].edges[curr].waight; /*waight of way btn them from parent to relative*/
                            if (parent_curr_waight < res.second) {
                                // if some edge less than min C
                                res.second = parent_curr_waight;
                            }
                            res.first.push_back(parent_curr);
                        }
                        reverse(res.first.begin(), res.first.end());
                        return res;
                    } else {
                        // we not met final
                        q.push(pair <int, Node *> (edge.first, edge.second.node));
                    }
                }
            }
        }
        return res;
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
        Node() : d(__INT_MAX__), h(__INT_MAX__), parent(-1) {}
        unordered_map <int, Edge> edges;
        int d;
        int h;
        int parent;
        ~Node() = default;
    };
    int size;
    vector <Node> nodes;
};
