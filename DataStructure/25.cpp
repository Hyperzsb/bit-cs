#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<map>
namespace std_namespace {
	using namespace std;
	struct Node {
		string name;
		Node *boss;
		Node *older_peer;
		Node *younger_peer;
		int employee_num;
		Node *first_employee;
		Node *last_employee;
		Node(const string &name_) {
			name = name_;
			boss = NULL;
			employee_num = 0;
			first_employee = NULL;
			last_employee = NULL;
			older_peer = NULL;
			younger_peer = NULL;
		}
	};
	void Traverse(Node *boss, int depth) {
		if (boss == NULL) {
			return ;
		}
		for (int i = 0; i < depth; i++) {
			printf("+");
		}
		printf("%s\n", boss->name.c_str());
		Node *employee = boss->first_employee;
		while (employee != NULL) {
			Traverse(employee, depth + 1);
			employee = employee->younger_peer;
		}
		return ;
	}
	void Hire(map<string, Node *> &person_map, string employer_name, string employee_name) {
		map<string, Node *>::iterator iter = person_map.find(employer_name);
		Node *boss = iter->second;
		//printf("Hire: %s %s\n", boss->name.c_str(), employee_name.c_str());
		Node *employee = new Node(employee_name);
		employee->boss = boss;
		person_map.insert(pair<string, Node *>(employee_name, employee));
		if (boss->employee_num == 0) {
			boss->first_employee = employee;
			boss->last_employee = employee;
			boss->employee_num++;
			employee->older_peer = NULL;
			employee->younger_peer = NULL;
		} else {
			employee->older_peer = boss->last_employee;
			boss->last_employee->younger_peer = employee;
			boss->employee_num++;
			boss->last_employee = employee;
			employee->younger_peer = NULL;
		}
		//printf("Hire successed\n");
		return ;
	}
	void Fire(map<string, Node *> &person_map, string employee_name) {
		map<string, Node *>::iterator iter = person_map.find(employee_name);
		person_map.erase(iter);
		Node *employee = iter->second, *boss = employee;
		//printf("Fire: %s\n", employee->name.c_str());
		while (boss->employee_num != 0) {
			boss->name.assign(boss->first_employee->name);
			boss = boss->first_employee;
		}
		if (boss->older_peer != NULL) {
			boss->older_peer->younger_peer = boss->younger_peer;
		} else {
			if (boss->younger_peer != NULL) {
				boss->younger_peer->older_peer = NULL;
			}
			boss->boss->first_employee = boss->younger_peer;
			boss->boss->employee_num--;
		}
		delete boss;
		//printf("Fire successed\n");
	}
}

int main() {
	using namespace std_namespace;
	map<string, Node *> person_map;
	string name, command_str, employer, employee;
	cin >> name;
	Node *boss = new Node(name);
	boss->boss = NULL;
	person_map.insert(pair<string, Node *>(name, boss));
	cin.get();
	while (getline(cin, command_str)) {
		if (cin.eof()) {
			break;
		}
		if (command_str.compare("print") == 0) {
			Traverse(boss, 0);
			printf("------------------------------------------------------------\n");
		} else {
			if (command_str.compare(0, 4, "fire", 4) == 0) {
				employee.assign(command_str, 5, string::npos);
				Fire(person_map, employee);
			} else {
				int index = command_str.find("hires");
				employer.assign(command_str, 0, index - 1);
				employee.assign(command_str, index + 6, string::npos);
				Hire(person_map, employer, employee);
			}
		}
	}


	return 0;
}

