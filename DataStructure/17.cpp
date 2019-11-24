#include<cstdio>
#include<cstdlib>
#include<string>
namespace std_namespace {
	using std::string;
	template<typename T>
	class GetTree {
	private:
		struct Node {
			T data;
			Node *left_child;
			Node *right_child;
		};
		Node *root;
		Node *CreateTree(char *in_order_str, char *post_order_str, Node *root) {
			
		}
		void GetPreOrderStr(Node *root){
			
		}

	public:
		GetTree(char *in_order_str, char *post_order_str) {
			CreateTree(in_order_str, post_order_str, this->root);
		}
		~GetTree() {}
		void PreOrderTraverse() {
			GetPreOrderStr(this->root);
		}
	};
}

int main() {
	using namespace std_namespace;
	char in_order_str[1000] = {'\0'}, post_order_str[1000] = {'\0'};
	scanf("%s%s", in_order_str, post_order_str);
	GetTree tree = new GetTree(in_order_str, post_order_str);
	tree->PreOrderTraverse();
	return 0;
}

