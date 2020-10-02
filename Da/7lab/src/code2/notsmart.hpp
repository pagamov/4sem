#ifndef notsmart_hpp
#define notsmart_hpp

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;

int MAX = 100;
int PETS = 100;

class Notsmart_obj {
public:

    Notsmart_obj() {
        w = 0;
        size = 0;
    }

    Notsmart_obj(int n, int w) {
        this->things = vector <int> (n, rand() % 2);
        // for (int i : things) {
        //     i = rand() % 2;
        // }
        size = n;
        this->w = w;
    }

    Notsmart_obj Merge(Notsmart_obj &l) {
        Notsmart_obj res(size, w);
        for (int i = 0; i < size; i++) {
            if (i < size / 2) {
                res.things[i] = things[i];
            } else {
                res.things[i] = l.things[i];
            }
        }
        return res;
    }

    void Mutate(int rate = 1) {
        int chose;
        for (int i = 0; i < rate; i++) {
            chose = rand() % size;
            if (things[chose] == 0) {
                things[chose] = 1;
            } else {
                things[chose] = 0;
            }
        }
    }

    int Distance(vector <pair <int, int>> & items, int max_w) {
        int res = 0;
        int mass = 0;
        int count = 0;

        for (int i = 0; i < size; i++) {
            if (things[i] == 1) {
                res += items[i].second;
                // cout << "item " << items[i].first << "\n";
                count++;
                mass += items[i].first;
            }
        }

        // cout << "dis count in : " << res * count << "\n";

        if (mass > max_w) {
            return -res * count;
        } else {
            return res * count;
        }
    }

    ~Notsmart_obj() = default;

    vector<int> things;
    int size;
    int w;
};


class Notsmart : Notsmart_obj {
public:
    Notsmart(int n, int w) {
        this->n = n;
        this->max_w = w;
        srand(time(0));
        for (int i = 0; i < PETS; i++) {
            pets.push_back(Notsmart_obj(n, w));
        }
        items = vector <pair<int, int>>(n);
        int a_1, b_1;
        // cout << "enter please\n";
        for (int i = 0; i < n; i++) {
            cin >> a_1 >> b_1;
            items[i] = make_pair(a_1, b_1);

            // cout << "item : " << i << " " << items[i].first << " " << b_1 << "\n";
        }
        Find_res();
    }

    void Find_res() {
        int glob_max = 0;
        int flag = 5;
        int max = 0;
        vector <pair<Notsmart_obj, int>> parents;
        while (flag > 0) {
            // cout << "new iteration!" << "\n";
            for (Notsmart_obj obj : pets) {
                int r = obj.Distance(items, max_w);

                // for (int var : obj.things) {
                //     cout << var << " ";
                // }
                // cout << "dis : " << r << "\n";

                if (r > max) {
                    max = r;
                    glob_max = max;
                    flag = 5;
                }
                if (parents.size() < 2) {
                    parents.push_back(make_pair(obj, r));
                } else {
                    if (r > parents[0].second) {
                        parents[0].first = obj;
                        parents[0].second = r;
                    } else if (r > parents[1].second) {
                        parents[1].first = obj;
                        parents[1].second = r;
                    }
                }
            }

            if (glob_max == max) {
                flag--;

                if (flag == 0) {
                    if (parents.size() == 0) {
                        cout << "no solution!\n";
                    } else if (parents.size() == 1) {
                        cout << parents[0].second << "\n";
                        for (int i = 0; i < parents[0].first.things.size(); i++) {
                            if (parents[0].first.things[i] == 1) {
                                cout << i + 1 << " ";
                            }
                        }
                        cout << "\n";
                    } else {
                        if (parents[0].second > parents[1].second) {
                            cout << parents[0].second << "\n";
                            for (int i = 0; i < parents[0].first.things.size(); i++) {
                                if (parents[0].first.things[i] == 1) {
                                    cout << i + 1 << " ";
                                }
                            }
                            cout << "\n";
                        } else {
                            cout << parents[1].second << "\n";
                            for (int i = 0; i < parents[1].first.things.size(); i++) {
                                if (parents[1].first.things[i] == 1) {
                                    cout << i + 1 << " ";
                                }
                            }
                            cout << "\n";
                        }
                    }
                    return;
                }
            }

            if (parents.size() == 0) {
                for (int a = 0; a < pets.size(); a++) {
                    pets[a].Mutate();
                }
            } else if (parents.size() == 1) {
                for (int a = 0; a < pets.size(); a++) {
                    pets[a].Mutate();
                }
            } else {
                pets[0] = parents[0].first.Merge(parents[1].first);
                pets[1] = parents[0].first;
                pets[2] = parents[1].first;

                for (int a = 3; a < pets.size(); a++) {
                    pets[0].Mutate();
                    pets[a] = pets[0];
                }
            }

            // cout << "record : " << max << " !\n";

            parents.clear();
        }


    }

    ~Notsmart() = default;

    vector <Notsmart_obj> pets;
    vector <pair<int, int>> items;
    int n;
    int max_w;
};

#endif
