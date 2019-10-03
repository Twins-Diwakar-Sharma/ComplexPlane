#ifndef H_STACK_H
#define H_STACK_H

#include <Node.h>
#include <vector>
#include <iostream>

class Stack
{
    private:
        std::vector<Node*> storage;
        int s_top = -1;
    public:
        int top();
        Node* get(int);
        void push(Node*);
        void pop();
        void clear();
        int getSize();
        void display();
};

#endif
