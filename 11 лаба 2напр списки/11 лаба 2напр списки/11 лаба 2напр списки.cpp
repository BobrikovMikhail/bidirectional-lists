// 11 лаба 2напр списки.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// 11 лаба 2 напр списки.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// Структура узла списка
struct Node {
    int data;     // Данные узла - строка символов
    Node* next; // Указатель на следующий элемент
    Node* prev; // указатель на предыдущий элемент
};

// Функция для создания узла списка
Node* createNode(int data) {    
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

// Функция для создания списка
Node* createList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int n;
    cout << "Введите число узлов: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        //Вариант 1: ручное заполнение списка
        //int data;
        //cout << "Введите значение узла " << i << ": ";
        //cin >> data;
        //Node* newNode = createNode(data); // значение для элемента вводится с клав-ры

        //Вариант 2: автоматическое заполнение списка
        Node* newNode = createNode(i); // значение для элемента берется из i

        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }
    return head;
}

// Функция для печати списка
void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Функция для удаления заданного количества элементов, начиная с заданного номера
void deleteNodes(Node*& head, int index, int number) {
    Node* current = head;
    for (int i = 1; i < index; i++) {
        if (current->next != nullptr) {

            current = current->next;
        }
        else {
            cout << "Элемента с таким номером нет в списке" << endl;
            return;
        }
    }
    int count = 0;
    bool flag = true;
    while (current->next != nullptr && flag == true) {
        if (current->prev != nullptr) { //предыдущий элемент существует
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        else { //предыдущий элемент не существует, т.е. мы удаляем первый элемент в списке
            head = current->next;
            head->prev = nullptr;
        }
        Node* tmp = current;
        current = current->next;
        delete tmp;
        count++;
        if (count == number) { //удалили заданное количество элементов 
            flag = false;
        }
    }
    if (current->next == nullptr && flag == true) { //мы находимся на последнем элементе списка, но нам надо его удалить
        if (current->prev != nullptr) { //предыдущий элемент существует
            current->prev->next = nullptr;
        }
        else { //предыдущий элемент не существует, т.е. мы удаляем единственный элемент в списке
            head = nullptr;
        }
        delete current;
    }
}

// Функция для добавления элемента перед элементом с заданным ключом
void addNode(Node*& head, int key) {
    Node* current = head;
    Node* prev = NULL;
    while (current != nullptr) {
        if (current->data == key) {
            int NewKey;
            cout << "Введите значение нового элемента: ";
            cin >> NewKey;
            Node* newNode = createNode(NewKey);
            if (prev != NULL) {
                prev->next = newNode;
                newNode->prev = prev;
            }
            else {
                head = newNode;
            }
            newNode->next = current;
        }
        prev = current;
        current = current->next;
    }
}

// Функция для уничтожения списка
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция для сохранения списка в файл
void SaveList(Node* head) {
    Node* current = head;
    char FName[] = "list.txt"; //Путь к файлу
    ofstream f1(FName, ios_base::out | ios_base::binary);   // открываем файл для записи
    while (current != nullptr) {
        f1.write((char*)current, sizeof(Node));   /*записываем структуру в файл*/
        current = current->next;
    }
    f1.close();     // закрываем файл
}

// Функция для чтения списка из файла
Node* LoadList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node current;
    char FName[] = "list.txt"; //Путь к файлу
    ifstream f2(FName);  // открываю файл для чтения
    if (!f2) {
        cout << "Файл не существует\n\n";
        f2.close();
        return nullptr;
    }
    f2.seekg(0, ios::end);      //функция перехода в конец файла
    long NumBytes = (long)f2.tellg();  //выяснение кол-ва байтов в файле
    float NumStruct = NumBytes / sizeof(Node);  //выяснение кол-ва структур в файле
    f2.seekg(0, ios::beg);      //переход в начало файла
    for (int i = 1; i <= NumStruct; i++) {
        f2.read((char*)&current, sizeof(Node));  // запись структуры из файла в переменную current
        Node* newNode = createNode(current.data);
        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }
    f2.close();
    return head;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "ru");
    cout << "Создание списка" << endl;
    Node* head = createList();
    printList(head);

    cout << "Добавление элемента перед элементом с заданным ключом" << endl;
    int key;
    cout << "Введите ключ, перед которым необходимо добавить элемент: ";
    cin >> key;
    addNode(head, key);
    printList(head);

    cout << "Удаление заданного количества элементов, начиная с заданного номера" << endl;
    int index;
    cout << "Введите номер первого удаляемого элемента: ";
    cin >> index;
    int number;
    cout << "Введите количество удаляемых элементов: ";
    cin >> number;
    deleteNodes(head, index, number);
    printList(head);

    cout << "Сохранение списка в файл" << endl;
    SaveList(head);
    printList(head);

    cout << "Уничтожение списка" << endl;
    deleteList(head);
    printList(head);

    cout << "Восстановление списка из файла" << endl;
    head = LoadList();
    printList(head);

    cout << "Уничтожение списка" << endl;
    deleteList(head);
    printList(head);
    return 0;
}