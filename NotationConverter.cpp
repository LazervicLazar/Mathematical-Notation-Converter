/* 
 * Notation Converter Project using Doubly Linked Lists implemented as a Deque.
 *
 * This program implements a Notation Converter using deque data structure.
 * It can convert from postfixToInfix, postfixToPrefix, infixToPostfix, infixToPrefix, prefixToInfix, prefixToPostfix depending on the user's input.
 *
*/


#include "NotationConverter.hpp"
NotationConverter::NotationConverter() {
        header = new Node;
        trailer = new Node;
        header->prev = NULL;
        trailer->next = NULL;
        header->next = trailer;
        trailer->prev = header;
    }

NotationConverter::~NotationConverter() {
        Node* current = header;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

void NotationConverter::add(Node *v, string operand) {
	//Adds a node before the node v, with the given operand
    Node *newNode = new Node;
    newNode->operand = operand;
    newNode->next = v;
    newNode->prev = v->prev;
    v->prev->next = newNode;
    v->prev = newNode;
}


void NotationConverter::remove(Node *v) {
	//Removes the node v
    Node *prev = v->prev;
    Node *next = v->next;
    prev->next = next;
    next->prev = prev;
    delete v;
}

string NotationConverter::top() {
	//Returns the operand of the first node
    return header->next->operand;
}


void NotationConverter::insertFront(string operand) {
	//Adds a node at the front of the deque
    add(header->next, operand);
}


void NotationConverter::removeFront() {
	//Removes the first node of the deque
    remove(header->next);
}


void NotationConverter::insertBack(string operand) {
	//Adds a node at the back of the deque
    add(trailer, operand);
}

void NotationConverter::removeBack() {
	//Removes the last node of the deque
    remove(trailer->prev);
}

void NotationConverter::removeAll() {
	//Removes all nodes of the deque
    while (!empty()) {
        removeFront();
    }
}

bool NotationConverter::empty() {
	//Returns true if the deque is empty
    return (header->next == trailer);
}


void NotationConverter::printitems() {
	//Prints all the operands in the deque
    cout << "___" << '\n';
    for (Node *p = header->next; p->next != NULL; p = p->next) {
        cout << p->operand << '\n';
    }
    cout << "___" << '\n';
}


bool NotationConverter::isOperator(char c) {
	//Returns true if the character is an operator
	if(c=='+'||c=='-'||c=='*'||c=='/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int NotationConverter::precedence(char c) { 
	//Returns the precedence of the operator
    if(c == '*' || c == '/') 
    return 2; 
    else if(c == '+' || c == '-') 
    return 1; 
    else
    return -1; 
} 


string NotationConverter::postfixToInfix(string postfix) {
	//Converts postfix to infix
    for (int i = 0; postfix[i] != '\0'; i++) {
		//Skips spaces
        if (postfix[i] == ' ') {
            continue;
        }
	    //If the character is an operand, it is added to the front of the deque
        if (isalpha(postfix[i])) {
            insertFront(string(1, postfix[i]));
        } else if (isOperator(postfix[i])) {
			//If the character is an operator, the first two operands are removed from the front of the deque and the operator is added to the middle of the two operands
            string operand1 = top();
            removeFront();
            string operand2 = top();
            removeFront();
            string temp = "(" + operand2 + " " + postfix[i] + " " + operand1 + ")";
            insertFront(temp);
        } 
		else {
			//If the character is not an operand or an operator, an error is thrown
			throw std::runtime_error("Invalid character!");
		}
		
    }
	//The infix notation is returned
    string str = top();
    removeAll();
    return str;
}

string NotationConverter::prefixToInfix(string prefix) {
	//Converts prefix to infix
	//The prefix is reversed
    reverse(prefix.begin(), prefix.end());
    for (int i = 0; prefix[i] != '\0'; i++) {
		//Skips spaces
		if (prefix[i] == ' ') {
            continue;
        }
		//If the character is an operand, it is added to the front of the deque
        if (isalpha(prefix[i])) {
            insertFront(string(1, prefix[i]));
        } else if (isOperator(prefix[i])) {
			//If the character is an operator, the first two operands are removed from the front of the deque and the operator is added to the middle of the two operands
            string operand1 = top();
            removeFront();
            string operand2 = top();
            removeFront();
            string temp = "(" + operand1 + " " + prefix[i] + " " + operand2 + ")";
            insertFront(temp);
        } 
		else {
			//If the character is not an operand or an operator, an error is thrown
			throw std::runtime_error("Invalid character!");
		}

    }
	//The infix notation is returned
    string str = top();
    removeAll();
    return str;
}

string NotationConverter::infixToPostfix(string infix) {
	//Converts infix to postfix
	string postfix;
	for(int i=0;i<infix.length();i++) {
		//Skips spaces
		if (infix[i] ==  ' ') {
			continue;
		}
		//If the character is an operand, it is added to the postfix string
		if(isalpha(infix[i])) {

			postfix+=infix[i];
			postfix += " ";

		} else if(infix[i] == '(') {
			//If the character is an opening parenthesis, it is added to the front of the deque
            string temp(1, infix[i]);
			insertFront(temp);

		} else if(infix[i] == ')') {
			//If the character is a closing parenthesis, all the operators are removed from the front of the deque and added to the postfix string until an opening parenthesis is reached
			while((top()[0]!='(') && (!empty())) {

				char temp=top()[0];
				postfix+=temp;
				postfix += " ";
				removeFront();
			}

			if(top()[0]=='(') {
				//The opening parenthesis is removed
				removeFront();
			}
		} 
		else if(isOperator(infix[i])) {
			//If the character is an operator, it is added to the front of the deque
			if(empty())
			{
				string temp(1, infix[i]);
			    insertFront(temp);
			} else {
				//Based on precedence, the operator is added to the front of the deque or removed from the front of the deque and added to the postfix string
				if(precedence(infix[i])>precedence(top()[0])) {
					string temp(1, infix[i]);
			        insertFront(temp);
				} else if((precedence(infix[i])==precedence(top()[0]))&&(infix[i]=='^')) {
					string temp(1, infix[i]);
			        insertFront(temp);
				} else {
					while((!empty())&&(precedence(infix[i])<=precedence(top()[0]))) {
						postfix+= top();
						removeFront();
					}
					string temp(1, infix[i]);
			        insertFront(temp);
				}
			}
		} else {
			//If the character is not an operand or an operator, an error is thrown
			throw std::runtime_error("Invalid character!");
		}
	}
	while(!empty()) {
		//All the operators are removed from the front of the deque and added to the postfix string
		postfix +=  top();
		removeFront();
	}
	//The postfix string is returned
	return postfix;
}

string NotationConverter::infixToPrefix(string infix) {
	//Converts infix to prefix
	//The infix is reversed
    reverse(infix.begin(), infix.end());
	string prefix;
	for(int i = 0; i < infix.length(); i++) { 	
		//Skips spaces
		if (infix[i] ==  ' ') {
			continue;
		}
		//If the character is an operand, it is added to the prefix string
		if(isalpha(infix[i])) {

			prefix+= infix[i];
			prefix += " ";

		} else if(infix[i] == ')') {
			//If the character is an opening parenthesis, it is added to the front of the deque
            string temp(1, infix[i]);
			insertFront(temp);

		} else if(infix[i] == '(') {
			//If the character is a closing parenthesis, all the operators are removed from the front of the deque and added to the prefix string until an opening parenthesis is reached
			while((top()[0]!=')') && (!empty())) {

				char temp=top()[0];
				prefix+=temp;
				prefix += " ";
				removeFront();

			}
			//The opening parenthesis is removed
			if(top()[0]==')') {
				removeFront();
			}
		} else if(isOperator(infix[i])) {
			//If the character is an operator, it is added to the front of the deque
			if(empty()) {
				string temp(1, infix[i]);
			    insertFront(temp);
			} else {
				//based on precedence, the operator is added to the front of the deque or removed from the front of the deque and added to the prefix string
				if(precedence(infix[i])>precedence(top()[0])) {
					string temp(1, infix[i]);
			        insertFront(temp);
				} else if ((precedence(infix[i])==precedence(top()[0]))&&(infix[i]=='^')) {
					string temp(1, infix[i]);
			        insertFront(temp);
				} else {
					while((!empty())&&( precedence(infix[i])<=precedence(top()[0]))) {
						prefix+= top();
						removeFront();
					}
					string temp(1, infix[i]);
			        insertFront(temp);
				}
			}
		} else {
			//If the character is not an operand or an operator, an error is thrown
			throw std::runtime_error("Invalid character!");
		} 
	}
	while(!empty()) {
		//All the operators are removed from the front of the deque and added to the prefix string
		prefix += top();	
		removeFront();
	}
	//The prefix string is reversed and returned
	reverse(prefix.begin(), prefix.end());
	return prefix;
}

string NotationConverter::postfixToPrefix(string postfix) {
	//Converts postfix to prefix
	for(int i=0;i<postfix.length();i++) {
		//Evaluates for invalid characters
		if (!isalpha(postfix[i]) && !(isOperator(postfix[i])) && postfix[i] != ' '){
			throw std::runtime_error("Invalid character!");
		}

	}
	//conversion is done using above methods
	string str1 = postfixToInfix(postfix);
	string str2 = infixToPrefix(str1);
	return str2;
}

string NotationConverter::prefixToPostfix(string prefix) {
	//Converts prefix to postfix
	for(int i=0;i<prefix.length();i++) {
		//Evaluates for invalid characters
		if (!isalpha(prefix[i]) && !(isOperator(prefix[i])) && prefix[i] != ' '){
			throw std::runtime_error("Invalid character!");
		}

	}
	//conversion is done using above methods
	string str1 = prefixToInfix(prefix);
	string str2 = infixToPostfix(str1);
	return str2;
}

int main() {
    NotationConverter notationConverter;

    cout << "Notation Converter Project" << endl;
    cout << "Available Conversions:" << endl;
    cout << "1. Postfix to Infix" << endl;
    cout << "2. Postfix to Prefix" << endl;
    cout << "3. Infix to Postfix" << endl;
    cout << "4. Infix to Prefix" << endl;
    cout << "5. Prefix to Infix" << endl;
    cout << "6. Prefix to Postfix" << endl;
    cout << "Enter the conversion option (1-6): ";

    int conversionChoice;
    cin >> conversionChoice;
    cin.ignore(); // Consume the newline character

    string inputExpression;
    cout << "Enter the expression to convert: ";
    getline(cin, inputExpression);

    string result;

    try {
        switch (conversionChoice) {
            case 1:
                result = notationConverter.postfixToInfix(inputExpression);
                break;
            case 2:
                result = notationConverter.postfixToPrefix(inputExpression);
                break;
            case 3:
                result = notationConverter.infixToPostfix(inputExpression);
                break;
            case 4:
                result = notationConverter.infixToPrefix(inputExpression);
                break;
            case 5:
                result = notationConverter.prefixToInfix(inputExpression);
                break;
            case 6:
                result = notationConverter.prefixToPostfix(inputExpression);
                break;
            default:
                cerr << "Invalid conversion choice." << endl;
                return 1;
        }

        cout << "Result: " << result << endl;
    } catch (const runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}