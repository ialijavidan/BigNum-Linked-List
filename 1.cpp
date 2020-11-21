#include <bits/stdc++.h>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
	int data;
	Node* next;
};

typedef Node node;

void push(Node** head_ref, int new_data)
{
	Node* new_node = new Node[(sizeof(Node))];

	new_node->data = new_data;

	new_node->next = (*head_ref);

	(*head_ref) = new_node;
}

void printList(Node* node)
{
	while (node != NULL) {
		cout << node->data << " ";
		node = node->next;
	}
	cout << endl;
}

void swapPointer(Node** a, Node** b)
{
	node* t = *a;
	*a = *b;
	*b = t;
}

int getSize(Node* node)
{
	int size = 0;
	while (node != NULL) {
		node = node->next;
		size++;
	}
	return size;
}

node* addSameSize(Node* head1, Node* head2, int* carry)
{
	if (head1 == NULL)
		return NULL;

	int sum;

	Node* result = new Node[(sizeof(Node))];

	result->next
		= addSameSize(head1->next, head2->next, carry);

	sum = head1->data + head2->data + *carry;
	*carry = sum / 10;
	sum = sum % 10;

	result->data = sum;

	return result;
}

void addCarryToRemaining(Node* head1, Node* cur, int* carry,
						Node** result)
{
	int sum;

	if (head1 != cur) {
		addCarryToRemaining(head1->next, cur, carry,
							result);

		sum = head1->data + *carry;
		*carry = sum / 10;
		sum %= 10;

		push(result, sum);
	}
}

void addList(Node* head1, Node* head2, Node** result)
{
	Node* cur;

	if (head1 == NULL) {
		*result = head2;
		return;
	}

	else if (head2 == NULL) {
		*result = head1;
		return;
	}

	int size1 = getSize(head1);
	int size2 = getSize(head2);

	int carry = 0;

	if (size1 == size2)
		*result = addSameSize(head1, head2, &carry);

	else {
		int diff = abs(size1 - size2);

		if (size1 < size2)
			swapPointer(&head1, &head2);

		for (cur = head1; diff--; cur = cur->next)
			;

		*result = addSameSize(cur, head2, &carry);

		addCarryToRemaining(head1, cur, &carry, result);
	}

	if (carry)
		push(result, carry);
}

vector<int> splitBySpace(string s){
    vector<int> result; 
    istringstream iss(s); 
    for(string s; iss >> s; ){
        stringstream geek(s); 
        int x;
        geek >> x; 
        result.push_back(x);
    }

    return result;
}

// Driver code
int main()
{
	Node *head1 = NULL, *head2 = NULL, *result = NULL;

    string n, m;
    getline (cin, n);
    getline (cin, m);
    vector<int> v1 = splitBySpace(n);
    vector<int> v2 = splitBySpace(m);

	int i;
	for (i = v1.size() - 1; i >= 0; --i)
		push(&head1, v1[i]);

	for (i = v2.size() - 1; i >= 0; --i)
		push(&head2, v2[i]);

	addList(head1, head2, &result);

	printList(result);

	return 0;
}