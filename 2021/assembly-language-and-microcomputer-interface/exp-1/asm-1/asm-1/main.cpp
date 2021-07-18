#include <stdio.h>
int main() {
	int target = 0, a = 0, b = 0, c = 0, d = 0;
	scanf_s("%d", &target);

	for (a = 0; a*a <= target; a++)
		for (b = a; b*b <= target; b++)
			for (c = b; c*c <= target; c++)
				for (d = c; d*d <= target; d++)
					if (target == a * a + b * b + c * c + d * d) {
						printf("%d = %d^2 + %d^2 + %d^2 + %d^2\n", target, a, b, c, d);
						return 0;
					}
	return 0;
}