#include <cstdio>
#include <cstring>
#include <cmath>
/**
 * @description 判断两公式是否等值
 * @param {int*} proposition_a - 公式a
 * @param {int*} proposition_b - 公式b
 * @return {bool} 两市是否等值
 */
bool IsSame(int *proposition_a, int *proposition_b) {
	for (int i = 0; i < 26; i++)
		if (proposition_a[i] != proposition_b[i])
			return false;
	return true;
}
/**
 * @description 判断新公式是否重复出现
 * @param {int*} proposition - 新公式
 * @param {int[][30]} disjunction_proposition - 所有公式
 * @param {int} disjunction_num - 所有公式个数
 * @return {bool} 新公式是否重复出现
 */
bool IsRepeat(int *proposition, int disjunction_proposition[][30], int disjunction_num) { //循环进行检验是否有重复，无重复返回正值
	for (int i = 0; i < disjunction_num; i++) { //与原有的s1比较，是否有重复
		if (IsSame(disjunction_proposition[i], proposition))
			return false;//如有相同则不将其加入s2
		return true;//无相同加入s2
	}
}
/**
 * @description 对公式进行消解并判断是否可满足 
 * @param {int*} proposition_a - 参与消解公式a
 * @param {int*} proposition_b - 参与消解公式b 
 * @param {int[][30]} disjunction_proposition - 所有公式
 * @param {int} disjunction_num - 所有公式个数
 * @return {bool} 公式是否可满足 
 */
bool RES(int *proposition_a, int *proposition_b, int disjunction_proposition[][30], int disjunction_num) {
	int record1 = 0;//记录消解的变元个数
	int record2 = 0;//记录未消解的变元个数
	int flag[30] = {0};
	for (int i = 0; i < 26; i++) { //利用字母代表变元，记录每个真值情况
		if (!proposition_a[i] && !proposition_b[i])//变元不存在
			continue;
		if ((proposition_a[i] == 1 && proposition_b[i] == 2) || (proposition_a[i] == 2 && proposition_b[i] == 1))//可消解的情况
			record1++;
		else
			record2++;
	}
	if (record1 != 1)return true; //无可以消解的情况，或者有多对可以消解的情况
	if (!record2)//全部都可以消解，得到空句子，直接返回不满足式
		return false;
	for (int i = 0; i < 26; i++) {
		if (proposition_a[i] + proposition_b[i] == 3 || proposition_a[i] + proposition_b[i] == 0)//变元不存在或者变元可消解
			flag[i] = 0;//可消解
		else if (proposition_a[i] == 1 || proposition_b[i] == 1) //有两种情况，两边只有一边有相应变元，两边都有变元，且变元相同
			flag[i] = 1;
		else//变元存在且真值为负
			flag[i] = 2;
	}//记录消解的结果
	if (IsRepeat(flag, disjunction_proposition, disjunction_num)) {
		disjunction_num++;
		for (int i = 0; i < 26; i++)
			disjunction_proposition[disjunction_num][i] = flag[i]; //将消解的结果存入s数组中，赋值给s2
	}
	return true;
}
/**
 * @description 主函数
 * @param {null}
 * @return {int} 
 */
int main() {
	/**
	 * 初始公式字符串 
	 */
	char original_proposition[1000];
	scanf("%s", original_proposition);
	int original_proposition_len = strlen(original_proposition);
	/**
	* 存储简单析取式
	*/
	int disjunction_proposition[1000][30] = {0};
	/**
	 * 简单析取式的个数
	 */
	int disjunction_num = 0;
	/**
	 * 进行循环消解 
	 */ 
	for (int i = 0; i < original_proposition_len; i++)
		if (original_proposition[i] >= 'a' && original_proposition[i] <= 'z') {
			disjunction_proposition[disjunction_num][original_proposition[i] - 'a'] = 1;//正值记为1
		} else if (original_proposition[i] == '&') {
			disjunction_num++;
		} else if (original_proposition[i] == '!') {
			disjunction_proposition[disjunction_num][original_proposition[++i] - 'a'] = 2;
		}
	int num0 = -1, num1 = disjunction_num;
	do {
		for (int i = 0; i <= num0; i++)
			for (int j = num0 + 1; j <= num1; j++)
				if (!RES(disjunction_proposition[i], disjunction_proposition[j], disjunction_proposition, disjunction_num)) {
					printf("NO\n");
					return 0;
				}
		for (int i = num0 + 1; i <= num1; i++)
			for (int j = i + 1; j <= num1; j++)
				if (!RES(disjunction_proposition[i], disjunction_proposition[j], disjunction_proposition, disjunction_num)) {
					printf("NO\n");
					return 0;
				}
	} while (disjunction_num > num1);
	printf("YES\n");
	return 0;
}
