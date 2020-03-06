#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
using namespace std;
class Student {
public:
	int id;
	std::string name;
	Student(int id, string name) {
		this->id = id;
		this->name.assign(name);
	}
};
int main() {
	int list_length[2] = {0};
	scanf("%d", &list_length[0]);
	Student **student_list = (Student **)malloc(list_length[0] * sizeof(Student *));
	int tmp_id;
	string tmp_name;
	for (int i = 0; i < list_length[0]; i++) {
		cin >> tmp_id >> tmp_name;
		student_list[i] = new Student(tmp_id, tmp_name);
	}
	scanf("%d", &list_length[1]);
	if (list_length[1] == 0) {
		printf("the LIST2 is NULL.\n");
	} else {
		int flag = 1;
		for (int i = 0; i < list_length[1]; i++) {
			cin >> tmp_id >> tmp_name;
			int flag_1 = 1;
			for (int j = 0; j < list_length[0]; j++)
				if (student_list[j]->id == tmp_id && student_list[j]->name.compare(tmp_name) == 0) {
					flag_1 = 0;
					break;
				}
			if (flag_1) {
				printf("%d %s is not in LIST1.\n", tmp_id, tmp_name.c_str());
				flag = 0;
			}
		}
		if(flag)
			printf("the records of LIST2 are all in the LIST1.\n");
	}
	return 0;
}
