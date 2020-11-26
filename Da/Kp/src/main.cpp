#include <iostream>
#include <vector>
#include "graf.hpp"

using namespace std;

int main() {
    int start, end;
    cin >> start >> end;

    int n, m, from, to, waight;
    cin >> n >> m;
    Graf G(n + 1);

    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> waight;
        G.changeEdge(from, to, waight);
    }
    G.dijkstra(end);
    vector <int> res = G.aStar(start, end);
    for (int path : res) {
        cout << path << " ";
    }
    cout << "\n";
    return 0;
}
