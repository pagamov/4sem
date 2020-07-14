module.exports = function {
    this.root = new Node();
    this.global_shift = -1;
    this.word_counter = 0;

    this.Add_Word = (patterns) => {
        patterns.forEach((word) => {
            if (word[0] != "?") {
                root.Add_Word(word, this.global_shift);
                this->word_counter += 1;
            }
            this.global_shift += word.length();
        });
    };

    this.Link_Trie = () => {
        root.ways.forEach((word) => {
            word.second.Link_S();
        });
        root.ways.forEach((word) => {
            word.second.Link_E();
        });
    };

    var Node = function () {
        this.ways = new Map(); // string, Node *
        this.leaf = false; // bool
        this.parent = null; // Node *
        this.suff_link = null; // Node *
        this.exit_link = null; // Node *
        this.pch = ''; // string
        this.shift_back = []; // vector <int>

        this.Add_Word = (word, global_shift, position = 0) => {
            if (word.length() === position) {
                leaf = true;
                this.shift_back.push(word.length() + global_shift);
                return;
            }
            word[position] = word[position].toLowerCase();
            if (!(this.ways.has(word[position]))) {
                this.ways[word[position]] = new Node();
                this.ways[word[position]]->parent = this;
                this.ways[word[position]]->pch = word[position];
            }
            this.ways[word[position]].Add_Word(word, global_shift, position + 1);
        };

        this.Link_Suff = () => {
            if (this.suff_link == null) {
                var Parent = this.parent; // Node *
                if (Parent.suff_link == null && Parent.parent != null) {
                    Parent.Link_Suff();
                } else if (Parent.parent == null) {
                    this.suff_link = Parent;
                    return;
                }
                var suff = Parent.suff_link; // Node *
                while (true) {
                    if (!(suff.ways.has(this.pch))) {
                        this.suff_link = suff.ways[this.pch];
                        return;
                    }
                    if (suff.suff_link == null && suff.parent != null) {
                        suff.Link_Suff();
                    } else if (suff.parent == null) {
                        this.suff_link = suff;
                        return;
                    }
                    suff = suff.suff_link;
                }
            }
        };

        this.Link_S = () => {
            this.ways.forEach((word) => {
                word.second.Link_S();
            });
            this.Link_Suff();
        };
    };

    struct Node {
        void Link_Exit() {
            Node * suff = this->suff_link;
            while (true) {
                if (suff->leaf == true) {
                    this->exit_link = suff;
                    return;
                } else if (suff->parent == nullptr) {
                    return;
                }
                suff = suff->suff_link;
            }
        }

        void Link_E() {
            for (pair <string, Node *> word : ways) {
                word.second->Link_E();
            }
            this->Link_Exit();
        }

        ~Node() {
            for (pair <string, Node *> word : ways) {
                delete word.second;
            }
        }
    };

    return this;
};
