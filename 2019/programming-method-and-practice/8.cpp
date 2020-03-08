#include<stdio.h>
#include<string.h>
#include<malloc.h>
char *calaulate(char *num1,int length1,char *num2,int length2,char *ans,char opt,int flag){
	if(opt=='+'){
		int jinWei=0,index=length1,tmp=0;
		ans[length1+1]='\0';
		for(int i=0;i<length2;i++){
			tmp=(num1[length1-1-i]-'0')+(num2[length2-1-i]-'0')+jinWei;
			if(tmp<10){
				ans[index]=tmp+'0';
				jinWei=0;
				index--;
			}else{
				ans[index]=(tmp-10)+'0';
				jinWei=1;
				index--;
			}
		}
		for(int i=0;i<length1-length2;i++){
			tmp=(num1[length1-length2-1-i]-'0')+jinWei;
			if(tmp<10){
				ans[index]=tmp+'0';
				jinWei=0;
				index--;
			}else{
				ans[index]=(tmp-10)+'0';
				jinWei=1;
				index--;
			}
		}
		if(jinWei==1){
			ans[index]='1';
			return ans;
		}else
			return ans+1;
	}else if(opt=='-'){
		int jinWei=0,index=length1,tmp=0;
		ans[length1+1]='\0';
		for(int i=0;i<length2;i++){
			tmp=(num1[length1-1-i]-'0')-(num2[length2-1-i]-'0')-jinWei;
			if(tmp>=0){
				ans[index]=tmp+'0';
				jinWei=0;
				index--;
			}else{
				ans[index]=(tmp+10)+'0';
				jinWei=1;
				index--;
			}
		}
		for(int i=0;i<length1-length2;i++){
			tmp=(num1[length1-length2-1-i]-'0')-jinWei;
			if(tmp>=0){
				ans[index]=tmp+'0';
				jinWei=0;
				index--;
			}else{
				ans[index]=(tmp+10)+'0';
				jinWei=1;
				index--;
			}
		}
		if(flag){
			if(ans[1]!='0')
				return ans+1;
			else
				return ans+2;
		}
		else{
			if(ans[1]!='0'){
				ans[0]='-';
				return ans;
			}else{
				ans[1]='-';
				return ans+1;
			}
		}
	}else{
		int jinWei=0,index=length1,tmp=0;
		for(int i=length2-1;i>=0;i--){
			for(int j=length1-1;j>=0;j--){
				tmp=(num1[j]-'0')*(num2[i]-'0')+jinWei;
				if(tmp<10){
					res[index]=tmp+'0';
					jinWei=0;
					index--;
				}else{
					res[index]=(tmp%10)+'0';
					jinWei=tmp/10;
					index--;
				}
			}
			
		}
	}
}
int main(){
	char num1[100001],num2[100001],ans[200005],opt='\0',tmp='\0';
	int index1=0,index2=0,flag=1;
	while(~scanf("%c",&tmp)){
		if(tmp!='\n'){
			if(tmp==' ')
				continue;
			if(tmp=='+'||tmp=='-'||tmp=='*'){
				opt=tmp;
				flag=0;
				continue;
			}
			if(flag){
				num1[index1]=tmp;
				index1++;
			}else{
				num2[index2]=tmp;
				index2++;
			}
		}else{
			num1[index1]=='\0';
			num2[index2]=='\0';
			//printf("%d\n%d\n",index1,index2);
			if(index1>=index2)
				printf("%s\n",calaulate(num1,index1,num2,index2,ans,opt,1));
			else
				printf("%s\n",calaulate(num2,index2,num1,index1,ans,opt,0));
			index1=0;
			index2=0;
			flag=1;
			continue;	
		}
	}
	return 0;
}
