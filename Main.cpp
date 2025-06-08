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
    void insert( Key key, T item);
    int getHeight(Node<T>* node) const;
    int getHeight() const { return getHeight(root); }
    bool remove(Key key);
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
    void rotate(Node<T>* parent);
    void LLR(Node<T>* parent, Node<T>* node, Node<T>* child);
    void LRR(Node<T>* parent, Node<T>* node, Node<T>* child);
    void RRR(Node<T>* parent, Node<T>* node, Node<T>* child);
    void RLR(Node<T>* parent, Node<T>* node, Node<T>* child);
    void setBalance(Node<T>* node);

    //dps tirar isso aq, é so pra teste
    //void generateDot(Node<T> *root, std::ostream& out);
    //void drawTree(Node<T> *root);

};

template<typename Key, typename T>
AVLTree<Key, T>::AVLTree() {
    root = nullptr;
}

template <typename Key, typename T>
int AVLTree<Key,T>::getHeight(Node<T>* node) const{
    if (!node) {
        return -1;
    }
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

template<typename Key, typename T>
void AVLTree<Key,T>::setBalance(Node<T>* node) {
    node->balanceFactor = getHeight(node->right) - getHeight(node->left);
}

template <typename Key, typename T>
void AVLTree<Key,T>::rebalance(Node<T>* node){
    cout << "Rebalanceando a partir de: " << node->getItem()<< endl;
    while (node != nullptr) {
        setBalance(node);
        if (node->balanceFactor >= 2 || node->balanceFactor <= -2) {
            rotate(node);
        }
        node = node->parent;
    }
}

template <typename Key, typename T>
void AVLTree<Key,T>::rotate(Node<T>* node){
    Node<T>* child;

      if (node->balanceFactor < -1){
        child = node->left;
        setBalance(child);
        if (child->balanceFactor == 1) {
            LRR(node, child, child->right);
        }
        else {
            LLR(node, child, child->left);
        }
      }

      else {
        child = node->right;
        setBalance(child);
        if (child->balanceFactor == -1) {
            RLR(node, child, child->left);
        }
        else {
            RRR(node, child, child->right);
        }
      }
}

template <typename Key, typename T>
void AVLTree<Key,T>::LLR(Node<T>* parent, Node<T>* node, Node<T>* child){
    Node<T>* grandParent = parent->parent;
    node->parent = grandParent;
    Node<T>* nodeRight = node->right;

    if (nodeRight != nullptr) nodeRight->parent = parent;
    node->right = parent;
    parent->parent = node;
    parent->left = nodeRight;

    if (grandParent == nullptr)
        root = node;
    else if (grandParent->left == parent)
        grandParent->left = node;
    else
        grandParent->right = node;

    setBalance(parent);
    setBalance(node);
}

template <typename Key, typename T>
void AVLTree<Key,T>::LRR(Node<T>* parent, Node<T>* node, Node<T>* child){
  RRR(node, child, child->right);
  LLR(parent, child, node);
}

template <typename Key, typename T>
void AVLTree<Key,T>::RRR(Node<T>* parent, Node<T>* node, Node<T>* child){
    Node<T>* grandParent = parent->parent;
    node->parent = grandParent;
    Node<T>* nodeLeft = node->left;

    if (nodeLeft != nullptr) nodeLeft->parent = parent;
    node->left = parent;
    parent->parent = node;
    parent->right = nodeLeft;
    if (grandParent == nullptr)
        root = node;
    else if (grandParent->left == parent)
        grandParent->left = node;
    else
        grandParent->right = node;

    setBalance(parent);
    setBalance(node);

    cout << "Nova raiz da subarvore: " << node->getItem() << endl;
    cout << "parent do antigo pai agora e: " << parent->parent->getItem() << endl;
}

template <typename Key, typename T>
void AVLTree<Key,T>::RLR(Node<T>* parent, Node<T>* node, Node<T>* child){
    LLR(node, child, child->left);
    RRR(parent, child, node);
}

template<typename Key, typename T>
Node<T>* AVLTree<Key, T>::getRoot() {
    return root;
}

//de acordo com o slide do prof é pra ta assim (?)
template<typename Key, typename T>
void AVLTree<Key, T>::create() {
    root = nullptr;
}

template<typename Key, typename T>
void AVLTree<Key, T>::insert(Key key,  T item) {
    //cout << "Inserindo " << key << std::endl;

    //se o root ja existe adicionar os nodes
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
            cout << "Elemento ja existe" << endl;
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

            int altura = getHeight(aux);
            cout << "Altura da subarvore a partir do no '" << key << "': " << altura << endl;
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
    cout << "Inserindo " << item << std::endl;
    if (p == nullptr) {
        p = new Node<T>(item);
        p->left = p->right = nullptr;
        p->item = item;
    } else if (item->key < p->item->key) {
        insert(item, p->left);
    } else if (item->key > p->item->key) {
        insert(item, p->right);
    } else {
        cout <<"elementor ja existe" << endl;
        //dps que tiver tudo certo apenas usar return
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

//acho q esse aq ta errado, era pra ser dois node de parametro
//dps vejo direito no slide
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
    if (current == nullptr) return 0;
    return current->height;
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
//DPS MUDAR PRA PUBLIC, so deixei assim pra testar um ngc
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

    ListNavigator<AVLTree<Key, T>> nav = table[index].getListNavigator();

    while (!nav.end()) {
        AVLTree<Key, T> tree =  nav.getCurrentItem();
        tree.insert(key, item);
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
    long unsigned int index = hash(key);

    ListNavigator<AVLTree<Key, T>> nav = table[index].getListNavigator();

    while (!nav.end()) {
        AVLTree<Key, T> tree =  nav.getCurrentItem();
        if (tree.search(key, item)) {
            cout << "Item encontrado: " << key << endl;
            return true;
        }
        nav.next();
    }

    cout << "Item nao encontrado: " << item << endl;
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

// Função para gerar a saída em formato DOT
template <typename T>
void generateDot(Node<T>* node, std::ostream& out) {
    if (node == nullptr) return;

    out << "    \"" << node->getItem() << "\" [label=\"" << node->getItem() << "\"];\n";

    if (node->left) {
        out << "    \"" << node->getItem() << "\" -> \"" << node->left->getItem() << "\";\n";
        generateDot(node->left, out);
    }

    if (node->right) {
        out << "    \"" << node->getItem() << "\" -> \"" << node->right->getItem() << "\";\n";
        generateDot(node->right, out);
    }
}

// Função principal para desenhar a árvore
template <typename T>
void drawTree(Node<T>* root) {
    cout << "digraph G {\n";
    generateDot(root, std::cout);
    cout << "}\n";
}

//Tira os sinais de pontuação das strings
void cleanGiantString(string key,List<string> giantString) {
    ListNavigator<string> nav = giantString.getListNavigator();
    List<string> cleanedGiantString;
    HashTable<string, string> ht(151);
    //cout << "Funcao ta funcionando" << endl;

    while (!nav.end()) {
        string phrase;
        nav.getCurrentItem(phrase);

        string currentWord;
        string cleaned;


        //cout << "While ta rodando" << endl;
        for (char c : phrase) {
            if (c == ' ') {
                if (!currentWord.empty()) {
                    cleaned.clear();
                    for (char ch : currentWord) {
                        if (!ispunct(ch)) cleaned += ch;
                    }

                    if (!cleaned.empty()) {
                        cout << "Ta inserindo na hashtable " << cleaned << endl;
                        ht.insert(cleaned, cleaned);
                        //dps tirar esse insertback pq era so pra teste
                        //cleanedGiantString.insertBack(cleaned);
                    }

                    currentWord.clear();
                }
            } else {
                currentWord += c;
            }
        }

        //cout << "Nao é a phrase q ta dando erro" << endl;

        // Ultima palavra da fraser
        if (!currentWord.empty()) {
            cleaned.clear();
            for (char ch : currentWord) {
                if (!ispunct(ch)) cleaned += ch;
            }

            if (!cleaned.empty()) {
                cout << "Ta inserindo na hashtable " << cleaned << endl;
                ht.insert(cleaned, cleaned);
                //cleanedGiantString.insertBack(cleaned);
            }
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

    //Tira espaco branco do Key
    string cleanedKey;
    for (char c : key) {
        if (c != '#' and c != ' ') {
            cleanedKey += c;
        }
    }

    cout << cleanedKey << endl;


    //isso aq e so pra ver a arvore e usar o drawTree
    for (size_t i = 0; i < ht.getSize(); ++i) {
        List<AVLTree<string, string>>& bucket = ht.table[i];

        ListNavigator<AVLTree<string, string>> nav = bucket.getListNavigator();

        while (!nav.end()) {
            AVLTree<string, string> tree = nav.getCurrentItem();

            cout << "Subárvore no bucket " << i << ":\n";
            drawTree<string>(tree.getRoot());

            nav.next();
        }
    }


    ht.search(cleanedKey,cleanedKey);


}




//Lê cada linha e adiciona para uma List
int main() {
    string line;
    List<string> giantString;
    string key;


    //por enquanto so reconhece quando ### esta na ultima linha sozinho e no começo
    while (getline(cin, line)) {
        if (line.rfind("###", 0) == 0) {
            key = line.substr(3); // remove os "###"
            break;
        } else {
            giantString.insertBack(line);
        }
    }


    cleanGiantString(key, giantString);
    return 0;
}

//Pode mexer a vontade :D
//Lista de tarefas
//1. Ler a string extra gigante (feito)
//1.5 Limpar a string de sinais(feito)
//2. Ler a chave (feito)
//3. Adicionar a AVL na HashTable (feito)
//3.5 Fazer esse drawTree e generateDot funcionarem (feito)
//4. Resolver a colisao com AVL (feito)
//5. Fazer os a AVL estar corretamente equilibrada (feito)
//6. Adicionar a busca por chave (feito)
//7. Mostrar a altura da chave na AVL (feito)
//8. Terminar de implementar os métodos da AVL de acordo com oq o prof pediu no uml (feito)
//9. Ler todo o arquivo do cap 1 D:

//Caso teste
/*
When Mr. Bilbo Baggins of Bag End announced that he
### Bilbo
*/

//O eleventyfirst ta sendo considerado uma palavra so, dps ver isso
