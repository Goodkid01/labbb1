#include <iostream>
#include <climits>
#include <cfloat>
#include <iomanip>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

void AddBack(Node* sent, int data) {
    Node* p = new Node;
    p->data = data;
    p->left = sent->left;
    p->right = sent;
    sent->left->right = p;
    sent->left = p;
}

void Print(Node* sent) {
    Node* p = sent->right;
    while (p != sent) {
        std::cout << p->data << std::endl;
        p = p->right;
    }
}

void Clear(Node* sent) {
    Node* p = sent->right;
    while (p != sent) {
        Node* tmp = p;
        p = p->right;
        delete tmp;
    }
    sent->left = sent;
    sent->right = sent;
}

bool hasDuplicates(Node* sent) {
    Node* p = sent->right;
    std::set<int> seen;
    while (p != sent) {
        if (seen.find(p->data) != seen.end()) {
            return true;
        }
        seen.insert(p->data);
        p = p->right;
    }
    return false;
}

bool containsDigit(int number, int digit) {
    if (number == 0) return digit == 0;
    number = abs(number);
    while (number > 0) {
        if (number % 10 == digit) {
            return true;
        }
        number /= 10;
    }
    return false;
}

// Исправленная функция: сортирует список по последней цифре
void sortByLastDigit(Node* sent) {
    vector<int> elements;
    Node* p = sent->right;
    while (p != sent) {
        elements.push_back(p->data);
        p = p->right;
    }

    // Сортируем по убыванию последней цифры
    sort(elements.begin(), elements.end(), [](int a, int b) {
        return (a % 10) > (b % 10);
    });

    // Очищаем список и заполняем отсортированными значениями
    Clear(sent);
    for (int num : elements) {
        AddBack(sent, num);
    }
}

// Исправленная функция: удаляет числа с цифрой 3
void removeNumbersWith3(Node* sent) {
    Node* p = sent->right;
    while (p != sent) {
        Node* nextNode = p->right;
        if (containsDigit(p->data, 3)) {
            p->left->right = p->right;
            p->right->left = p->left;
            delete p;
        }
        p = nextNode;
    }
}

// Исправленная функция: дублирует числа с цифрой 7 (без 3)
void duplicateNumbersWith7(Node* sent) {
    Node* current = sent->right;
    while (current != sent) {
        Node* nextNode = current->right;
        if (containsDigit(current->data, 7) && !containsDigit(current->data, 3)) {
            Node* newNode = new Node;
            newNode->data = current->data;  // Важно: копируем данные!
            newNode->left = current;
            newNode->right = current->right;
            current->right->left = newNode;
            current->right = newNode;
            nextNode = newNode->right;  // Пропускаем новый узел
        }
        current = nextNode;
    }
}

void processSequence(Node* sent) {
    if (hasDuplicates(sent)) {
        sortByLastDigit(sent);
    } else {
        removeNumbersWith3(sent);
        duplicateNumbersWith7(sent);
    }
}

int main() {
    Node* sent = new Node;
    sent->left = sent;
    sent->right = sent;

    AddBack(sent, 11);
    AddBack(sent, 13);
    AddBack(sent, 33);
    AddBack(sent, 12);
    AddBack(sent, 17);

    processSequence(sent);

    cout << "Результат:" << endl;
    Print(sent);

    Clear(sent);
    delete sent;
    return 0;
}

