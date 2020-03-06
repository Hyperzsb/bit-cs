#include <cstdio>
#include <cstring>
#include <cmath>
/**
 * @description �ж�����ʽ�Ƿ��ֵ
 * @param {int*} proposition_a - ��ʽa
 * @param {int*} proposition_b - ��ʽb
 * @return {bool} �����Ƿ��ֵ
 */
bool IsSame(int *proposition_a, int *proposition_b) {
	for (int i = 0; i < 26; i++)
		if (proposition_a[i] != proposition_b[i])
			return false;
	return true;
}
/**
 * @description �ж��¹�ʽ�Ƿ��ظ�����
 * @param {int*} proposition - �¹�ʽ
 * @param {int[][30]} disjunction_proposition - ���й�ʽ
 * @param {int} disjunction_num - ���й�ʽ����
 * @return {bool} �¹�ʽ�Ƿ��ظ�����
 */
bool IsRepeat(int *proposition, int disjunction_proposition[][30], int disjunction_num) { //ѭ�����м����Ƿ����ظ������ظ�������ֵ
	for (int i = 0; i < disjunction_num; i++) { //��ԭ�е�s1�Ƚϣ��Ƿ����ظ�
		if (IsSame(disjunction_proposition[i], proposition))
			return false;//������ͬ�򲻽������s2
		return true;//����ͬ����s2
	}
}
/**
 * @description �Թ�ʽ�������Ⲣ�ж��Ƿ������ 
 * @param {int*} proposition_a - �������⹫ʽa
 * @param {int*} proposition_b - �������⹫ʽb 
 * @param {int[][30]} disjunction_proposition - ���й�ʽ
 * @param {int} disjunction_num - ���й�ʽ����
 * @return {bool} ��ʽ�Ƿ������ 
 */
bool RES(int *proposition_a, int *proposition_b, int disjunction_proposition[][30], int disjunction_num) {
	int record1 = 0;//��¼����ı�Ԫ����
	int record2 = 0;//��¼δ����ı�Ԫ����
	int flag[30] = {0};
	for (int i = 0; i < 26; i++) { //������ĸ�����Ԫ����¼ÿ����ֵ���
		if (!proposition_a[i] && !proposition_b[i])//��Ԫ������
			continue;
		if ((proposition_a[i] == 1 && proposition_b[i] == 2) || (proposition_a[i] == 2 && proposition_b[i] == 1))//����������
			record1++;
		else
			record2++;
	}
	if (record1 != 1)return true; //�޿������������������ж�Կ�����������
	if (!record2)//ȫ�����������⣬�õ��վ��ӣ�ֱ�ӷ��ز�����ʽ
		return false;
	for (int i = 0; i < 26; i++) {
		if (proposition_a[i] + proposition_b[i] == 3 || proposition_a[i] + proposition_b[i] == 0)//��Ԫ�����ڻ��߱�Ԫ������
			flag[i] = 0;//������
		else if (proposition_a[i] == 1 || proposition_b[i] == 1) //���������������ֻ��һ������Ӧ��Ԫ�����߶��б�Ԫ���ұ�Ԫ��ͬ
			flag[i] = 1;
		else//��Ԫ��������ֵΪ��
			flag[i] = 2;
	}//��¼����Ľ��
	if (IsRepeat(flag, disjunction_proposition, disjunction_num)) {
		disjunction_num++;
		for (int i = 0; i < 26; i++)
			disjunction_proposition[disjunction_num][i] = flag[i]; //������Ľ������s�����У���ֵ��s2
	}
	return true;
}
/**
 * @description ������
 * @param {null}
 * @return {int} 
 */
int main() {
	/**
	 * ��ʼ��ʽ�ַ��� 
	 */
	char original_proposition[1000];
	scanf("%s", original_proposition);
	int original_proposition_len = strlen(original_proposition);
	/**
	* �洢����ȡʽ
	*/
	int disjunction_proposition[1000][30] = {0};
	/**
	 * ����ȡʽ�ĸ���
	 */
	int disjunction_num = 0;
	/**
	 * ����ѭ������ 
	 */ 
	for (int i = 0; i < original_proposition_len; i++)
		if (original_proposition[i] >= 'a' && original_proposition[i] <= 'z') {
			disjunction_proposition[disjunction_num][original_proposition[i] - 'a'] = 1;//��ֵ��Ϊ1
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
