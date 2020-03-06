#include<iostream>
#include<cstdlib>
using namespace std;

struct Node {
	long long int id;
	long long int width;
	long long int height;
	Node *previous;
	Node *next;
};

Node *HEAD = NULL, *TAIL = NULL;
long long int SIZE = 0;

void pushBack(Node *newNode) {
	if (SIZE == 0) {
		HEAD = newNode;
		TAIL = newNode;
		newNode->previous = NULL;
		newNode->next = NULL;
		SIZE = 1;
	} else {
		newNode->previous = TAIL;
		newNode->next = NULL;
		TAIL->next = newNode;
		TAIL = newNode;
		SIZE++;
	}
	return ;
}

void erase(Node *oldNode) {
	if (oldNode->previous != NULL)
		oldNode->previous->next = oldNode->next;
	if (oldNode->next != NULL)
		oldNode->next->previous = oldNode->previous;
	delete oldNode;
	SIZE--;
	return ;
}

int main() {
	long long int mianShu = 0, deepest = INT_MAX, ans = 0, mian = 0;
	cin >> mianShu;
	mian = mianShu;
	long long int *ansList = (long long int *)malloc((mianShu + 10) * sizeof(long long int));
	Node **mianIndex = (Node **)malloc((mianShu + 10) * sizeof(Node *));
	Node *previous = NULL, *current = NULL, *next = NULL, *tmp = NULL;
	for (long long int i = 0; i < mianShu; i++) {
		Node *newNode = new Node;
		cin >> newNode->width >> newNode->height;
		newNode->id = i + 1;
		if (newNode->height < deepest) {
			deepest = newNode->height;
			current = newNode;
		}
		pushBack(newNode);
	}
	while (mianShu > 1) {
		previous = current->previous, next = current->next;
		int nextHeight[2] = {0}, flag = 0;
		if (previous != NULL) {
			nextHeight[0] = previous->height;
		} else {
			nextHeight[0] = INT_MAX;
		}
		if (next != NULL) {
			nextHeight[1] = next->height;
		} else {
			nextHeight[1] = INT_MAX;
		}
		if (nextHeight[0] < nextHeight[1]) {
			flag = 0;
		} else if (nextHeight[0] > nextHeight[1]) {
			flag = 1;
		}
		if (nextHeight[flag] > current->height) {
			ans += current->width;
			ansList[current->id - 1] = ans;
			ans += (nextHeight[flag] - current->height - 1) * current->width;
			mianShu--;
			switch (flag) {
				case 0: {
					previous->width += current->width;
					erase(current);
					current = previous;
					break;
				}
				case 1: {
					next->width += current->width;
					erase(current);
					current = next;
					break;
				}
			}
		} else {
			if (!flag) {
				current = previous;
			} else {
				current = next;
			}
		}
	}
	
	ans += current->width;
	ansList[current->id-1] = ans;
	for (long long int i = 0; i < mian; i++ )
		cout << ansList[i] << endl;
	return 0;
}

