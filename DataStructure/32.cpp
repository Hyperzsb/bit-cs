#include<cstdio>
#include<iostream>
#include<string>
#include<map>
using namespace std;
int main() {
	int mapSize[2] = {0};
	map<int, string> map1, map2;
	cin >> mapSize[0];
	for (int i = 0; i < mapSize[0]; i++) {
		int stuNum = 0;
		string stuName;
		cin >> stuNum >> stuName;
		pair<int, string> stu(stuNum, stuName);
		map1.insert(stu);
	}
	cin >> mapSize[1];
	for (int i = 0; i < mapSize[1]; i++) {
		int stuNum = 0;
		string stuName;
		cin >> stuNum >> stuName;
		pair<int, string> stu(stuNum, stuName);
		map2.insert(stu);
	}
	if (mapSize[1] == 0) {
		cout << "the LIST2 is NULL." << endl;
	} else {
		int flag = 1;
		map<int, string>::iterator stuIter = map2.begin();
		for (; stuIter != map2.end(); stuIter++) {
			map<int, string>::iterator findIter = map1.find(stuIter->first);
			if (findIter == map1.end()) {
				cout << stuIter->first << " " + stuIter->second << " is not in LIST1." << endl;
				flag = 0;
			} else {
				if (stuIter->second != findIter->second) {
					cout << stuIter->first << " " + stuIter->second << " is not in LIST1." << endl;
					flag = 0;
				} else {
					continue;
				}
			}
		}
		if (flag) {
			cout << "the records of LIST2 are all in the LIST1." << endl;
		}
	}
	return 0;
}
