#include <iostream>


struct Node {
    long long value;
    Node* next;
    Node(long long val) {
        value = val;
        next = nullptr;
    }
};

class Stack {
    private:
        Node* top;

    public:
        Stack() {
            top = nullptr;
        }

        ~Stack() {
            while (!is_empty()) {
                pop();
            }
        }

        void push(long long value) {
            Node* new_node = new Node(value);
            new_node -> next = top;
            top = new_node;
        }

        long long pop() {
            if (is_empty()) {
                return -1;
            }
            Node* temp = top;
            long long value = top -> value;
            top = top -> next;
            delete temp;
            return value;
        }

        long long peek() {
            if (is_empty()) {
                return -1;
            }
            return top -> value;
        }

        bool is_empty() {
            return top == nullptr;
        }
};


int main() {
    int N;
    std::cin >> N;
    long long* heights = new long long[N];
    long long* left = new long long[N];
    long long* right = new long long[N];

    for (int i = 0; i < N; i++) {
        std::cin >> heights[i];
    }

    Stack stack;

    for (int i = 0; i < N; i++) {
        while(!stack.is_empty() && heights[stack.peek()] >= heights[i]) {
            stack.pop();
        }

        if (stack.is_empty()) {
            left[i] = -1;
        } else {
            left[i] = stack.peek();
        }

        stack.push(i);
    }

    while (!stack.is_empty()) {
        stack.pop();
    }

    for (int i = N - 1; i >= 0; i--) {
        while (!stack.is_empty() && heights[stack.peek()] >= heights[i]) {
            stack.pop();
        }

        if (stack.is_empty()) {
            right[i] = N;
        } else {
            right[i] = stack.peek();
        }

        stack.push(i);
    }

    long long max_area = 0;
    for (int i = 0; i < N; i++) {
        long long width = right[i] - left[i] - 1;
        long long area = width * heights[i];
        if (max_area < area) {
            max_area = area;
        }
    }

    std::cout << max_area;

    delete[] heights;
    delete[] left;
    delete[] right;
}
