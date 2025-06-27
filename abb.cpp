#include <iostream>
#include <string>
using namespace std;

// Classe Pair
template <typename Key, typename T>
class Pair {
private:
    Key key;
    T value;

public:
    Pair() = default;
    Pair(const Key& k, const T& v) : key(k), value(v) {}

    Key getKey() const { return key; }
    T getValue() const { return value; }

    void setKey(const Key& k) { key = k; }
    void setValue(const T& v) { value = v; }

    bool operator<(const Pair& other) const {
        return key < other.key;
    }

    bool operator>(const Pair& other) const {
        return key > other.key;
    }

    bool operator==(const Pair& other) const {
        return key == other.key;
    }
};

// Classe BinarySearchTree
template <typename Key, typename T>
class BinarySearchTree {
private:
    class Node {
    public:
        Pair<Key, T> item;
        Node* left;
        Node* right;

        Node(const Pair<Key, T>& p) : item(p), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const Pair<Key, T>& item);
    Node* remove(Node* node, const Key& key);
    Node* findMin(Node* node);
    bool search(Node* node, const Key& key, T& value);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void destroy(Node* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(const Pair<Key, T>& item);
    void remove(const Key& key);
    bool search(const Key& key, T& value);
    void inOrder();
    void preOrder();
    void postOrder();
};

// Implementações da BinarySearchTree

template <typename Key, typename T>
BinarySearchTree<Key, T>::BinarySearchTree() : root(nullptr) {}

template <typename Key, typename T>
BinarySearchTree<Key, T>::~BinarySearchTree() {
    destroy(root);
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::insert(const Pair<Key, T>& item) {
    root = insert(root, item);
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::Node* BinarySearchTree<Key, T>::insert(Node* node, const Pair<Key, T>& item) {
    if (!node)
        return new Node(item);

    if (item < node->item)
        node->left = insert(node->left, item);
    else if (item > node->item)
        node->right = insert(node->right, item);
    else
        cerr << "Erro: chave já existe.\n";

    return node;
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::remove(const Key& key) {
    root = remove(root, key);
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::Node* BinarySearchTree<Key, T>::remove(Node* node, const Key& key) {
    if (!node)
        return nullptr;

    if (key < node->item.getKey()) {
        node->left = remove(node->left, key);
    } else if (key > node->item.getKey()) {
        node->right = remove(node->right, key);
    } else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            Node* temp = findMin(node->right);
            node->item = temp->item;
            node->right = remove(node->right, temp->item.getKey());
        }
    }

    return node;
}

template <typename Key, typename T>
typename BinarySearchTree<Key, T>::Node* BinarySearchTree<Key, T>::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

template <typename Key, typename T>
bool BinarySearchTree<Key, T>::search(const Key& key, T& value) {
    return search(root, key, value);
}

template <typename Key, typename T>
bool BinarySearchTree<Key, T>::search(Node* node, const Key& key, T& value) {
    if (!node)
        return false;

    if (key < node->item.getKey())
        return search(node->left, key, value);
    else if (key > node->item.getKey())
        return search(node->right, key, value);
    else {
        value = node->item.getValue();
        return true;
    }
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::inOrder() {
    inOrder(root);
    cout << endl;
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::inOrder(Node* node) {
    if (node) {
        inOrder(node->left);
        cout << node->item.getKey() << ": " << node->item.getValue() << " ";
        inOrder(node->right);
    }
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::preOrder() {
    preOrder(root);
    cout << endl;
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::preOrder(Node* node) {
    if (node) {
        cout << node->item.getKey() << ": " << node->item.getValue() << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::postOrder() {
    postOrder(root);
    cout << endl;
}

template <typename Key, typename T>
void BinarySearchTree<Key, T>::postOrder(Node* node) {
    if (node) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->item.getKey() << ": " << node->item.getValue() << " ";
    }
}

// Função principal
int main() {
    BinarySearchTree<int, string> arvore;

    arvore.insert(Pair<int, string>(10, "dez"));
    arvore.insert(Pair<int, string>(5, "cinco"));
    arvore.insert(Pair<int, string>(15, "quinze"));
    arvore.insert(Pair<int, string>(8, "oito"));
    arvore.insert(Pair<int, string>(3, "três"));

    cout << "Percurso em ordem (inOrder): ";
    arvore.inOrder();

    cout << "Pré-ordem: ";
    arvore.preOrder();

    cout << "Pós-ordem: ";
    arvore.postOrder();

    string resultado;
    if (arvore.search(8, resultado))
        cout << "Chave 8 encontrada: " << resultado << endl;
    else
        cout << "Chave 8 não encontrada." << endl;

    arvore.remove(5);
    cout << "In-Order após remover chave 5: ";
    arvore.inOrder();

    return 0;
}
