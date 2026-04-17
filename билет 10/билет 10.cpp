// билет 10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct List {
    int value = NULL;
    List* next = nullptr;
};

void addToList(List& list, int value) {
    List* current = &list;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = new List;
    current->next->value = value;
}

void displayList(List& list) {
    List* current = &list;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    List list;
    list.value = 1;

    addToList(list, 2);
    addToList(list, 3);
    addToList(list, 4);

    displayList(list);

    return 0;
}