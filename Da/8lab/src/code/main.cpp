#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool comp(int& first, int& second) {
    return first > second;
}

bool check_if_valid(const int& s_1, const int& s_2, const int& s_3) {
    if ((s_1 < (s_2 + s_3)) && (s_2 < (s_1 + s_3)) && (s_3 < (s_1 + s_2))) {
        return true;
    } else {
        return false;
    }
}

double area(int s_1, int s_2, int s_3) {
    double p = 0.5 * (s_1 + s_2 + s_3);
    double area = sqrt(p) * sqrt(p - s_1) * sqrt(p - s_2) * sqrt(p - s_3);
    return area;
}

int main() {
    vector <int> data;
    int n, side, s_1 = 0, s_2 = 0, s_3 = 0;
    double maxArea = 0, curArea;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> side;
        data.push_back(side);
    }

    sort(data.begin(), data.end(), comp);

    for (int i = 1; i < int(data.size() - 1); ++i) {
        if (data.size() < 3) {
            break;
        }
        if (check_if_valid(data[i - 1], data[i], data[i + 1])) {
            curArea = area(data[i - 1], data[i], data[i + 1]);
            if (curArea > maxArea) {
                maxArea = curArea;
                s_1 = data[i + 1];
                s_2 = data[i];
                s_3 = data[i - 1];
            }
        }
    }
    if (maxArea == 0) {
        cout << 0 << '\n';
    } else {
        printf("%.3f\n", maxArea);
        cout << s_1 << ' ' << s_2 << ' ' << s_3 << '\n';
    }
    return 0;
}
