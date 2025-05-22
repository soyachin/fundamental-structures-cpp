#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
using namespace std;


template<typename T>
class BTree {
    
    struct Node {
        T keys;
        Node** children;
        int count; // key counter
        bool isLeaf;
        int M;

        Node(int M = 4){
            this->M = M;
            children = new Node*[M];
            keys = new T[M-2];
            count = -1;
        };
    };

    Node* root;
    int M;

    public:
            // complejidad de range_search O(logN*k) -> se resuelve con un stack
    // este arbol requiere solo permite valores unicos (en BD permite valores repetidos)
        BTree() : root(nullptr), M(4) {}    
    
        BTree(Node* node = nullptr, int M = 4) {
            this->root = node;
            this->M = M;
        }

        bool search(T value);
        vector<T> range_search(T begin, T end);
        string toString() {
            string result = "";
            display_inorder(root, result);  
            return result;
        }

    private:

        void display_inorder(Node* node, string& result){ // pasar por referencia
            for(int i = 0 ; i < node->count ; ++i){
                if (!node->isLeaf)
                    result += display_inorder(node->children[i]);
                result += node->keys[i] << " ";
            }

            if (!node->isLeaf)
                result += display_inorder(node->children[node->count]);
            
        }

        


        
};

#endif //BTREE_H
