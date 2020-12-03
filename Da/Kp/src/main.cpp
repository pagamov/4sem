#include <iostream>
#include <vector>
#include <time.h>
#include "graf.hpp"

using namespace std;

int main() {
    clock_t start_clock;
    int start, end;
    cin >> start >> end;

    int n, m, x, y, from, to, waight;
    cin >> n >> m;
    Graf G(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> x >> y;
        G.setCoord(i, x, y);
    }

    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> waight;
        G.changeEdge(from, to, waight);
    }

    start_clock = clock();
    pair <int, vector <int>> res_1 = G.aStar(start, end);

    printf("A star time: %f\t\t\n", (double)(clock() - start_clock) / CLOCKS_PER_SEC);
    for (int path : res_1.second) {
        cout << path << " ";
    }
    cout << "\n";
    // cout << "distance: " << res_1.first << "\n";

    G.clearGraf();

    start_clock = clock();
    pair <int, vector <int>> res_2 = G.Dijkstra(start, end);

    printf("Dijkstra time : %f\t\t\n", (double)(clock() - start_clock) / CLOCKS_PER_SEC);
    for (int path : res_2.second) {
        cout << path << " ";
    }
    cout << "\n";
    // cout << "distance: " << res_2.first << "\n";

    return 0;
}
