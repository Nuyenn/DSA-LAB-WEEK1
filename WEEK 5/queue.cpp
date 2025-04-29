#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = nullptr;
    q->tail = nullptr;
    return q;
}

void enqueue(Queue& q, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = nullptr;

    if (q.head == nullptr) {
        q.head = q.tail = newNode;
    }
    else {
        q.tail->p_next = newNode;
        q.tail = newNode;
    }
}

int dequeue(Queue& q) {
    if (q.head == nullptr) return -1;

    NODE* temp = q.head;
    int val = temp->key;
    q.head = q.head->p_next;
    if (q.head == nullptr) q.tail = nullptr;
    delete temp;
    return val;
}

bool isEmpty(Queue q) {
    return (q.head == nullptr);
}

void printQueue(ofstream& fout, Queue q) {
    if (q.head == nullptr) {
        fout << "EMPTY\n";
        return;
    }
    NODE* current = q.head;
    while (current != nullptr) {
        fout << current->key;
        if (current->p_next != nullptr) fout << " ";
        current = current->p_next;
    }
    fout << "\n";
}

void destroyQueue(Queue*& q) {
    while (q->head != nullptr) {
        NODE* temp = q->head;
        q->head = q->head->p_next;
        delete temp;
    }
    delete q;
    q = nullptr;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Failed to open input or output file.\n";
        return 1;
    }

    string line;
    Queue* q = nullptr;

    while (getline(fin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "init") {
            if (q != nullptr) destroyQueue(q);
            q = initializeQueue();
            fout << "EMPTY\n";
        }
        else if (command == "enqueue") {
            int val;
            if (q != nullptr && ss >> val) {
                enqueue(*q, val);
                printQueue(fout, *q);
            }
        }
        else if (command == "dequeue") {
            if (q != nullptr) {
                int result = dequeue(*q);
                if (result == -1)
                    fout << "EMPTY\n";
                printQueue(fout, *q);
            }
        }
        // Không in gì nếu lệnh không hợp lệ
    }

    if (q != nullptr) destroyQueue(q);

    fin.close();
    fout.close();
    return 0;
}
