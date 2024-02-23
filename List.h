//#pragma once
//
//template<typename T>
//class List {
//    struct Node {
//        T data;
//        Node* next;
//        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
//    };
//
//    Node* head;
//
//public:
//    class iterator {
//        Node* current;
//    public:
//        iterator(Node* node) : current(node) {}
//        iterator& operator++() { current = current->next; return *this; }
//        T& operator*() { return current->data; }
//        const T& operator*() const { return current->data; } // ����������� ������ ��������� *
//        T* operator->() { return &(current->data); }
//        const T* operator->() const { return &(current->data); } // ����������� ������ ��������� ->
//        bool operator!=(const iterator& other) { return current != other.current; }
//
//        friend class List;
//    };
//
//    List() : head(nullptr) {}
//    ~List() {
//        while (head) {
//            Node* temp = head;
//            head = head->next;
//            delete temp;
//        }
//    }
//
//    void push_back(const T& data) {
//        if (!head) {
//            head = new Node(data);
//        }
//        else {
//            Node* current = head;
//            while (current->next) {
//                current = current->next;
//            }
//            current->next = new Node(data);
//        }
//    }
//
//    void erase(iterator it) {
//        if (head == it.current) {
//            Node* temp = head;
//            head = head->next;
//            delete temp;
//        }
//        else {
//            Node* current = head;
//            while (current && current->next != it.current) {
//                current = current->next;
//            }
//            if (current) {
//                Node* temp = current->next;
//                current->next = current->next->next;
//                delete temp;
//            }
//        }
//    }
//
//    iterator begin() { return iterator(head); }
//    const iterator begin() const { return iterator(head); } // ����������� ������ ������ begin
//    iterator end() { return iterator(nullptr); }
//    const iterator end() const { return iterator(nullptr); } // ����������� ������ ������ end
//};


#include <iostream>
#include <exception>

template<typename T>
class List {
public:
    struct Node {
        T data;
        Node* next;
        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    class Iterator {
        friend class List;
    public:
        Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // ������������� ������ ��������� �������������
        T& operator*() {
            return current->data;
        }

        // ����������� ������ ��������� �������������
        const T& operator*() const {
            return current->data;
        }

        // ������������� ������ ��������� ������� � ����� ����� ���������
        T* operator->() {
            return &(current->data);
        }

        // ����������� ������ ��������� ������� � ����� ����� ���������
        const T* operator->() const {
            return &(current->data);
        }
    private:
        Node* current;
    };

    List() : head(nullptr) {}

    List(const List& other) : head(nullptr) {
        Node* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }

    ~List() {
        clear();
    }

    void push_back(T value) {
        if (head == nullptr) {
            head = new Node(value);
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new Node(value);
        }
    }

    void erase(Iterator it) {
        if (head == nullptr || it.current == nullptr) {
            throw std::runtime_error("Invalid iterator or empty list");
        }
        if (head == it.current) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }
        Node* current = head;
        while (current->next && current->next != it.current) {
            current = current->next;
        }
        if (current->next == it.current) {
            Node* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
        else {
            throw std::runtime_error("Iterator does not belong to this list");
        }
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

private:
    Node* head;
};

