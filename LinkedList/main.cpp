#include <iostream>
using namespace std;

// Node sınıfı tanımı
class Node {
public:
    int data;
    Node* next;

    // Yapıcı (constructor)
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Linked List sınıfı
class LinkedList {
public:
    Node* head;

    // Yapıcı (constructor)
    LinkedList() {
        head = nullptr;
    }

    // 1. Traversal: Linked List'te tüm elemanları gezip yazdırma
    void traverse() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // 2. Insertion: Linked List'in başına, sonuna veya istenen pozisyona ekleme

    // Başına ekleme
    void insertAtHead(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Sonuna ekleme
    void insertAtEnd(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Belirli bir pozisyona ekleme (0-indexli)
    void insertAtPosition(int position, int data) {
        if (position == 0) {
            insertAtHead(data);
            return;
        }
        Node* newNode = new Node(data);
        Node* temp = head;
        for (int i = 0; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Pozisyon geçersiz!" << endl;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // 3. Deletion: Linked List'ten düğüm silme

    // Baştan silme
    void deleteAtHead() {
        if (head == nullptr) {
            cout << "Liste boş!" << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Son düğümü silme
    void deleteAtEnd() {
        if (head == nullptr) {
            cout << "Liste boş!" << endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // Belirli bir pozisyondan silme
    void deleteAtPosition(int position) {
        if (position == 0) {
            deleteAtHead();
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr) {
            cout << "Pozisyon geçersiz!" << endl;
            return;
        }
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }
    // Sorted Insertion: Sıralı şekilde düğüm ekler
    void sortedInsert(int data) {
        Node* newNode = new Node(data);

        // Eğer liste boşsa veya yeni düğüm ilk düğümden küçükse başa ekle
        if (head == nullptr || head->data >= newNode->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Uygun yeri bulana kadar listeyi gez
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data < newNode->data) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Iterative Reversal
    void reverseIterative() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr != nullptr) {
            next = curr->next;  // Sonraki düğümü sakla
            curr->next = prev;  // Mevcut düğümün yönünü ters çevir
            prev = curr;        // Önceki düğüm güncelle
            curr = next;        // Sonraki düğüme geç
        }
        head = prev;  // Son düğüm yeni head olacak
    }
};

int main() {
    LinkedList list;

    // Ekleme işlemleri
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtHead(5);
    list.insertAtPosition(2, 15); // 2. pozisyona 15 ekle

    cout << "Linked List'in elemanları (Traversal): ";
    list.traverse(); // Listeyi gezip elemanları yazdır

    // Silme işlemleri
    list.deleteAtHead(); // Baştan sil
    cout << "Baştan silindikten sonra: ";
    list.traverse();

    list.deleteAtEnd(); // Sondan sil
    cout << "Sondan silindikten sonra: ";
    list.traverse();

    list.deleteAtPosition(1); // 1. pozisyondaki elemanı sil
    cout << "1. pozisyondaki eleman silindikten sonra: ";
    list.traverse();

    LinkedList list1;

    list1.sortedInsert(50);
    list1.sortedInsert(30);
    list1.sortedInsert(40);
    list1.sortedInsert(20);
    list1.sortedInsert(60);

    cout << "Sıralı eklemeden sonra Linked List: ";
    list1.traverse();  // Listeyi gezip elemanları yazdırır

    LinkedList list2;

    list2.insertAtEnd(10);
    list2.insertAtEnd(20);
    list2.insertAtEnd(30);
    list2.insertAtEnd(40);
    list2.insertAtEnd(50);

    cout << "Orijinal Linked List: ";
    list2.traverse();  // Orijinal listeyi yazdır

    list2.reverseIterative();

    cout << "Ters çevrildikten sonra (Iterative) Linked List: ";
    list2.traverse();


    return 0;
}
