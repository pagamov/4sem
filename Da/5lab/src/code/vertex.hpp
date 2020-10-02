#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
// #include <vector>
#include <string>
// #include <unordered_map>
#include <map>

using namespace std;

struct Vertex {

    int i, j;

    Vertex * parent;
    Vertex * suff_link;
    Vertex * root;

    map <char, Vertex *> childs;

    bool leaf, o_1, o_2;

    int * g_v;
    int * l_c;

    map <char, int> overlap;
    int max_size, max_count;

    Vertex() {}

    Vertex(int ** g_var, int ** l_count) : i(-1), j(-1), parent(nullptr), suff_link(nullptr), g_v(*g_var), l_c(*l_count) {
        this->fill_map();
        this->max_size = 0;
        this->max_count = 0;
        o_1 = false;
        o_2 = false;
        root = this;
    }

    Vertex(int start, int end, Vertex * dad) : Vertex(&(dad->g_v), &(dad->l_c)) {
        this->i = start;
        this->j = end;
        this->parent = dad;
        this->leaf = true;
        root = dad->root;
    }

    void fill_map() {
        for (int i = int('a'); i <= int('z'); i++) {
            this->overlap[char(i)] = 0;
        }
    }

    bool Is_Root() {
        if (this->i == -1 && this->j == -1) {
            return true;
        } else {
            return false;
        }
    }

    void Print_Tree(int deep, string &pattern) {
        if (this->Is_Root() != true) {
            for (int i = 0; i < deep; i++) {cout << '\t';}
            for (int i = this->i; i <= this->j; i++) {cout << pattern[i];}
            if (leaf) {cout << "...";}
            if (this->leaf != true) {cout << " " << this << " " << this->suff_link;}
            cout << endl;
        } else {
            cout << this << "\n";
        }
        for (pair <char, Vertex *> node : this->childs) {
            if (node.second != nullptr) {
                node.second->Print_Tree(deep + 1, pattern);
            } else {
                cout << "bad\n";
            }
        }
    }

    inline int Case(int start, int end) {
        if (this->Is_Root() == true) {
            return 1;
        } else if (end - start > this->j - this->i) {
            return 2;
        } else {
            return 3;
        }
    }

    void Case_1(int start, int end, string &pattern, Vertex * need_for_suff) {
        if (this->childs.find(pattern[start]) == this->childs.end()) {

            this->childs[pattern[start]] = new Vertex(start, this->g_v[0], this);

            this->l_c[0]++;

            this->Add_Word(start + 1, end, pattern, nullptr);

        } else {

            this->childs[pattern[start]]->Add_Word(start, end, pattern, need_for_suff);
        }
    }

    void Case_2(int start, int end, string &pattern, Vertex * need_for_suff) {

        int new_start = start + this->j - this->i + 1;

        if (this->childs.find(pattern[new_start]) != this->childs.end()) {

            this->childs[pattern[new_start]]->Add_Word(new_start, end, pattern, need_for_suff);

        } else {
            this->childs[pattern[new_start]] = new Vertex(new_start, this->g_v[0], this);
            this->l_c[0]++;

            if (need_for_suff != nullptr) {
                need_for_suff->suff_link = this;
            }

            if (this->parent->Is_Root()) {

                this->parent->Add_Word(start + 1, end, pattern, nullptr);

            } else {

                this->parent->suff_link->childs[pattern[start]]->Add_Word(start, end, pattern, nullptr);

            }
        }
    }

    void Case_3(int start, int end, string &pattern, Vertex * need_for_suff) {
        for (int count = 0; count <= end - start; count++) {
            if (pattern[this->i + count] != pattern[start + count]) {
                Vertex * new_me = new Vertex(this->i, this->i + count - 1, this->parent);
                new_me->leaf = false;
                new_me->parent->childs[pattern[new_me->i]] = new_me;
                this->i += count;
                this->parent = new_me;
                Vertex * ptr = new Vertex(start + count, this->g_v[0], new_me);
                this->l_c[0]++;

                new_me->childs[pattern[new_me->i + count]] = this;
                new_me->childs[pattern[start + count]] = ptr;

                if (need_for_suff != nullptr) {
                    need_for_suff->suff_link = new_me;
                }

                new_me->suff_link = this->root;

                if (new_me->parent->Is_Root()) {

                    new_me->parent->Add_Word(start + 1, end, pattern, new_me);

                } else {

                    new_me->parent->suff_link->childs[pattern[start]]->Add_Word(start, end, pattern, new_me);

                }
                return;
            }
        }

        if (need_for_suff != nullptr) {
            need_for_suff->suff_link = this->parent;
        }
    }

    void Add_Word(int start, int end, string &pattern, Vertex * need_for_suff) {
        if (start > end) {
            // cout << "add word end\n";
            return;
        }

        switch (this->Case(start, end)) {
            case 1: // создание нового нода или продолжение по старому для рута
                // cout << "add word case 1\n";
                this->Case_1(start, end, pattern, need_for_suff);
                break;
            case 2: // шагаем вглубь нода
                // cout << "add word case 2\n";
                this->Case_2(start, end, pattern, need_for_suff);
                break;
            case 3: // создание развилки
                // cout << "add word case 3\n";
                this->Case_3(start, end, pattern, need_for_suff);
                break;
        }
    }

    void Clean(int position) {
        if (this->Is_Root() != true) {

            if (this->leaf == true) {
                this->j = this->g_v[0];
            }

            if (position <= this->j && position >= this->i) {
                // senatinel is in the diapason of including
                // i <= pos <= j
                this->j = position;
                this->leaf = true;

                for (pair <char, Vertex *> v : this->childs) {
                    delete v.second;
                }

                this->childs.clear();

                return;
            }
        }

        for (pair <char, Vertex *> v : this->childs) {
            v.second->Clean(position);
        }
    }

    int Collect(int pos_1, int pos_2) {
        if (this->leaf) { // auto not root
            // leaf
            if (pos_1 <= this->j && pos_1 >= this->i) {
                return -1;
            } else if (pos_2 <= this->j && pos_2 >= this->i) {
                return -2;
            } else {
                cout << "ERROR" << endl;
                return -3;
            }
        }

        int piv;
        for (pair <char, Vertex *> node : this->childs) {
            piv = node.second->Collect(pos_1, pos_2);
            switch (piv) {
                case -1:
                    o_1 = true;
                    break;
                case -2:
                    o_2 = true;
                    break;
                default:
                    if (piv > this->max_size) {
                        this->max_size = piv;
                        o_1 = true;
                        o_2 = true;
                        this->max_count = 1;
                    } else if (piv == this->max_size) {
                        max_count++;
                    }
                    this->overlap[node.first] = piv;
                    break;
            }
        }

        if (this->o_1 && this->o_2) {
            if (this->Is_Root()) {
                return max_size;
            } else {
                return this->j - this->i + max_size + 1;
            }
        } else if (this->o_1) {
            return -1;
        } else if (this->o_2) {
            return -2;
        } else {
            return 0;
        }

        // return (this->o_1 && this->o_2) ? (this->Is_Root()) ? max_size : this->j - this->i + max_size + 1 : 0;

    }

    bool Output_Res(string &pattern) {
        if (this->Is_Root()) {
            for (int i = int('a'); i <= int('z'); i++) {
                if (this->overlap[char(i)] == this->max_size) {
                    if (this->childs[char(i)]->Output_Res(pattern) != true) {
                        i--;
                    }
                }
            }
        } else {
            for (int i = this->i; i <= this->j; i++) {
                printf("%c", pattern[i]);
            }
            if (this->max_count != 0) {
                for (int i = int('a'); i <= int('z'); i++) {
                    if (this->overlap[char(i)] == this->max_size) {
                        if (this->childs[char(i)]->Output_Res(pattern)) {
                            this->max_count -= 1;
                            this->overlap[char(i)] = 0;
                        }
                        if (this->max_count == 0) {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
            cout << "\n";
        }
        return true;
    }

    bool In_Tree(int start, int end, string &pattern) {
        if (this->Is_Root()) {
            for (pair <char, Vertex *> node : childs) {
                if (node.second == nullptr) {
                    cout << "dont have node\n";
                    return false;
                } else {
                    if (node.second->In_Tree(start, end, pattern) != true) {
                        return false;
                    }
                    return true;
                }
            }
        } else {
            if (this->leaf != true) {
                if (this->suff_link == nullptr) {
                    cout << "no suff link\n";
                    return false;
                } else {

                    if (this->Deep() != this->suff_link->Deep() + 1) {
                        cout << "suff len\n" << this->suff_link;
                        return false;
                    }


                }

                // if (this->suff_link->Is_Root() != true) {
                //     if (pattern[this->j] != pattern[this->suff_link->j]) {
                //         cout << "bad suff link " << this->suff_link << "\n";
                //         return false;
                //     }
                // }

                for (pair <char, Vertex *> node : childs) {
                    if (node.second == nullptr) {
                        cout << "dont have node\n";
                        return false;
                    } else {

                        if (node.second->In_Tree(start, end, pattern) != true) {
                            return false;
                        }
                        return true;

                    }
                }
            } else {
                return true;
            }
        }

        return true;
    }

    int Deep() {
        Vertex * ptr = this;
        int len = 0;
        while (ptr->Is_Root() != true) {
            len += ptr->j - ptr->i + 1;
            ptr = ptr->parent;
        }
        return len;
    }

    ~Vertex() {
        for (pair <char, Vertex *> node : this->childs) {
            delete node.second;
        }
    }

};

#endif
