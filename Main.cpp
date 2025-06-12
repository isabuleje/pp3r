#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

using namespace std;

// Class Node
template<typename T> class Node {
private:
    T item;

public:
    Node<T>* left;
    Node<T>* right;
    Node<T> *next;
    Node<T> *prev;
    Node<T> *parent;
    T getItem();
    Node();
    Node(T item);
    int height;
    int balanceFactor;

};

template<typename T>
Node<T>::Node() {
    next = nullptr;
    prev = nullptr;
    left = nullptr; 
    right = nullptr; 
    parent = nullptr; 
    height = 0; 
    balanceFactor = 0; 
}

template<typename T>
Node<T>::Node(T item) {
    this->item = item;
    next = nullptr;
    prev = nullptr;
     left = nullptr; 
    right = nullptr; 
    parent = nullptr; 
    height = 0; 
    balanceFactor = 0; 
}

template<typename T> T Node<T>::getItem() { return item; }

template<typename T> class ListNavigator;

// Class List
template<typename T> class List {
private:
    Node<T> *pHead;
    Node<T> *pBack;
    int numItems;
    void succ(Node<T> *&p);
    void pred(Node<T> *&p);

public:
    void insertFront(T item);
    void insertBack(T item);
    void removeFront();
    void removeBack();
    T getItemFront();
    T getItemBack();
    ListNavigator<T> getListNavigator() const;
    int size();
    bool empty();
    List();
    Node<T>* getHead();
};

template<typename T> List<T>::List()
{
    pHead = new Node<T>();
    pBack = pHead;
    pHead->next = nullptr;
    numItems = 0;
}

template<typename T> void List<T>::succ(Node<T> *&p) { p = p->next; }


template<typename T> void List<T>::pred(Node<T> *&p)
{
    Node<T> *q = pHead;
    while (q->next != p) {
        succ(q);
    }
    p = q;
}

template<typename T> void List<T>::insertFront(T item)
{
    Node<T> *pNew = new Node<T>(item);
    pNew->next = pHead->next;
    pHead->next = pNew;
    pNew->prev = pHead;

    if (pBack == pHead) {
      pBack = pNew;
    }
    numItems++;
}

template<typename T> void List<T>::insertBack(T item)
{
    Node<T> *pNew = new Node<T>(item);
    pBack->next = pNew;
    pNew->prev = pBack;
    pBack = pNew;
    numItems++;
}

template<typename T> void List<T>::removeFront()
{
    if (empty()) {
      cout << "List is empty" << endl;
      return;
    }

    Node<T> *temp = pHead->next;
    pHead->next = temp->next;

    if (pBack == temp) {
      pBack = pHead;
    }

    delete temp;
    numItems--;
}


template<typename T> void List<T>::removeBack()
{
    if (empty()) {
        cout << "List is empty" << endl;
    }

    Node<T> *temp = pBack;
    pred(pBack);
    pBack->next = nullptr;

    delete temp;

    if (pHead == pBack) {
        pHead = pBack;
    }
    numItems--;
}

template<typename T> T List<T>::getItemFront()
{
    if (empty()) {
      return T();
    }

    return pHead->next->getItem();
}

template<typename T> T List<T>::getItemBack()
{
    if (empty()) {
      return T();
    }

    return pBack->getItem();
}

template<typename T> ListNavigator<T> List<T>::getListNavigator() const
{
    return ListNavigator<T>(pHead->next);
}

template<typename T> int List<T>::size(){
    return numItems;
}


template<typename T> bool List<T>::empty() { return pBack == pHead; }

template<typename T> Node<T>* List<T>::getHead() { return pHead; }

// ListNavigator
template<typename T> class ListNavigator {
private:
    Node<T> *current;
    Node<T> *start;
    int currentPosition;

public:
    bool end();
    void next();
    void reset();
    bool getCurrentItem(T &item);
    int  getCurrentPosition() const;
    ListNavigator(Node<T> *current);
    T getCurrentItem();
    Node<T> *getCurrentNode() { return current; }
};

template<typename T> ListNavigator<T>::ListNavigator(Node<T> *current)
{
    this->current = current;
    this->start = current;
}

template<typename T> bool ListNavigator<T>::end() { return current == nullptr; }

template<typename T> void ListNavigator<T>::next() {
        current = current->next;
}

template<typename T> void ListNavigator<T>::reset() { current = start; }

template<typename T> bool ListNavigator<T>::getCurrentItem (T &item)
{
    if (current == nullptr) {
      return false;
    }
    item = current->getItem();
    return true;
}

template<typename T> T ListNavigator<T>::getCurrentItem() { return current->getItem();}

template<typename T> int ListNavigator<T>::getCurrentPosition() const { return currentPosition; }


//Class Queue
template<typename T> class Queue {
private:
    List<T> list;

public:
    void enqueue(T item);
    void dequeue();
    T front();
    int size();
    bool empty();
    Queue(List<T>);
};

template<typename T> Queue<T>::Queue(List<T> list) { this->list = list; }

template<typename T> void Queue<T>::enqueue(T item) { list.insertBack(item); }

template<typename T> void Queue<T>::dequeue()
{
    if (empty()) {
      cout << "Queue is empty" << endl;
    }
    list.removeFront();
}

template<typename T> T Queue<T>::front()
{
    if (empty()) {
      return T();
    }
    return list.getItemFront();
}

template<typename T> int Queue<T>::size() { return list.size(); }

template<typename T> bool Queue<T>::empty() { return list.empty(); }

// Class Stack
template<typename T> class Stack {
private:
    List<T> list;

public:
    void push(T item);
    void pop();
    T top();
    int size();
    bool empty();
    bool contains(T item);
    Stack(List<T>);
};

template<typename T> Stack<T>::Stack(List<T> list) { this->list = list; }

template<typename T> void Stack<T>::push(T item) { list.insertFront(item); }

template<typename T> void Stack<T>::pop()
{
    if (empty()) {
      cout << "Stack is empty" << endl;
    }
    list.removeFront();
}

template<typename T> T Stack<T>::top()
{
    if (empty()) {
      return T();
    }
    return list.getItemFront();
}

template<typename T> int Stack<T>::size() { return list.size(); }

template<typename T> bool Stack<T>::empty() { return list.empty(); }

template <typename T>
bool Stack<T>::contains(T item) {
    ListNavigator<T> nav = list.getListNavigator();
    T currentItem;
    while (!nav.end()) {
        if (nav.getCurrentItem(currentItem) && currentItem == item) {
            return true;
        }
        nav.next();
    }
    return false;
}

template<typename Key, typename T>
class AVLTree {
private:
    Node<T>* root;

public:
    AVLTree();
    void create();
    void insert(Key key, T item);
    int getHeight(Node<T>* node) const;
    int getHeight() const { return getHeight(root); }
    bool search(Key key, T item);
    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();
    void insert(T item, Node<T>* p);
    void remove(T item, Node<T>* p);
    void remove_aux(Node<T>* q, Node<T>* p);
    void search(T item, Node<T>* p);
    void preorderTraversal(Node<T>* p);
    void inorderTraversal(Node<T>* p);
    void postorderTraversal(Node<T>* p);
    Node<T>* getRoot();
    void rebalance(Node<T>* node);
    void rotateRight(Node<T>* node);
    void rotateLeft(Node<T>* node);
    void setBalance(Node<T>* node);
    void updateHeight(Node<T>* node);

};

template<typename Key, typename T>
AVLTree<Key, T>::AVLTree() {
    root = nullptr;
}

template <typename Key, typename T>
int AVLTree<Key,T>::getHeight(Node<T>* node) const{
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template <typename Key, typename T>
void AVLTree<Key, T>::updateHeight(Node<T>* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        node->balanceFactor = getHeight(node->right) - getHeight(node->left);
    }
}

template<typename Key, typename T>
void AVLTree<Key,T>::setBalance(Node<T>* node) {
    if (node) {
        node->balanceFactor = getHeight(node->right) - getHeight(node->left);
    }
}

template <typename Key, typename T>
void AVLTree<Key,T>::rebalance(Node<T>* node){
    while (node != nullptr) {
        updateHeight(node);

        if (node->balanceFactor < -1) {
            if (node->left->balanceFactor <= 0) {
                //esquerda esquerda
                rotateRight(node);
            } else {
                rotateLeft(node->left);
                //esquerda direita
                rotateRight(node);
            }
        } else if (node->balanceFactor > 1) {
            if (node->right->balanceFactor >= 0) {
                //direita direita
                rotateLeft(node);
            } else {
                //direita esquerda
                rotateRight(node->right);
                rotateLeft(node);
            }
        }
        node = node->parent;
    }
}


template <typename Key, typename T>
void AVLTree<Key,T>::rotateLeft(Node<T>* node) {
    Node<T>* newRoot = node->right;
    node->right = newRoot->left;

    if (newRoot->left) {
        newRoot->left->parent = node;
    }

    newRoot->parent = node->parent;

    if (!node->parent) {
        root = newRoot;
    }
    else if (node == node->parent->left) {
        node->parent->left = newRoot;
    }
    else {
        node->parent->right = newRoot;
    }
    newRoot->left = node;
    node->parent = newRoot;

    updateHeight(node);
    updateHeight(newRoot);
}

template <typename Key, typename T>
void AVLTree<Key,T>::rotateRight(Node<T>* node) {
    Node<T>* newRoot = node->left;
    node->left = newRoot->right;

    if (newRoot->right) {
        newRoot->right->parent = node;
    }

    newRoot->parent = node->parent;

    if (!node->parent) {
        root = newRoot;
    }
    else if (node == node->parent->right) {
        node->parent->right = newRoot;
    }
    else {
        node->parent->left = newRoot;
    }
    newRoot->right = node;
    node->parent = newRoot;

    updateHeight(node);
    updateHeight(newRoot);
}
template<typename Key, typename T>
Node<T>* AVLTree<Key, T>::getRoot() {
    return root;
}

template<typename Key, typename T>
void AVLTree<Key, T>::create() {
    root = nullptr;
}

template<typename Key, typename T>
void AVLTree<Key, T>::insert(Key key,  T item) {
    Node<T>* newNode = new Node<T>(item);
    newNode->left = newNode->right = nullptr;
    newNode->parent = nullptr;
    if (!root) {
        root = newNode;
        return;
    }

    Node<T>* parent = nullptr;
    Node<T>* current = this->root;

    while (current != nullptr) {
        parent = current;
        if (key == current->getItem()) {
            return;
        }
        else if (key < current->getItem()) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (key < parent->getItem()) {
        parent->left = newNode;

    } else {
        parent->right = newNode;
    }


    rebalance(newNode);
}


template<typename Key, typename T>
bool AVLTree<Key, T>::search(Key key, T item) {
    Node<T>* aux = root;
    while (aux != nullptr) {
        if (key == aux->getItem()) {
            int height = getHeight();
            cout << key << " - " << height << endl;
            return true;
        } else if (key < aux->getItem()) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }
    return false;
}

template<typename Key, typename T>
void AVLTree<Key, T>::preorderTraversal() {
    preorderTraversal(root);
}

template<typename Key, typename T>
void AVLTree<Key, T>::inorderTraversal() {
    inorderTraversal(root);
}

template<typename Key, typename T>
void AVLTree<Key, T>::postorderTraversal() {
    postorderTraversal(root);
}

template<typename Key, typename T>
void AVLTree<Key, T>::insert(T item, Node<T> *p) {
    if (p == nullptr) {
        p = new Node<T>(item);
        p->left = p->right = nullptr;
        p->item = item;
    } else if (item->key < p->item->key) {
        insert(item, p->left);
    } else if (item->key > p->item->key) {
        insert(item, p->right);
    } else {
        return;
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::remove(T item, Node<T> *p) {
    if (p == nullptr) {
        cout << "O item nao esta na arvore";
    }
    else if (item.key < p->item.key) {
        remove(p->left, item);
    }
    else if (item.key > p->item.key) {
        remove(p->right, item);
    }
    else if (p->right == nullptr) {
        Node<T>* aux = p;
        p = p->left;
        delete aux;
    }
    else if (p->left == nullptr) {
        Node<T>* aux = p;
        p = p->right;
        delete aux;
    }else {
        remove(p, p->left);
    }

}


template<typename Key, typename T>
void AVLTree<Key, T>::remove_aux(Node<T>* q, Node<T> *p) {
    if (p->right != nullptr) {
        remove_aux(q, p->right);
    }
    else {
        q->getItem() = p->getItem();
        q = p;
        p = p->left;
        delete q;
    }
}

template<typename Key, typename T>
int height(Node<T>* current) {
    if (current == nullptr) {
        return 0;
    }
    return current->height;
}


template<typename Key, typename T>
void AVLTree<Key, T>::search(T item, Node<T> *p) {
    if (p == nullptr) {
        cout << "Elemento nao encontrando";
    }else if (item->key < p->item->key) {
        search(item, p->left);
    }else if (item->key > p->item->key) {
        search(item, p->right);
    } else {
        item = p->item;
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::preorderTraversal(Node<T> *p) {
    if (p != nullptr) {
        processItem(p->getItem());
        preorderTraversal(p->left);
        preorderTraversal(p->right);
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::inorderTraversal(Node<T> *p) {
    if (p != nullptr) {
        inorderTraversal(p->left);
        processItem(p->getItem());
        inorderTraversal(p->right);
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::postorderTraversal(Node<T> *p) {
    if (p != nullptr) {
        postorderTraversal(p->left);
        postorderTraversal(p->right);
        processItem(p->getItem());
    }
}

//class HashTable
template<typename Key, typename T>
class HashTable {
public:
    List<AVLTree<Key,T>> *table;

public:
    HashTable(int capacity);
    long unsigned int size;

    ~HashTable();
    long unsigned int getSize() const;
    void insert(Key key, T item);
    bool remove(Key key);
    bool search(Key key, T item);
    bool empty();
    size_t hash(const string& key, size_t m);

};


template<typename Key, typename T>
HashTable<Key, T>::HashTable(int capacity){
    table = new List<AVLTree<Key,T>>[capacity];
    size = capacity;
}

template<typename Key, typename T>
HashTable<Key, T>::~HashTable(){
    delete[] table;
}

template<typename Key, typename T>
long unsigned int HashTable<Key, T>::getSize() const{
    return size;
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Key key, T item){
    long unsigned int index = hash(key, this->size);
    List<AVLTree<Key, T>>& bucket = table[index];
    ListNavigator<AVLTree<Key, T>> nav = bucket.getListNavigator();

    int pos = 0;

    while (!nav.end()) {
        AVLTree<Key, T> tree =  nav.getCurrentItem();
        tree.insert(key, item);
        List<AVLTree<Key, T>> tempList;
        ListNavigator<AVLTree<Key, T>> tempNav = bucket.getListNavigator();
        int i = 0;
        while (!tempNav.end()) {
            AVLTree<Key, T> t = tempNav.getCurrentItem();
            if (i == pos) {
                tempList.insertBack(tree); // coloca a arvore modificada
            } else {
                tempList.insertBack(t); // copia as outras
            }
            tempNav.next();
            i++;
        }

        bucket = tempList;
        return;
    }

    AVLTree<Key, T> newTree;
    newTree.insert(key, item);
    table[index].insertBack(newTree);
}

template<typename Key, typename T>
bool HashTable<Key, T>::remove(Key key) {
    long unsigned int index = hash(key);
    List<AVLTree<Key, T>>& target = table[index];
    ListNavigator<AVLTree<Key, T>> nav = target.getListNavigator();
    while (!nav.end()) {
        if (nav.getCurrentItem().getFirst() == key) {
            nav.removeCurrentItem();
            return true;
        }
        nav.next();
    }
    return false;
}

template<typename Key, typename T>
bool HashTable<Key, T>::search(Key key, T item){
    long unsigned int index = hash(key, this->size);

    ListNavigator<AVLTree<Key, T>> nav = table[index].getListNavigator();

    while (!nav.end()) {
        AVLTree<Key, T> tree =  nav.getCurrentItem();
        if (tree.search(key, item)) {
            return true;
        }
        nav.next();
    }

    cout << item <<" - "<< "Nao encontrado" << endl;
    return false;

}

template<typename Key, typename T>
bool HashTable<Key, T>::empty(){
    for (int i=0; i < table->capacity; i++){
        if(!table){
            return false;
        }else{
            return true;
        }
    }
}


template<typename Key, typename T>

size_t HashTable<Key,T>::hash(const string& key, size_t m) {
    size_t hashValue = 0;
    size_t n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<size_t>(std::pow(128, n - i - 1));
        hashValue %= m;
    }
    return hashValue;
}


//Limpa as acentuacoes das palavras
HashTable<string,string> cleanWords(List<string> cleanedGiantString) {
    HashTable<string, string> ht(151);
    ListNavigator<string> nav = cleanedGiantString.getListNavigator();

    while (!nav.end()) {
        string word = nav.getCurrentItem();
        string cleaned = "";

        for (char c : word) {
            if (!ispunct(c)) {
                cleaned += c;
            }
        }

        if (!cleaned.empty()) {
            ht.insert(cleaned, cleaned);
        }

        nav.next();
    }

    return ht;
}

//Separa todas as palavras por " "
List<string> separateWords(List<string> giantString) {
    ListNavigator<string> nav = giantString.getListNavigator();
    List<string> cleanedGiantString;

    while (!nav.end()) {
        string currentLine = nav.getCurrentItem();
        string currentWord;

        for (char c : currentLine) {
            if (c == ' ') {
                if (!currentWord.empty()) {
                    cleanedGiantString.insertBack(currentWord);
                    currentWord.clear();
                }
            }else {
                currentWord += c;
            }
        }
        if (!currentWord.empty()) {
            cleanedGiantString.insertBack(currentWord);
        }

        nav.next();
    }

    return  cleanedGiantString;
}


//Limpa, insere e procura
void searcher(string key,List<string> giantString) {
    List<string> cleanedGiantString = separateWords(giantString);
    HashTable<string,string> ht = cleanWords(cleanedGiantString);

    string cleanedKey;
    for (char c : key) {
        if (c != '#' and c != ' ') {
            cleanedKey += c;
        }
    }
    ht.search(cleanedKey, cleanedKey);
}


int main() {
    string line;
    List<string> giantString;
    string key;

    while (getline(cin, line)) {
        if (line.rfind("###", 0) == 0) {
            key = line.substr(3);
            break;
        } else {
            giantString.insertBack(line);
        }
    }

    searcher(key, giantString);
    return 0;
}
