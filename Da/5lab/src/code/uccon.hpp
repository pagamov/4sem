#ifndef UCCON_HPP
#define UCCON_HPP

#include <iostream>
#include <string>

#include "vertex.hpp"

using namespace std;

class Uccon : Vertex {
public:
    string pattern;
    Vertex * root;

    int len_1, len_2;

    // var needed for constant extent leaf nodes
    int * global_extention;
    int * leaf_count;

    Uccon(string &line_1, string &line_2) : pattern(line_1 + "%" + line_2 + "$") {
        len_1 = line_1.length();
        len_2 = line_1.length() + line_2.length() + 1;

        this->global_extention = new int;
        this->global_extention[0] = len_2;

        this->leaf_count = new int;
        this->leaf_count[0] = 0;

        this->root = new Vertex(&global_extention, &leaf_count);
        this->root->leaf = false;

        this->Build_Tree();
        // this->Clean_Nodes();
        // this->Collect_Nodes();
    }

    void Build_Tree() {
        int end = 0;
        int size = int(pattern.size());

        while (end != size) {
            // cout << "start " << this->leaf_count[0] + 2 << " end " << end + 2 << "\n";

            root->Add_Word(this->leaf_count[0], end, pattern, nullptr);

            // this->Print(nullptr);

            // if (this->Check_Tree(this->leaf_count[0], end) != true) {
            //     cout << "Error!\n";
            //     // this->Print();
            //     return;
            // }

            end++;
        }
    }

    void Clean_Nodes() {
        this->root->Clean(this->len_1);
    }

    void Collect_Nodes() {
        int res = this->root->Collect(this->len_1, this->len_2);
        cout << res << "\n";
        if (res == 0) {
            cout << "\n";
            return;
        } else if (res > 0) {
            this->root->Output_Res(this->pattern);
        } else {
            cout << "ERROR\n";
        }
    }

    bool Check_Tree(int start, int end) {
        for (int i = start; i <= end; i++) {
            if (this->root->In_Tree(i, end, pattern) != true) {
                return false;
            }
        }
        return true;
    }

    void Print(Vertex * piv) {
        // cout << "-" << endl;
        // cout << "piv " << piv << endl;
        cout << "-" << endl;
        this->root->Print_Tree(0, pattern);
        cout << "-" << endl;
    }

    ~Uccon() {
        delete this->leaf_count;
        delete this->global_extention;
        delete this->root;
    }

};

#endif
