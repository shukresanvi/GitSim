
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

private:

    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    int count;

public:

    // Constructor
    LinkedList() {
        head = nullptr;
        count = 0;
    }

    // Prevent accidental shallow copying of pointers
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Add a new node
    void append(T value) {

        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;

            while (temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = newNode;
        }

        count++;
    }

    // Find an element using a condition
    template <typename Predicate>
    T* find(Predicate condition) {

        Node* temp = head;

        while (temp != nullptr) {

            if (condition(temp->data)) {
                return &(temp->data);
            }

            temp = temp->next;
        }

        return nullptr;
    }

    // Traverse the linked list
    template <typename Function>
    void forEach(Function action) const {

        Node* temp = head;

        while (temp != nullptr) {
            action(temp->data);
            temp = temp->next;
        }
    }

    // Return number of nodes
    int size() const {
        return count;
    }

    // Check whether list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Delete all nodes
    void clear() {

        while (head != nullptr) {

            Node* temp = head;
            head = head->next;

            delete temp;
        }

        count = 0;
    }

    // Destructor
    ~LinkedList() {
        clear();
    }
};

#endif
