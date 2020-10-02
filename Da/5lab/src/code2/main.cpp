#include <iostream>
#include <string>
#include "Uccon.hpp"

using namespace std;

int main() {
    string str1, str2;
    while(cin >> str1 >> str2) {
        str1 += "#";
        str2 += "$";
        str1 += str2;
        Uccon tree(str1, str2);
    }
    return 0;
}
