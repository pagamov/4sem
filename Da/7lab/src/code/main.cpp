#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    int n, m, w, c; // n - number of items; m - max mass; w - w_i; c - c_i
    std::cin >> n >> m;
    n++;
    m++;
    vector<vector<vector<int>>> matrix(n, vector<vector<int>>(n, vector<int>(m, 0)));
    vector<int> shift(n); // for items
    for (int k = 1; k < n; k++) { // layer of item from 1 to n
        cin >> w >> c; //get w and c of item
        shift[k] = w; //add item
        for (int j = 1; j <= k; j++) { // for every variant of number to take
            for (int c_m = 0; c_m < m; c_m++) { // for every mass in range
                if (c_m - w >= 0) { // we can insert item
                    if (matrix[k - 1][j - 1][c_m - w] != 0 || j - 1 == 0) {
                        matrix[k][j][c_m] = max(matrix[k - 1][j][c_m], matrix[k - 1][j - 1][c_m - w] + c);
                    } else {
                        matrix[k][j][c_m] = matrix[k - 1][j][c_m];
                    }
                } else { // we cannot insert item
                    matrix[k][j][c_m] = matrix[k - 1][j][c_m];
                }
            }
        }
    }

    int k = n - 1, c_c = 0, c_m = m - 1; // k - item level; c_c = curent count; c_m - curent mass
    int max_value = 0; // max item value based on count
    for (int count = 0; count < n; count++) {
        if (matrix[k][count][c_m] * count > max_value) {
            max_value = matrix[k][count][c_m] * count;
            c_c = count;
        }
    }
    cout << max_value << "\n";

    vector<int> res;
    while (c_c > 0) {
        if (matrix[k][c_c][c_m] != matrix[k - 1][c_c][c_m]) {
            c_c--;
            c_m -= shift[k];
            res.push_back(k);
        }
        k--;
    }

    for (int r = res.size() - 1; r >= 0; r--) {
        cout << res[r] << ' ';
    }
    cout << '\n';
    return 0;
}
