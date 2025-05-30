#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <list>


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

template<typename Key, typename T>
class AVLTree {
private:
    Node<T>* root;

public:
    AVLTree();
    void create();
    void insert(Key key, T item);
    bool remove(Key key);
    bool search(Key key, T item);
    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();
    void insert(T item, Node<T>* p);
    void remove(T item, Node<T>* p);
    void remove_aux(T item, Node<T>* p);
    void search(T item, Node<T>* p);
    void preorderTraversal(Node<T>* p);
    void inorderTraversal(Node<T>* p);
    void postorderTraversal(Node<T>* p);

    //dps tirar isso aq, é so pra teste
    void generateDot(Node<T> *root, std::ostream& out);
    void drawTree(Node<T> *root);

};



template<typename Key, typename T>
AVLTree<Key, T>::AVLTree() {
    root = nullptr;
}

//de acordo com o slide do prof é pra ta assim (?)
template<typename Key, typename T>
void AVLTree<Key, T>::create() {
    root = nullptr;
}

template<typename Key, typename T>
void AVLTree<Key, T>::insert(Key key, T item) {
    //se o root ja existe adicionar os nodes
    Node<T>* parent = nullptr;
    Node<T>* current = this->root;

    while (current != nullptr) {
        parent = current;
        if (key == current->key) {
            cout << "Elemento ja existe";
            return;
        }
        else if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }


}

//deleta, se true quer dizer q removeu e falso quer dizer q nunca existiur
/*template<typename Key, typename T>
bool AVLTree<Key, T>::remove(Key key) {

}*/

template<typename Key, typename T>
bool AVLTree<Key, T>::search(Key key, T item) {
    if (root == NULL) return NULL;
    Node<T> *aux = root;
    while (aux->item != key) {
        if (key < aux->item) {
            aux = aux->left;
        }else {

        }
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::preorderTraversal() {

}

template<typename Key, typename T>
void AVLTree<Key, T>::inorderTraversal() {

}

template<typename Key, typename T>
void AVLTree<Key, T>::postorderTraversal() {

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
        cout <<"elementor ja existe";
        //dps que tiver tudo certo apenas usar return
    }
}

template<typename Key, typename T>
void AVLTree<Key, T>::remove(T item, Node<T> *p) {

}

template<typename Key, typename T>
void AVLTree<Key, T>::remove_aux(T item, Node<T> *p) {

}

//aq ta do jeito do slide do prof
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

}

template<typename Key, typename T>
void AVLTree<Key, T>::inorderTraversal(Node<T> *p) {

}

template<typename Key, typename T>
void AVLTree<Key, T>::postorderTraversal(Node<T> *p) {

}

//class HashTable
template<typename Key, typename T>
class HashTable {
private:
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
    long unsigned int hash(const Key& key) const;
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
    long unsigned int index = hash(key);

    table[index].insertBack(AVLTree<Key,T>());
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
    long unsigned int index = hash(key);
    const List<AVLTree<Key, T>>& bucket = table[index];
    ListNavigator<AVLTree<Key, T>> nav = bucket.getListNavigator();
    while (!nav.end()) {
        const AVLTree<Key, T>& p = nav.getCurrentItem();
        if (p.getFirst() == key && p.getLast() == item) {
            cout << item << " found at index " << index << endl;
            return true;
        }
        nav.next();
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
long unsigned int HashTable<Key, T>::hash(const Key& key) const{
    long unsigned int hashValue = 0;
    long unsigned int n = key.length();
    for (size_t i = 0; i < n; ++i) {
        hashValue += key[i] * static_cast<size_t>(pow(128, n - i - 1));
        hashValue %= this->getSize();
    }
    return hashValue;
}

//Tira os sinais de pontuação das strings
void cleanGiantString(string key,List<string> giantString) {
    ListNavigator<string> nav = giantString.getListNavigator();
    List<string> cleanedGiantString;
    string word;
    string cleaned;
    HashTable<string, string> ht(10);

    while (!nav.end()) {
        nav.getCurrentItem(word);
        cleaned.clear();

        for (char c: word) {
            if (!ispunct(c)) cleaned += c;
        }

        if (!cleaned.empty()) {
            //nao tenho ctz se e pra ser assim o insert
            //pq na minha cabeca key e item e pra ser a mesma coisa
            ht.insert(cleaned, cleaned);
            cout << cleaned << endl;
            cleanedGiantString.insertBack(cleaned);
        }

        nav.next();
    }


    //aqui so pra teste
    ListNavigator<string> nav_test = cleanedGiantString.getListNavigator();
    string line;
    while (!nav_test.end()) {
        nav_test.getCurrentItem(line);
        cout << line << endl;
        nav_test.next();
    }

        //o key ainda tá com a ### nele
        cout << key << endl;

}


// Função para gerar a saída em formato DOT
template <typename Key, typename T>
void AVLTree<Key,T>::generateDot(Node<T>* node, std::ostream& out) {
    if (node == nullptr) {
        return;
    }

    // Adiciona o nó atual com a altura
    out << "    " << node->getKey() << " [label=\"" << node->getKey() << "\\nAltura: " << height(node) << "\"];\n";

    // Conecta o nó atual aos filhos
    if (node->getLeft()) {
        out << "    " << node->getKey() << " -> " << node->getLeft()->getKey() << ";\n";
    }
    if (node->getRight()) {
        out << "    " << node->getKey() << " -> " << node->getRight()->getKey() << ";\n";
    }

    // Chama recursivamente para os filhos
    generateDot(node->getLeft(), out);
    generateDot(node->getRight(), out);
}

// Função principal para desenhar a árvore
template <typename Key, typename T>
void AVLTree<Key,T>::drawTree(Node<T>* root) {
    std::cout << "digraph G {\n";
    generateDot(root, std::cout);
    std::cout << "}\n";
}

//Lê cada linha e adiciona para uma List
int main() {
    string line;
    List<string> giantString;
    string key;

    //por enquanto so reconhece quando ### esta na ultima linha sozinho e no começo
    while (getline(cin, line)){
        if (line.find('#')) {
            giantString.insertBack(line);
        }else {
            key = line;
            break;
        }

    }
}

//Pode mexer a vontade :D
//Lista de tarefas
//1. Ler a string extra gigante (feito)
//1.5 Limpar a string de sinais(feito)
//2. Ler a chave (feito mas falta tirar o ###)
//3. Adicionar a AVL na HashTable (feito?)
//3.5 Fazer esse drawTree e generateDot funcionarem
//4. Resolver a colisao com AVL
//5. Fazer os a AVL estar corretamente equilibrada
//6. Mostrar a altura da chave na AVL
//7. Terminar de implementar os métodos da AVL de acordo com oq o prof pediu no uml

//Caso teste
/*
When Mr. Bilbo Baggins of Bag End announced that he
would shortly be celebrating his eleventy-first birthday
with a party of special magnificence, there was much talk and e
xcitement in Hobbiton.
### Key
*/