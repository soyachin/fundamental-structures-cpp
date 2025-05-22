#include <exception>
#include <stack>
#include <iostream>
#include <type_traits>
#include <queue>

using namespace std;


template<typename T>
struct NodeBT {
    T data;
    NodeBT<T>* right;
    NodeBT<T>* left;

    explicit NodeBT<T>(T d) : data(d), right(nullptr), left(nullptr) {}
};

template <typename T>
class BSTIterator
{
private:
    NodeBT<T> *current;
    stack<NodeBT<T> *> stack;

public:
    BSTIterator() : current(nullptr){};

    BSTIterator(NodeBT<T> *node)
    {
        while (node != nullptr) {
            this->stack.push(node);
            node = node->left;
        }
        this->current = this->stack.empty() ? nullptr : stack.top();
    }

    BSTIterator<T> &operator++()
    {
        if (this->stack.empty())
            throw std::out_of_range("It's not possible");

        NodeBT<T> *node = this->stack.top();
        this->stack.pop();
        node = node->right;
        while (node != nullptr) {
            this->stack.push(node);
            node = node->left;
        }
        this->current = this->stack.empty() ? nullptr : stack.top();
        return *this;
    }

    BSTIterator<T> &operator=(BSTIterator<T> other)
    {
        this->current = other->current;
        this->stack = other.stack;
        return (*this);
    }

    bool operator!=(BSTIterator<T> other)
    {
        return this->current != other.current;
    }

    T operator*()
    {
        if (this->current != nullptr)
            return this->current->data;
        throw std::out_of_range("Current is NULL");
    }
};


template <typename T>
class BSTree
{
public:
    typedef BSTIterator<T> iterator;

private:
    NodeBT<T> *root;

public:
    BSTree() : root(nullptr) {}

    void insert(T value)
    {
        insert(this->root, value);
    }

    void displayInOrder(){
        displayInOrder(this->root);
    }

    void displayPostOrder(){
        displayPostOrder(this->root);
    }

    void displayPreOrder(){
        displayPreOrder(this->root);
    }

  
    iterator begin(){
        return iterator(this->root);
    }

    iterator end(){
        return iterator();
    }

    bool remove (T value) {
        return remove(root, value);
    }

    void dfs(NodeBT<T>* &node){
        stack<NodeBT<T>*> stack;
        NodeBT<T>* current = this->root;
        while(current != nullptr || !stack.empty()){
            while(current != nullptr) {
                stack.push(current);
                current = current->left;
            }                
            current = stack.top();                
            stack.pop();
            cout<<current->data<<","; 
            current = current->right;
        }
    }

    
    void bfs(NodeBT<T>* &node){
        if (node == nullptr) return;
        
        queue<NodeBT<T>*> q;

        q.push(root);
        while (!q.empty) {
            NodeBT<T>* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left != nullptr){
                q.push(current->left);
            }
            if (current->right != nullptr){
                q.push(current->right);
            }

        }

        cout << endl;

    }


    bool contains(NodeBT<T>* node, T value) const {
        if (!node) return false;
        if (value == node->data) return true;
        return value < node->data ? contains(node->left, value) : contains(node->right, value);
    }

    size_t size(NodeBT<T>* node) const {
        return node ? 1 + size(node->left) + size(node->right) : 0;
    }

    size_t height(NodeBT<T>* node) const {
        if (!node) return -1;  // Base case for empty tree
        return 1 + std::max(height(node->left), height(node->right));
    }

    NodeBT<T>* min(NodeBT<T>* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    NodeBT<T>* max(NodeBT<T>* node) const { // 
        while (node && node->right) node = node->right;
        return node;
    }


    int getLevel(T value) const {
        return findLevel(root, value, 0);
    }

private:
    void insert(NodeBT<T> *&node, T value) {
        if (node == nullptr) node = new NodeBT<T>(value); // si el nodo está vacío crea un nuevo nodo
        else if (value < node->data) insert(node->left, value); // si el valor es menor al valor del nodo, se inserta de forma recursiva a la izquierda
        else insert(node->right, value); // si el valor es mayor se inserta de forma recursiva a la derecha
    }

    void displayInOrder(NodeBT<T>* &node){
        if(node == nullptr) return;

        displayInOrder(node->left);
        cout<<node->data<<",";
        displayInOrder(node->right);
    }

    void displayPostOrder(NodeBT<T>* &node){
        if (node == nullptr) return;

        displayPostOrder(node->left);
        displayPostOrder(node->right);
        cout << node->data << ",";
    }

    void displayPreOrder(NodeBT<T>* &node){
        if (node == nullptr) return;

        cout << node->data << ",";
        displayPreOrder(node->left);
        displayPreOrder(node->right);
    }


    bool remove(NodeBT<T>* &node, T value){
        // caso base
        if (node == nullptr) return false;

        if (value < node->data) { // si el valor es menor debemos ir a la izq!
            return remove(node->left, value); // moverse a la izq en remove!                            
        }

        else if (value > node->data) {
            return remove(node->right, value); //moverse a la derecha porque es mayor
        }

        else { // nodo->data == value !!!!
            // caso 1: el nodo no tiene hijos
            if (node->left = nullptr && node->right == nullptr) {
                delete node; 
                node = nullptr;
            }
            
            // caso 2: nodo tiene 1 hijo
            else if (node->left == nullptr) {
                NodeBT<T>* temp = node; 
                node = node->right;
                delete temp;
            }

            else if (node->right == nullptr) {
                NodeBT<T>* temp = node;
                node = node->left;
                delete temp;
            }
            
            // caso 3: tiene 2 hijos
            else {
                NodeBT<T>* temp = findMin(node->right);
                node->data = temp->data;
                remove(node->right, temp->data);
            }

            return true;

        }

    }

    NodeBT<T>* findMin(NodeBT<T>* node){
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    int findLevel(NodeBT<T>* node, T value, int currentLevel) const {
        if (!node) return -1; // Node not found
        
        if (value == node->data) {
            return currentLevel;
        }
        else if (value < node->data) {
            return findLevel(node->left, value, currentLevel + 1);
        }
        else {
            return findLevel(node->right, value, currentLevel + 1);
        }
    }
    
    
};


int main()
{
    BSTree<int> *bstree = new BSTree<int>();
    bstree->insert(8);
    bstree->insert(3);
    bstree->insert(1);
    bstree->insert(6);
    bstree->insert(4);
    bstree->insert(7);
    bstree->insert(10);
    bstree->insert(14);
    bstree->insert(13);
    cout<<endl;

    /*-----------------------iterator---------------------------------*/
    string result = "";
    BSTree<int>::iterator ite = bstree->begin();
    while(ite != bstree->end()) {
        cout<<*ite<<",";
        ++ite;
    }   
    cout<<endl;

    return 0;
}
