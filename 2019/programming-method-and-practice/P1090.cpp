#include<stdio.h>
#include<malloc.h>
#include<algorithm>
int main(){
	int zhongLei=0;
	long long int ans=0;
	int *appleList=(int*)malloc(10001*sizeof(int));
	scanf("%d",&zhongLei);
	for(int i=0;i<zhongLei;i++)
		scanf("%d",&appleList[i]);
	std::sort(appleList,appleList+10001);
	for(int i=10001-zhongLei;i<10000;i++){
		if(appleList[i]>appleList[i+1])
			std::sort(appleList+i,appleList+10001);
		appleList[i+1]+=appleList[i];
		ans+=appleList[i+1];
	}
	printf("%lld",ans);
	
	return 0;
}
