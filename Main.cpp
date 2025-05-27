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
    Node<T> *next;
    Node<T> *prev;
    T getItem();
    Node();
    Node(T item);
};

template<typename T>
Node<T>::Node() {
    next = nullptr;
    prev = nullptr;
}

template<typename T>
Node<T>::Node(T item) {
    this->item = item;
    next = nullptr;
    prev = nullptr;
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

template<typename T> bool ListNavigator<T>::getCurrentItem(T &item)
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


//class HashTable
template<typename Key, typename T>
class HashTable {
private:
    List<AVLTree<Pair<Key, T>> *table> *table;
public:
    HashTable(int capacity);
    long unsigned int size;

    ~HashTable();

    long unsigned int getSize() const;
    void insert(Key key, T item);
    void insert(Pair<Key, T> pair);
    bool remove(Key key);
    bool search(Key key, T item);
    T findItemFromKey(Key key) const;
    bool empty();
    long unsigned int hash(const Key& key) const;
};

template<typename Key, typename T>
HashTable<Key, T>::HashTable(int capacity){
    table = new List<Pair<Key, T>>[capacity];
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
    long unsigned int index = hash(key);

    table[index].insertBack(Pair<Key, T>(key, item));
}

template<typename Key, typename T>
void HashTable<Key, T>::insert(Pair<Key, T> pair){
    long unsigned int index = hash(pair.getFirst());
    table[index].push(pair);
}

template<typename Key, typename T>
bool HashTable<Key, T>::remove(Key key) {
    long unsigned int index = hash(key);
    List<Pair<Key, T>>& target = table[index];
    ListNavigator<Pair<Key, T>> nav = target.getListNavigator();
    Pair<Key, T> currentItem;
    while (!nav.end()) {
        currentItem = nav.getCurrentItem();
        if (currentItem.getFirst() == key) {
            nav.removeCurrentItem();
            return true;
        }
        nav.next();
    }
    return false;
}

template<typename Key, typename T>
bool HashTable<Key, T>::search(Key key, T item){
    long unsigned int index = hash(key);
    List<Pair<Key, T>>& target = table[index];
    ListNavigator<Pair<Key, T>> nav = target.getListNavigator();
    Pair<Key, T> currentItem;
    while (!nav.end()) {
        currentItem = nav.getCurrentItem();
        if (currentItem.getFirst() == key && currentItem.getLast() == item) {
            cout << item << " found at index " << index << endl;
            return true;
        }
    }
    cout << key << " not found" << endl;
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
T HashTable<Key, T>::findItemFromKey(Key key) const {
    long unsigned int index = hash(key);
    Node<Pair<Key, T>>* currentNode  = table[index].getHead();
    while (true) {
        if (currentNode == nullptr || currentNode->next == nullptr) {
            break;
        }
        currentNode = currentNode->next;
        if (currentNode->getItem().getFirst() == key) {
            return currentNode->getItem().getLast();
        }
    }
    return T();
}


template<typename Key, typename T>
long unsigned int HashTable<Key, T>::hash(const Key& key) const{
    long unsigned int hashValue = 0;
    long unsigned int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<size_t>(pow(128, n - i - 1));
        hashValue %= this->getSize();
    }
    return hashValue;
}



int main() {
    string line;
    List<string> alienList;

    while (getline(cin, line)) {
        if (line == "~") break;
        alienList.insertBack(line);
    }

    return 0;
}
