#include<cstdio>
#include<cstdlib>
#include<cstring>
namespace std_namespace{
	template<typename T>
	class GeneralizedList{
	public:
		GeneralizedList(char *list_string){
			if(strcmp(list_string,"()")==0){
				this.head.type=List;
				this.head.generalized_list=NULL;
				this.tail_list=NULL;
			}else{
				int str_length=strlen(list_string);
				for(int i=0;i<str_length;i++){
					
				}
			}
		}
		~GeneralizedList(){
			
		}
		char* GetHead(){
			
		}
		GeneralizedList GetTail(){
			
		}
		char* ToString(){
			
		}
		enum Type{Atom,List};
		
	private:
		struct Node{
			Type type;
			union{
				T data;
				GeneralizedList *generalized_list;
			};
		}head;
		GeneralizedList *tail_list;
	};
}
int main(){
	return 0;
}
