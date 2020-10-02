#include <iostream>
#include <vector>
#include "graf.hpp"

using namespace std;

int main() {
    int n, m, from, to, waight;
    cin >> n >> m;
    Graf G(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> waight;
        G.changeEdge(from, to, waight);
    }

    unsigned long long answer = 0;
    pair <vector <int>, int> path = G.findShortestPath(1, n);

    while (path.second != 0) {
        answer += path.second;
        for (int i = 1; i < (int)path.first.size(); i++) {
            G.changeEdge(path.first[i - 1], path.first[i], G.Waight(path.first[i - 1], path.first[i]) - path.second);
            G.changeEdge(path.first[i], path.first[i - 1], G.Waight(path.first[i], path.first[i - 1]) + path.second);
        }
        path = G.findShortestPath(1, n);
    }
    cout << answer << "\n";
    return 0;
}
