int prime(int n){
	int sum = 0;
	int i,j,flag = 1;
	for(i = 2; i<=n; i++){
		flag = 1;
		for(j = 2; j*j <= i; j++){
			if(i%j == 0){
				flag = 0;
				break;
			}
		}
		if(flag == 1){
			sum ++;
		}
	}
	return sum;
}
int main(){
	int res = n = 0;
	if(n < 10);

return 0;
}
