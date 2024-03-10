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

        // Неконстантная версия оператора разыменования
        T& operator*() {
            return current->data;
        }

        // Константная версия оператора разыменования
        const T& operator*() const {
            return current->data;
        }

        // Неконстантная версия оператора доступа к члену через указатель
        T* operator->() {
            return &(current->data);
        }

        // Константная версия оператора доступа к члену через указатель
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

