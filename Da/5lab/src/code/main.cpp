#include <iostream>
#include <sstream>
#include "uccon.hpp"

using namespace std;

int main() {

    string input, input_1, input_2;

    getline(cin, input);
    std::istringstream iline(input);

    iline >> input_1;

    getline(cin, input);
    std::istringstream jline(input);

    jline >> input_2;

    Uccon uccon(input_1, input_2);

    // uccon.Print();

    return 0;
}
