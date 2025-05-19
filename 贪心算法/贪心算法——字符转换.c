#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool canConvert(const char *str1, const char *str2) {
    if (strcmp(str1, str2) == 0) {
        return true;
    }

    int map[26] = {0}; // ��ʼ��map����Ϊ0
    int kinds = 0;
    for (int i = 0; str2[i] != '\0'; i++) {
        int index = str2[i] - 'a';
        if (map[index] == 0) {
            kinds++;
        }
        map[index]++;
    }
    if (kinds == 26) {
        return false;
    }

    // ���³�ʼ��map����Ϊ-1������ʹ��memset������
    memset(map, -1, sizeof(map));

    // map[x] = y ��ʾstr1�е��ַ�x�ϴγ�����str1�е�yλ��
    for (int i = 0, cur; str1[i] != '\0'; i++) {
        cur = str1[i] - 'a';
        if (map[cur] != -1 && str2[map[cur]] != str2[i]) {
            return false;
        }
        map[cur] = i;
    }

    return true;
}

int main() {
    // ʾ���÷�
    const char *str1 ;
    const char *str2 ;
    scanf("%s",str1);
    scanf("%s",str2);
    if (canConvert(str1, str2)) {
        printf("����ת��\n");
    } else {
        printf("������ת��\n");
    }

    return 0;
}
