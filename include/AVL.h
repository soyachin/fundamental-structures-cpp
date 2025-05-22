#ifndef AVL_H
#define AVL_H

#include <type_traits>
template<typename T>
struct Node {
    T data;
    Node<T>* right;
    Node<T>* left;
    int height; // necesitamos guardar height pq siempre va a ser consultada

    explicit Node<T>(T d) : data(d), right(nullptr), left(nullptr){}

};

template<typename T>
class AVL {
    private:
        Node<T>* root;
    public:
        AVL() : root(nullptr) {}
        void insert(T value) {
            root = insert(root,value);   
        }
        bool remove (T value){
            return bool(root, value);
        }
        
        std::size_t height() const {
            return height(root);
        }        


    private:
        int height(Node<T>* node){
            return node ? node->height : 0;
        }

        int balanceFactor(Node<T>* node) const {
            return node ? height(node->left) - height(node->right) : 0;
        }

        Node<T>* rotateRight(Node<T>* y) {
            Node<T>* x = y->left;
            Node<T>* T2 = x->right;

            // Perform rotation
            x->right = y;
            y->left = T2;
        
            // Update heights
            updateHeight(y);
            updateHeight(x);
        
            return x;
        }

        Node<T>* rotateLeft(Node<T>* x) {
            Node<T>* y = x->right;
            Node<T>* T2 = y->left;

        // Perform rotation
            y->left = x;
            x->right = T2;

        // Update heights
            updateHeight(x);
            updateHeight(y);

            return y;
        }

   Node<T>* insert(Node<T>* node, T value) {
        // 1. Perform the normal BST insertion
        if (!node) return new Node<T>(value);

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node;  // Duplicate values not allowed
        }

        // 2. Update height of this ancestor node
        updateHeight(node);

        // 3. Get the balance factor to check if unbalanced
        int balance = balanceFactor(node);

        // 4. If unbalanced, perform rotations

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
        
        
        
        

        void insert(Node<T>* node, T value){
            
        }

        bool remove(Node<T>* node, T value){
            return false;
        }

        void updateHeight(Node<T>* node){
            if (node) {
                node->height = 1 + std::max(height(node->left), height(node->right));
            }
        }



};
        

#endif // AVL_H
