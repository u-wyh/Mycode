#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// ����1: �����ݹ�
int same(TreeNode *a, TreeNode *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}

int isSubtree(TreeNode *t1, TreeNode *t2) {
    if (t1 == NULL) return t2 == NULL;
    return same(t1, t2) || isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
}

// ����2: �������������л� + KMP�㷨ƥ��
// ע�⣺����Ϊ�˼򻯣�����ֱ��ʹ���ַ���������ģ��ArrayList<String>
#define MAX_NODES 1000
char *serialized[MAX_NODES];
int serial_index = 0;

void serial(TreeNode *head, char ***path) {
    if (head == NULL) {
        serialized[serial_index++] = strdup("null");
    } else {
        char val_str[12]; // ��������ֵ���ᳬ��10λ
        sprintf(val_str, "%d", head->val);
        serialized[serial_index++] = strdup(val_str);
        serial(head->left, path);
        serial(head->right, path);
    }
}

// KMP�㷨��غ������򻯰棩
// ... ����ʡ��KMP�㷨��ʵ�֣���Ϊ����Ը�������Ҫ����ռ�

// ע�⣺����KMP�㷨ʵ�ֽ�Ϊ���ӣ����ﲻչ����������Ҫ�Լ�ʵ����
// ��������Կ���ʹ�������ַ���ƥ���㷨�������ص��ַ���ƥ��

// ʾ�������������ڲ���
int main() {
    // ������Ҫ����һЩTreeNodeʵ������������Ȼ�����isSubtree
    // ����ƪ�����ƣ����ﲻչ�����������������

    // ����t1��t2���Ѿ������õ���
    // TreeNode *t1 = ...;
    // TreeNode *t2 = ...;

    // ���Է���1
    printf("Method 1: %s\n", isSubtree(t1, t2) ? "true" : "false");

    // ע�⣺���ڷ���2��KMP�㷨δʵ�֣����ﲻ���Է���2

    return 0;
}
