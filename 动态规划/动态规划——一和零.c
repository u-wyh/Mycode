#include <stdio.h>
#include <string.h>
#define max 100
// ȫ�ֱ���
static int zeros, ones;

int main()
{
    char str[max][max][max];
    for(int )
    return 0;
}
/*// ͳ��һ���ַ�����0��1������
void zerosAndOnes(const char* str) {
    zeros = 0;
    ones = 0;
    while (*str) {
        if (*str == '0') {
            zeros++;
        } else if (*str == '1') {
            ones++;
        }
        printf("%5d %5d\n",zeros,ones);
        str++;
    }
}

// strs[i...]����ѡ��ϣ���������������z��һ������������o
// �����ѡ���ٸ��ַ���
int f1(const char* strs[], int i, int z, int o) {
    if (i == 0 && strs == NULL) {
        // û���ַ�����
        return 0;
    }
    // ��ʹ�õ�ǰ��strs[i]�ַ���
    int p1 = f1(strs, i + 1, z, o);

    // ʹ�õ�ǰ��strs[i]�ַ���
    int p2 = 0;
    zerosAndOnes(strs[i]);
    if (zeros <= z && ones <= o) {
        p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
    }
    return (p1 > p2) ? p1 : p2;
}

// �����ṩ�Ľӿڣ�ͳ�������ѡ���ٸ��ַ���
int findMaxForm(const char* strs[], int m, int n) {
    return f1(strs, 0, m, n);
}

int main() {
    // ʾ��
    const char* strs[] = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    printf("�����ѡ %d ���ַ���\n", findMaxForm(strs, m, n));
    return 0;
}*/
