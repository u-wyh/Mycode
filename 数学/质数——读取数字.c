#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

// f1 ������C���԰汾��ֱ�Ӷ�ȡlong long����
void f1() {
    printf("f1�������Զ���\n");
    long long num;
    // ʹ��scanfֱ�Ӷ�ȡlong long���ͣ�%lld��long long��ռλ��
    scanf("%lld", &num);
    printf("%lld\n", num);
}

// f2 ������C�����в���Ҫ�ر���ַ�����long long��ת������Ϊ���ǿ���ֱ�Ӷ�ȡ
void f2() {
    char str[100]; // ��������������ַ���������99���ַ�����һ��'\0'
    long num;
    char *endptr;

    printf("f2�������Զ���: ");
    // ʹ��fgets������gets�Ա��������gets�ѱ����ã�
    // ע�⣺fgets�ᱣ�����з�������ַ�������С�ڻ�������С
    if (fgets(str, sizeof(str), stdin) == NULL) {
        perror("fgets failed");
        return;
    }

    // �Ƴ����ܵĻ��з�
    str[strcspn(str, "\n")] = 0;

    // ʹ��strtol���ַ���ת��Ϊlong
    errno = 0; // ���errno����Ϊstrtol���ڳ���ʱ������
    num = strtol(str, &endptr, 10);

    // ���strtol�ķ���ֵ�Ƿ���Ϊ�����ʧ��
    if ((errno == ERANGE && (num == LONG_MAX || num == LONG_MIN))
            || (endptr == str)) {
        printf("ת��ʧ��: ��������������\n");
        return;
    }
}

int main() {
    f1();

    f2();
    return 0;
}
