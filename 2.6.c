#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла дерева
typedef struct Node {
    unsigned int key;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node* BST;

// Функция вставки элемента в дерево
BST insert(BST root, unsigned int key) {
    if (!root) {
        Node *p = (Node*)malloc(sizeof(Node));
        p->key = key;
        p->left = p->right = NULL;
        return p;
    }
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    // если ключ уже есть, ничего не делаем
    return root;
}

// Функция поиска элемента
int find(BST root, unsigned int key) {
    if (!root) return 0;
    if (key == root->key) return 1;
    else if (key < root->key) return find(root->left, key);
    else return find(root->right, key);
}

// Функция поиска минимального элемента (для удаления)
BST findMin(BST root) {
    while (root->left) root = root->left;
    return root;
}

// Функция удаления элемента из дерева
BST removeNode(BST root, unsigned int key) {
    if (!root) return NULL;

    if (key < root->key) root->left = removeNode(root->left, key);
    else if (key > root->key)
        root->right = removeNode(root->right, key);
    else { // нашли узел
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = removeNode(root->right, temp->key);
        }
    }
    return root;
}

// Функция освобождения памяти дерева
void destruct(BST root) {
    if (!root) return;
    destruct(root->left);
    destruct(root->right);
    free(root);
}

int main() {
    BST root = NULL;
    char cmd;
    unsigned int x;

    // читаем команды до конца файла
    while (scanf(" %c%u", &cmd, &x) == 2) {
        if (cmd == '+') root = insert(root, x);
        else if (cmd == '-') root = removeNode(root, x);
        else if (cmd == '?') printf("%u %s\n", x, find(root, x) ? "yes" : "no");
    }

    destruct(root); // очищаем память
    return 0;
}
