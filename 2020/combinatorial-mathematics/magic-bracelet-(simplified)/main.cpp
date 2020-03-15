#include <cstdio>
#include <cmath>

int euler[100000] = {0};

struct Map {
    int matrix[15][15];

    Map() {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++)
                matrix[i][j] = 1;
    }
};

Map MatrixMultiply(Map x, Map y, int jie_shu, int mod) {
    Map tmp;
    for (int i = 1; i <= jie_shu; i++) {
        for (int j = 1; j <= jie_shu; j++) {
            tmp.matrix[i][j] = 0;
            for (int k = 1; k <= jie_shu; k++) {
                if (mod != 0)
                    tmp.matrix[i][j] += (x.matrix[i][k] * y.matrix[k][j]) % mod;
                else
                    tmp.matrix[i][j] += x.matrix[i][k] * y.matrix[k][j];
            }
            if (mod != 0)
                tmp.matrix[i][j] = tmp.matrix[i][j] % mod;
        }
    }
    return tmp;
}


Map MatrixPower(Map x, Map y, int pow, int jie_shu, int mod) {
    while (pow) {
        if (pow & 1) {
            y = MatrixMultiply(y, x, jie_shu, mod);
        }
        x = MatrixMultiply(x, x, jie_shu, mod);
        pow = pow >> 1;
    }
    return y;
}

int MatrixTrace(Map map, int jie_shu, int mod) {
    int trace = 0;
    for (int i = 1; i <= jie_shu; i++)
        if (mod != 0)
            trace = (trace + map.matrix[i][i]) % mod;
        else
            trace = trace + map.matrix[i][i];
    return trace;
}

bool IsPrime(int num) {
    int max = (int) sqrt(num);
    for (int i = 2; i <= max; i++)
        if (num % i == 0)
            return false;
    return true;
}

int Euler(int num, int *euler_list, int euler_list_length) {
    if (num < euler_list_length && euler_list[num] != 0) {
        return euler_list[num];
    } else {
        int res = num, tmp = num;
        for (int i = 2; i <= tmp; i++)
            if (tmp % i == 0 && IsPrime(i)) {
                res = res - res / i;
                while (tmp % i == 0)
                    tmp /= i;
            }
        if (num < euler_list_length)
            euler_list[num] = res;
        return res;
    }
}

int main() {
    int zu_shu = 0;
    scanf("%d", &zu_shu);
    while (zu_shu--) {
        Map map;
        int bracelet_length = 0, beads_kind = 0, conflict_num = 0, sum = 0;
        scanf("%d%d%d", &bracelet_length, &beads_kind, &conflict_num);
        for (int i = 0; i < conflict_num; i++) {
            int bead_a = 0, bead_b = 0;
            scanf("%d%d", &bead_a, &bead_b);
            map.matrix[bead_a][bead_b] = 0;
            map.matrix[bead_b][bead_a] = 0;
        }
        int pow = 1;
        Map tmp_map = map;
        for (int i = 1; i <= bracelet_length; i++)
            if (bracelet_length % i == 0) {
                if (i == pow) { ;
                } else if (i - pow == 1) {
                    tmp_map = MatrixMultiply(tmp_map, map, beads_kind, 0);
                    pow = i;
                } else {
                    tmp_map = MatrixMultiply(tmp_map,
                                             MatrixPower(map, map, i - pow - 1, beads_kind, 0),
                                             beads_kind, 0);
                    pow = i;
                }
                int euler_num = Euler(bracelet_length / i, euler, 100000);
                int trace_num = MatrixTrace(tmp_map, beads_kind, 0);
                sum = sum + euler_num * trace_num;
            }
        sum /= bracelet_length;
        printf("%d\n", sum % 9973);
    }
    return 0;
}