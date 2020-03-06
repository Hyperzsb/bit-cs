#include<iostream>
#include<stdio.h>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
	int zuShu=0;
	scanf("%d",&zuShu);
	for(int i=0;i<zuShu;i++){
		long long int num=0;
		scanf("%lld",&num);
		double res=log(num)/log(2);
		int res1=int(res);
		if(res>res1)
			printf("%d\n",res1+1);
		else
			printf("%d\n",res1);
		//cout << setiosflags(ios::fixed) << setprecision(0) << res << endl;
	}
	return 0;
}
