#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

class Graf {
public:
    Graf() = default;
    Graf(int size) : size(size), nodes(size) {}

    void changeEdge(const int from, const int to, const int waight) {
        if (waight == 0) {
            nodes[from].edges.erase(to);
        } else {
            nodes[from].edges[to] = Edge(&nodes[to], waight);
        }
    }

    inline int Waight (const int from, const int to) {
        return nodes[from].edges.find(to) != nodes[from].edges.end() ? nodes[from].edges[to].waight : 0;
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
    };
    struct Node {
        unordered_map <int, Edge> edges;
    };
    int size;
    vector <Node> nodes;
};
