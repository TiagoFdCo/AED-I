#include <iostream>
#include <stdlib.h>

using namespace std;

//NODE------------------------------------------------------------------------------------------------------------------------------------
template<typename T, typename Key>
class Node{
private:
    T item;

public:
    Node<T, Key>* pLeft;
    Node<T, Key>* pRight;

    Node(): item(T{}), pLeft(nullptr), pRight(nullptr) {}
    Node(T value): item(value), pLeft(nullptr), pRight(nullptr){}

    T getItem();
    void setItem(T value);
};

template<typename T, typename Key>
T Node<T, Key>::getItem(){
    return item;
}

template<typename T, typename Key>
void Node<T, Key>::setItem(T value){
    item = value;
}

//PAIR------------------------------------------------------------------------------------------------------------------------------------
template<typename T, typename Key>
class Pair{
private:
    Key chave;
    T value;

public:
    Pair(){}
    Pair(Key key, T item) : chave(key), value(item) {}

    Key getKey() const;
    T getValue() const;

    friend ostream& operator <<(ostream& os, const Pair<T, Key>& p){
    os << "(" << p.getKey() << ", " << p.getValue() << ")";
    return os;
}
};

template<typename T, typename Key>
Key Pair<T, Key>::getKey() const{
    return chave;
}

template<typename T, typename Key>
T Pair<T, Key>::getValue() const{
    return value;
}

//AROVRE BINARIA DE BUSCA----------------------------------------------------------------------------------------------------------------
template<typename T, typename Key>
class Tree{
private:
    Node<T, Key>* root;

    void insert(T& item, Node<T, Key>*& p);
    void remove(T& item, Node<T, Key>*& p);
    void remove_aux(Node<T, Key>*& p, Node<T, Key>*& q);
    void search(T& item, Node<T, Key>*& p);
    void preorderTraversal(Node<T, Key>*& p);
    void inorderTraversal(Node<T, Key>*& p);
    void postorderTraversal(Node<T, Key>*& p);

public:
    Tree(): root(nullptr) {}

    void insert(Key key, T& item);
    bool remove(Key key);
    bool search(Key key, T& item);
    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();

};
//-----------------------------------------------------METODOS PRIVADOS--------------------------------

template<typename T, typename Key>
void Tree<T, Key>::insert(T& item, Node<T, Key>*& p){
    if(p == nullptr){
        p = new Node<T, Key>(item);
        p->pLeft = nullptr;
        p->pRight = nullptr;
    }else if(item.getKey() < p->getItem().getKey()){
        insert(item, p->pLeft);
    }else if(item.getKey() > p->getItem().getKey()){
        insert(item, p->pRight);
    }else{
        throw runtime_error("Item já existe na ABB");
    }
}

template<typename T, typename Key>
void Tree<T, Key>::remove(T& item, Node<T, Key>*& p){
    if(p == nullptr){
        throw runtime_error("ITEM NAO EXISTE NA ARVORE");
    }else if(item.getKey() < p->getItem().getKey()){
        remove(item, p->pLeft);
    }else if(item.getKey() > p->getItem().getKey()){
        remove(item, p->pRight);
    }else if(p->pRight == nullptr){
        Node<T, Key>* aux = p;
        p = p->pLeft;
        delete aux; 
    }else if(p->pLeft == nullptr){
        Node<T, Key>* aux = p;
        p = p->pRight;
        delete aux; 
    }else{
        remove_aux(p, p->pLeft);
    }
}

template<typename T, typename Key>
void Tree<T, Key>::remove_aux(Node<T, Key>*& p, Node<T, Key>*& q){
    if(q->pRight != nullptr){
        remove_aux(p, q->pRight);
    }else{
        p->setItem(q->getItem()); 
        Node<T, Key>* aux = q;
        q = q->pLeft;
        delete aux;
    }
}

template<typename T, typename Key>
void Tree<T, Key>::search(T& item, Node<T, Key>*& p){
    if (p == nullptr){
        throw runtime_error("Item nao encontrado");
    }else if(item.getKey() < p->getItem().getKey()){
        search(item, p->pLeft);
    }else if(item.getKey() > p->getItem().getKey()){
        search(item, p->pRight);
    }else{
        item = p->getItem();
    }
}

template<typename T, typename Key>
void Tree<T, Key>::preorderTraversal(Node<T, Key>*& p){
    if (p != nullptr){
        cout << p->getItem() << " ";
        preorderTraversal(p->pLeft);
        preorderTraversal(p->pRight);
    }
}

template<typename T, typename Key>
void Tree<T, Key>::inorderTraversal(Node<T, Key>*& p){
    if(p != nullptr){
        inorderTraversal(p->pLeft);
        cout << p->getItem() << " ";
        inorderTraversal(p->pRight);
    }
}

template<typename T, typename Key>
void Tree<T, Key>::postorderTraversal(Node<T, Key>*& p){
    if(p != nullptr){
        postorderTraversal(p->pLeft);
        postorderTraversal(p->pRight);
        cout << p->getItem() << " ";
    }
}

//METODOS PUBLICOS------------------------------------------------------------------------------------------------------------------------
template<typename T, typename Key>
void Tree<T, Key>::insert(Key key, T& item){

    insert(item, root);
}

template<typename T, typename Key>
bool Tree<T, Key>::remove(Key key){
     T temp(key, "");
    try {
        remove(temp, root);
        return true;
    } catch (runtime_error&) {
        return false;
    }
}

template<typename T, typename Key>
bool Tree<T, Key>::search(Key key, T& item){
    T temp(key, "");
    try {
        search(temp, root);
        item = temp;
        return true;
    } catch (runtime_error&) {
        return false;
    }
}

template<typename T, typename Key>
void Tree<T, Key>::preorderTraversal(){
    preorderTraversal(root);
    cout << endl;
}

template<typename T, typename Key>
void Tree<T, Key>::postorderTraversal(){
    postorderTraversal(root);
    cout << endl;
}

template<typename T, typename Key>
void Tree<T, Key>::inorderTraversal(){
    inorderTraversal(root);
    cout << endl;
}

int main(){
    Tree<Pair<string, int>, int> arvore;

    Pair<string, int> p1(1, "um");
    Pair<string, int> p2(2, "dois");
    Pair<string, int> p3(3, "tres");

    arvore.insert(p1.getKey(), p1);
    arvore.insert(p2.getKey(), p2);
    arvore.insert(p3.getKey(), p3);

    cout << "Em ordem: ";
    arvore.inorderTraversal();

    Pair<string, int> buscado;
    if (arvore.search(2, buscado)) {
        cout << "Encontrado: " << buscado << endl;
    } else {
        cout << "Nao encontrado." << endl;
    }

    arvore.remove(2);
    cout << "Depois da remocao: ";
    arvore.inorderTraversal();


    return 0;
}
