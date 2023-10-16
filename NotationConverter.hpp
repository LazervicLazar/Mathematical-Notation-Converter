#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;

class Node {
    //Node class for doubly linked list
    private:
        string operand;
        Node *next;
        Node *prev;

        Node() {
            string operand = " ";
            Node *next = NULL;
            Node *prev = NULL;
        }
    friend class NotationConverter;

};

class NotationConverter {
    //NotationConverter class for converting between infix, prefix, and postfix notation
    private:
        Node *header;
        Node *trailer;

    public:

    NotationConverter();
    ~NotationConverter();
    void add(Node *v, string operand);
    void remove(Node *v);
    bool empty();
    string top();
    string bottom();

    int precedence(char c);
    bool isOperator(char c);

    void insertFront(string operand);
    void removeFront();
    void insertBack(string operand);
    void removeBack();
    void removeAll();
    void printitems();

    string postfixToInfix(std::string inStr);
    //This method takes in a string of postfix notation and returns a string in the infix notation 

    string postfixToPrefix(std::string inStr); 
    //This method takes in a string of postfix notation and returns a string in the prefix notation 

    string infixToPostfix(std::string inStr); 
    //This method takes in a string of infix notation and returns a string in the postfix notation 

    string infixToPrefix(std::string inStr); 
    //This method takes in a string of infix notation and returns a string in the prefix notation 

    string prefixToInfix(std::string inStr); 
    //This method takes in a string of prefix notation and returns a string in the postfix notation 

    string prefixToPostfix(std::string inStr); 
    //This method takes in a string of prefix notation and returns a string in the postfix notation

};