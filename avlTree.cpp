#include <iostream>

using namespace std;

// NODE -------------------------------------------------------------------------
template<typename T, typename Key>
class Node {
private:
    T item;

public:
    Node<T, Key>* pLeft;
    Node<T, Key>* pRight;
    Node<T, Key>* pParent;
    int height;

    Node() : item(T{}), pLeft(nullptr), pRight(nullptr), pParent(nullptr), height(1) {}
    Node(const T& value) : item(value), pLeft(nullptr), pRight(nullptr), pParent(nullptr), height(1) {}

    T getItem() const { return item; }
    void setItem(const T& value) { item = value; }
};

// PAIR -------------------------------------------------------------------------
template<typename T, typename Key>
class Pair {
private:
    Key chave;
    T value;

public:
    Pair() : chave(Key{}), value(T{}) {}
    Pair(Key key, T val) : chave(key), value(val) {}

    Key getKey() const { return chave; }
    T getValue() const { return value; }

    friend ostream& operator<<(ostream& os, const Pair<T, Key>& p) {
        os << "(" << p.getKey() << ", " << p.getValue() << ")";
        return os;
    }
};

// TREE -------------------------------------------------------------------------
template<typename T, typename Key>
class Tree {
private:
    Node<T, Key>* root;

    bool insert(T& item, Node<T, Key>*& p);
    bool remove(T& item, Node<T, Key>*& p);
    void remove_aux(Node<T, Key>*& p, Node<T, Key>*& q);
    bool search(T& item, Node<T, Key>* p) const;
    void preorderTraversal(Node<T, Key>* p) const;
    void inorderTraversal(Node<T, Key>* p) const;
    void postorderTraversal(Node<T, Key>* p) const;

    int height(Node<T, Key>* p) const;
    int updateHeight(Node<T, Key>* p);
    int balanceFactor(Node<T, Key>* p) const;
    Node<T, Key>* balance(Node<T, Key>*& p);
    Node<T, Key>* rotateLeft(Node<T, Key>*& p);
    Node<T, Key>* rotateRight(Node<T, Key>*& p);

public:
    Tree() : root(nullptr) {}

    bool insert(T& item);
    bool remove(Key key);
    bool search(Key key, T& item) const;
    void preorderTraversal() const;
    void inorderTraversal() const;
    void postorderTraversal() const;
};

// MÉTODOS PRIVADOS -------------------------------------------------------------
template<typename T, typename Key>
bool Tree<T, Key>::insert(T& item, Node<T, Key>*& p) {
    if (p == nullptr) {
        p = new Node<T, Key>(item);
        return true;
    } else if (item.getKey() < p->getItem().getKey()) {
        if (!insert(item, p->pLeft)) return false;
        p->pLeft->pParent = p;
    } else if (item.getKey() > p->getItem().getKey()) {
        if (!insert(item, p->pRight)) return false;
        p->pRight->pParent = p;
    } else {
        return false;  // chave duplicada
    }

    p = balance(p);
    if (p->pParent == nullptr)
        root = p;
    return true;
}

template<typename T, typename Key>
bool Tree<T, Key>::remove(T& item, Node<T, Key>*& p) {
    if (p == nullptr) return false;

    if (item.getKey() < p->getItem().getKey()) {
        if (!remove(item, p->pLeft)) return false;
    } else if (item.getKey() > p->getItem().getKey()) {
        if (!remove(item, p->pRight)) return false;
    } else if (p->pRight == nullptr) {
        Node<T, Key>* aux = p;
        p = p->pLeft;
        delete aux;
    } else if (p->pLeft == nullptr) {
        Node<T, Key>* aux = p;
        p = p->pRight;
        delete aux;
    } else {
        remove_aux(p, p->pLeft);
    }

    if (p != nullptr)
        p = balance(p);
    if (p != nullptr && p->pParent == nullptr)
        root = p;

    return true;
}

template<typename T, typename Key>
void Tree<T, Key>::remove_aux(Node<T, Key>*& p, Node<T, Key>*& q) {
    if (q->pRight != nullptr) {
        remove_aux(p, q->pRight);
    } else {
        p->setItem(q->getItem());
        Node<T, Key>* aux = q;
        q = q->pLeft;
        delete aux;
    }
}

template<typename T, typename Key>
bool Tree<T, Key>::search(T& item, Node<T, Key>* p) const {
    if (p == nullptr) return false;

    if (item.getKey() < p->getItem().getKey()) {
        return search(item, p->pLeft);
    } else if (item.getKey() > p->getItem().getKey()) {
        return search(item, p->pRight);
    } else {
        item = p->getItem();
        return true;
    }
}

template<typename T, typename Key>
void Tree<T, Key>::preorderTraversal(Node<T, Key>* p) const {
    if (p != nullptr) {
        cout << p->getItem() << " ";
        preorderTraversal(p->pLeft);
        preorderTraversal(p->pRight);
    }
}

template<typename T, typename Key>
void Tree<T, Key>::inorderTraversal(Node<T, Key>* p) const {
    if (p != nullptr) {
        inorderTraversal(p->pLeft);
        cout << p->getItem() << " ";
        inorderTraversal(p->pRight);
    }
}

template<typename T, typename Key>
void Tree<T, Key>::postorderTraversal(Node<T, Key>* p) const {
    if (p != nullptr) {
        postorderTraversal(p->pLeft);
        postorderTraversal(p->pRight);
        cout << p->getItem() << " ";
    }
}

template<typename T, typename Key>
int Tree<T, Key>::height(Node<T, Key>* p) const {
    return (p == nullptr) ? 0 : p->height;
}

template<typename T, typename Key>
int Tree<T, Key>::balanceFactor(Node<T, Key>* p) const {
    return height(p->pRight) - height(p->pLeft);
}

template<typename T, typename Key>
int Tree<T, Key>::updateHeight(Node<T, Key>* p) {
    int hLeft = height(p->pLeft);
    int hRight = height(p->pRight);
    return p->height = max(hLeft, hRight) + 1;
}

template<typename T, typename Key>
Node<T, Key>* Tree<T, Key>::balance(Node<T, Key>*& p) {
    updateHeight(p);
    int bf = balanceFactor(p);

    if (bf > 1) {
        if (balanceFactor(p->pRight) < 0)
            p->pRight = rotateRight(p->pRight);
        p = rotateLeft(p);
    } else if (bf < -1) {
        if (balanceFactor(p->pLeft) > 0)
            p->pLeft = rotateLeft(p->pLeft);
        p = rotateRight(p);
    }

    return p;
}

template<typename T, typename Key>
Node<T, Key>* Tree<T, Key>::rotateLeft(Node<T, Key>*& p) {
    Node<T, Key>* q = p->pRight;
    p->pRight = q->pLeft;
    if (q->pLeft) q->pLeft->pParent = p;
    q->pLeft = p;

    q->pParent = p->pParent;
    p->pParent = q;

    updateHeight(p);
    updateHeight(q);

    return q;
}

template<typename T, typename Key>
Node<T, Key>* Tree<T, Key>::rotateRight(Node<T, Key>*& p) {
    Node<T, Key>* q = p->pLeft;
    p->pLeft = q->pRight;
    if (q->pRight) q->pRight->pParent = p;
    q->pRight = p;

    q->pParent = p->pParent;
    p->pParent = q;

    updateHeight(p);
    updateHeight(q);

    return q;
}

// MÉTODOS PÚBLICOS -------------------------------------------------------------
template<typename T, typename Key>
bool Tree<T, Key>::insert(T& item) {
    return insert(item, root);
}

template<typename T, typename Key>
bool Tree<T, Key>::remove(Key key) {
    T temp(key, T{}.getValue());
    return remove(temp, root);
}

template<typename T, typename Key>
bool Tree<T, Key>::search(Key key, T& item) const {
    T temp(key, T{}.getValue());
    if (search(temp, root)) {
        item = temp;
        return true;
    }
    return false;
}

template<typename T, typename Key>
void Tree<T, Key>::preorderTraversal() const {
    preorderTraversal(root);
    cout << endl;
}

template<typename T, typename Key>
void Tree<T, Key>::inorderTraversal() const {
    inorderTraversal(root);
    cout << endl;
}

template<typename T, typename Key>
void Tree<T, Key>::postorderTraversal() const {
    postorderTraversal(root);
    cout << endl;
}

// MAIN -------------------------------------------------------------------------
int main() {
    Tree<Pair<string, int>, int> arvore;

    Pair<string, int> pares[] = {
        {1, "um"},
        {2, "dois"},
        {3, "tres"},
        {4, "quatro"},
        {5, "cinco"}
    };

    for (auto& p : pares) {
        if (arvore.insert(p))
            cout << "Inserido: " << p << endl;
        else
            cout << "Erro ao inserir: " << p << endl;
    }

    cout << "Inorder: ";
    arvore.inorderTraversal();

    Pair<string, int> buscado;
    if (arvore.search(3, buscado))
        cout << "Encontrado: " << buscado << endl;
    else
        cout << "Nao encontrado." << endl;

    if (arvore.remove(3))
        cout << "Removido com sucesso.\n";
    else
        cout << "Erro ao remover.\n";

    cout << "Inorder apos remocao: ";
    arvore.inorderTraversal();

    return 0;
}
