#ifndef UCCON_HPP
#define UCCON_HPP

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include "Vertex.hpp"

using namespace std;

class Uccon {
public:
    string pattern;
    string str_2;
    Vertex * root, * activeNode, * link;
    // int numStr;
    int remaining, activeLen;
    string::iterator activeEdge;

    int num_max_substring;
    vector <LCS> answer;
    LCS ans; // prev version (with only one substring)

    Uccon(string patt_1, string patt_2);
    void Add(string::iterator symbol);
    void Sufflink(Vertex *node);
    int Markup(Vertex * node);
    void FindNumMax(Vertex * node, int walk);
    void FindLongestSubstrings(Vertex * node, int walk, Vertex * begin, vector <Vertex *> path_to_sub);

    // void Destroy(Vertex * node);
    ~Uccon();
};

Uccon::Uccon(string patt_1, string patt_2) : remaining(0), activeLen(0), num_max_substring(0) {
    this->pattern = patt_1;
    this->str_2 = patt_2;
    this->activeEdge = pattern.begin();
    this->root = new Vertex(pattern.end(), pattern.end());
    this->root->suff_link = this->root;
    this->activeNode = this->root;
    this->link = this->root;
    ans.length = 0;
    ans.begining = nullptr;
    ans.ending = nullptr;

    for (string::iterator symbol = pattern.begin(); symbol != pattern.end(); symbol++) {
        Add(symbol); // adding new sumbol
    }

    Markup(root);

    FindNumMax(root, 0);
    vector <Vertex *> path_to_sub;
    FindLongestSubstrings(root, 0, root, path_to_sub);
    list <string> answer_string;

    int size_answer = answer.size();
    for (int i = 0; i < size_answer; i++) {
        string a_string;
        int size_answer_path_to_subs = answer[i].path_to_subs.size();
        for(int j = 0; j < size_answer_path_to_subs; j++) {
            string next_string(answer[i].path_to_subs[j]->begin, answer[i].path_to_subs[j]->end + 1);
            a_string += next_string;
        }
        answer_string.push_back(a_string);
    }

    answer_string.sort();
    cout << num_max_substring << "\n";
    for (list<string>::iterator i = answer_string.begin(); i != answer_string.end(); i++) {
        cout << *i << "\n";
    }
}

void Uccon::FindNumMax(Vertex * node, int walk) {
    if (node->number_string.size() == 2) {
        if (node != root) {
            walk += distance(node->begin, node->end) + 1;
            if (walk > num_max_substring) {
                num_max_substring = walk;
            }
        }
        for (map<char, Vertex *>::iterator n = node->child.begin(); n != node->child.end(); n++) {
            Vertex * next_child = n->second;
            FindNumMax(next_child, walk);
        }
    }
}

void Uccon::FindLongestSubstrings(Vertex *node, int walk, Vertex *begin, vector <Vertex *> path_to_sub) {
    if (node->number_string.size() == 2) {
        if (node != root) {
            if (walk == 0) {
                path_to_sub.clear();
            }
            path_to_sub.push_back(node);
            walk += distance(node->begin, node->end) + 1;
            if (walk == num_max_substring) {
                ans.path_to_subs = path_to_sub;
                ans.length = walk;
                answer.push_back(ans);
                path_to_sub.clear();
            }
        }
        for (map<char, Vertex *>::iterator n = node->child.begin(); n != node->child.end(); n++) {
            Vertex * next_child = n->second;
            FindLongestSubstrings(next_child, walk, begin, path_to_sub);
        }
    }
}

int Uccon::Markup(Vertex * node) {
    if (node->begin != pattern.end()) {
        if(*node->begin == '#')
            node->number_string.insert(1);
        else if(*node->begin == '$')
            node->number_string.insert(2);
    }

    if(distance(node->begin, node->end) > 0) {
        int size_str = str_2.size();
        if (distance(node->begin, node->end) > size_str) {
            node->number_string.insert(1);
        } else if (node->end == pattern.end()) {
            node->number_string.insert(2);
        }
    }

    for (map<char, Vertex *>::iterator it2 = node->child.begin(); it2 != node->child.end(); it2++) {
        Vertex * next_child = it2->second;
        int ans = Markup(next_child);
        if (node->number_string.size() < 2) {
            if (ans == 3) {
                node->number_string.insert(1);
                node->number_string.insert(2);
            }
            if (ans == 1) {
                node->number_string.insert(1);
            }
            if (ans == 2) {
                node->number_string.insert(2);
            }
        }
    }

    if (node->number_string.size() == 2) {
        return 3;
    }
    if (node->number_string.size() == 1) {
        if(*node->number_string.begin() == 1) {
            return 1;
        }
        if(*node->number_string.begin() == 2) {
            return 2;
        }
    }
    return 0;
}

void Uccon::Add(string::iterator symbol) {
    link = root;
    remaining++;

    while (remaining) {

        if (!activeLen) {
            activeEdge = symbol;
        }

        map <char, Vertex *>::iterator it1 = activeNode->child.find(* activeEdge);

        if (it1 == activeNode->child.end()) { // dont find edge
            Vertex * n_node = new Vertex(symbol, pattern.end()); // new leaf
            activeNode->child[*activeEdge] = n_node;
            Sufflink(activeNode);
        } else { // find edge
            Vertex * after = it1->second;
            // Jump
            int length = after->end - after->begin + 1;

            if (activeLen >= length) {
                activeEdge += length;
                activeLen -= length;
                activeNode = after;
                continue;
            }

            // Rule 3 extention
            if (*(after->begin + activeLen) == *symbol) {
                activeLen++;
                Sufflink(activeNode);
                //show stopper
                break;
            }

            // Rule 2 extention
            Vertex * split = new Vertex(after->begin, after->begin + activeLen - 1);
            Vertex * leaf = new Vertex(symbol, pattern.end());
            activeNode->child[* activeEdge] = split;
            split->child[* symbol] = leaf;
            after->begin += activeLen;
            split->child[* after->begin] = after;
            Sufflink(split);
        }

        remaining--;

        if (activeNode == root && activeLen != 0){
            activeLen--;
            activeEdge++;
        } else {
            if (activeNode->suff_link) {
                activeNode = activeNode->suff_link;
            } else {
                activeNode = root;
            }
        }

    }
}

void Uccon::Sufflink(Vertex * node) {
    if (link != root)
        link->suff_link = node;
    link = node;
}

Uccon::~Uccon() {
    delete root;
}

#endif
