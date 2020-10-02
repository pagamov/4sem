#include <iostream>
#include <string>
#include <map>
#include "bigint.hpp"

using namespace std;

enum {
    ADD,SUB,MULT,POW,DEL,
    GT,IT,EQ
};

map <string, int> arr { {"+", ADD}, {"-", SUB}, {"*", MULT}, {"^", POW}, {"/", DEL}, {">", GT}, {"<", IT}, {"=", EQ} };

int main () {
    BigInt A, B;
    string oper;
    while (cin >> A >> B >> oper) {

        switch (arr[oper]) {
            case ADD:
                try {
                    cout << A + B << "\n";
                } catch (...) {
                    cout << "Error\n";
                }
                break;
            case SUB:
                try {
                    cout << A - B << "\n";
                } catch (...) {
                    cout << "Error\n";
                }
                break;
            case MULT:
                try {
                    cout << A * B << "\n";
                    // cout << A << "\n" << B << "\n";
                } catch (...) {
                    cout << "Error\n";
                }
                break;
            case POW:
                try {
                    cout << (A ^ B) << "\n";
                } catch (...) {
                    cout << "Error\n";
                }
                break;
            case DEL:
                try {
                    cout << A / B << "\n";
                } catch (...) {
                    cout << "Error\n";
                }
                break;
            case GT:
                A > B ? cout << "true\n" : cout << "false\n";
                break;
            case IT:
                A < B ? cout << "true\n" : cout << "false\n";
                break;
            case EQ:
                A == B ? cout << "true\n" : cout << "false\n";
                break;
        }

    }
    return 0;
}
