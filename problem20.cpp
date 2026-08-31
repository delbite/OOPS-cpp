#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int v) : prev(p), next(n), key(k), value(v) {}
    Node(int k, int v) : prev(nullptr), next(nullptr), key(k), value(v) {}
};

class Cache {
protected:
    map<int, Node*> mp;
    int cp;
    Node* tail;
    Node* head;
    virtual void set(int, int) = 0;
    virtual int get(int) = 0;
};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        cp = capacity;
        head = nullptr;
        tail = nullptr;
    }

    void set(int key, int value) override {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            detach(node);
            moveToHead(node);
        } else {
            Node* node = new Node(key, value);
            if (mp.size() >= static_cast<size_t>(cp)) {
                mp.erase(tail->key);
                removeTail();
            }
            moveToHead(node);
            mp[key] = node;
        }
    }

    int get(int key) override {
        if (mp.find(key) == mp.end()) {
            return -1;
        }
        Node* node = mp[key];
        detach(node);
        moveToHead(node);
        return node->value;
    }

private:
    void detach(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
    }

    void moveToHead(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head) {
            head->prev = node;
        }
        head = node;
        if (!tail) {
            tail = head;
        }
    }

    void removeTail() {
        if (!tail) return;
        Node* temp = tail;
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            head = nullptr;
            tail = nullptr;
        }
        delete temp;
    }
};

int main() {
    int n, capacity;
    cin >> n >> capacity;
    LRUCache lru(capacity);
    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << lru.get(key) << "\n";
        } else if (command == "set") {
            int key, value;
            cin >> key >> value;
            lru.set(key, value);
        }
    }
    return 0;
}