#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};

Stack* initializeStack() {
    Stack* stack = new Stack;
    stack->top = nullptr;
    return stack;
}

void push(Stack* s, int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->p_next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (s->top == nullptr) {
        return -1;
    }
    NODE* temp = s->top;
    int value = temp->key;
    s->top = s->top->p_next;
    delete temp;
    return value;
}

bool isEmpty(Stack* s) {
    return s->top == nullptr;
}


NODE* reverseList(NODE* head) {
    NODE* prev = nullptr;
    NODE* current = head;
    while (current != nullptr) {
        NODE* next = current->p_next;
        current->p_next = prev;
        prev = current;
        current = next;
    }
    return prev;
}


void printStack(Stack* s, ofstream& outfile) {
    if (isEmpty(s)) {
        outfile << "EMPTY" << endl;
        return;
    }

    // Đảo ngược stack tạm để in từ bottom lên top
    NODE* reversed = reverseList(s->top);
    NODE* temp = reversed;

    while (temp != nullptr) {
        outfile << temp->key;
        if (temp->p_next != nullptr)
            outfile << " ";
        temp = temp->p_next;
    }
    outfile << endl;

    // Khôi phục lại stack ban đầu bằng cách reverse lại một lần nữa
    reverseList(reversed);
}


int main() {
    string inputfile = "input.txt";
    string outputfile = "output.txt";

    ifstream infile(inputfile);
    ofstream outfile(outputfile);

    if (!infile.is_open()) {
        cout << "Error: cannot open input file: " << inputfile << endl;
        return 1;
    }

    if (!outfile.is_open()) {
        cout << "Error: cannot open output file: " << outputfile << endl;
        return 1;
    }

    string command;
    Stack* s = nullptr;

    while (infile >> command) {
        if (command == "init") {
            if (s == nullptr) {
                s = initializeStack();
                outfile << "EMPTY" << endl;
            }
        }
        else if (command == "push") {
            int key;
            if (infile >> key && s != nullptr) {
                push(s, key);
                printStack(s, outfile);
            }
        }
        else if (command == "pop") {
            if (s != nullptr) {
                if (isEmpty(s)) {
                    outfile << "EMPTY" << endl;
                }
                else {
                    pop(s);
                    printStack(s, outfile);
                }
            }
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
