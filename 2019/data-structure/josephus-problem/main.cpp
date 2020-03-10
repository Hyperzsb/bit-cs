#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
struct info {
    int id;
};

class List {

private:
    struct node {
        int index;
        info information;
        node *previous;
        node *next;
    };
    node *_HEAD;
    int _length;

public:
    List(int length)
            : _length(length) {
        _HEAD = (node *) malloc(sizeof(node));
        _HEAD->index = 1;
        _HEAD->information.id = 1;
        _HEAD->previous = NULL;
        _HEAD->next = (node *) malloc(sizeof(node));
        node *current = _HEAD->next;
        node *previous = _HEAD;

        for (int i = 2; i < _length; i++) {
            current->index = i;
            current->information.id = i;
            current->previous = previous;
            current->next = (node *) malloc(sizeof(node));
            previous = current;
            current = current->next;
        }

        current->index = _length;
        current->information.id = _length;
        current->previous = previous;
        current->next = NULL;
    };

    ~List() {};

    void traversalList() {
        if (_length != 0) {
            cout << _HEAD->index << " " << _HEAD->information.id << endl;
            node *current = _HEAD->next;

            while (current != NULL) {
                cout << current->index << " " << current->information.id << endl;
                current = current->next;
            }

            return;
        } else {
            return;
        }
    };

    bool insertNode(int index, string name, string id) {
        return true;
    };

    node *findNodeByIndex(int index) {
        if (index >= 0 && index <= _length) {
            node *previous = _HEAD->previous, *current = _HEAD, *next = _HEAD->next;

            while (current->index != index) {
                previous = current;
                current = current->next;
                next = current->next;
            }

            return current;
        } else {
            return NULL;
        }
    };

    node *findnodeByInfo(info information) {
        return NULL;
    };

    /*
    *Description: Remove node from list by its index.
    */
    bool removeNodeByIndex(int index) {
        if (index > 0 && index <= _length) {
            node *previous = _HEAD->previous, *current = _HEAD, *next = _HEAD->next;

            while (current->index != index) {
                previous = current;
                current = current->next;
                next = current->next;
            }

            if (previous != NULL)
                previous->next = next;
            if (next != NULL)
                next->previous = previous;
            free(current);
            _length--;
            current = next;

            while (current != NULL) {
                current->index--;
                current = current->next;
                if (current != NULL) {
                    next = current->next;
                } else {
                    next = NULL;
                }
            }

            return true;
        } else {
            return false;
        }
    };

    bool removeNodeByInfo(info information) {
        return true;
    };

    void specialClear(int startNo, int step) {
        int outNo = 0, flag = 1;
        node *outNode;

        while (_length != 0) {
            if (flag == 1) {
                outNo = (startNo + step - 1) % _length;
                if (outNo == 0)
                    outNo = _length;
                outNode = this->findNodeByIndex(outNo);
                cout << outNode->information.id;
                this->removeNodeByIndex(outNo);
                startNo = outNo;
                flag++;
            } else if (flag == 10) {
                outNo = (startNo + step - 1) % _length;
                if (outNo == 0)
                    outNo = _length;
                outNode = this->findNodeByIndex(outNo);
                cout << " " << outNode->information.id << endl;
                this->removeNodeByIndex(outNo);
                startNo = outNo;
                flag = 1;
            } else {
                outNo = (startNo + step - 1) % _length;
                if (outNo == 0)
                    outNo = _length;
                outNode = this->findNodeByIndex(outNo);
                cout << " " << outNode->information.id;
                this->removeNodeByIndex(outNo);
                startNo = outNo;
                flag++;
            }
        }
        if (flag != 1)
            cout << endl;

        return;
    };
};

int main() {
    int perNum = 0, startNo = 0, step = 0;
    scanf("%d,%d,%d", &perNum, &startNo, &step);

    if (perNum < 1 || startNo < 1 || step < 1) {
        cout << "n,m,k must bigger than 0." << endl;
    } else if (startNo > perNum) {
        cout << "k should not bigger than n." << endl;
    } else {
        List list = List(perNum);
        list.specialClear(startNo, step);
    }

    return 0;
}