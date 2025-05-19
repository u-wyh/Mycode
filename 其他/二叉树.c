#include <stdio.h>
#include <stdlib.h>

// ����������ڵ�ṹ��
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// �����µĽڵ�
TreeNode* createNode(int v) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        return NULL;
    }
    newNode->val = v;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ����������ݹ飩
void preOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    printf("%d ", head->val);
    preOrder(head->left);
    preOrder(head->right);
}

// ����������ݹ飩
void inOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    inOrder(head->left);
    printf("%d ", head->val);
    inOrder(head->right);
}

// ����������ݹ飩ע�⣺��Ĵ����� `posOrder` �����Ǹ�����ͨ�����ǳ�Ϊ `postOrder`
void postOrder(TreeNode* head) {
    if (head == NULL) {
        return;
    }
    postOrder(head->left);
    postOrder(head->right);
    printf("%d ", head->val);
}

// ������������������������
int main() {
    TreeNode* head = createNode(1);
    head->left = createNode(2);
    head->right = createNode(3);
    head->left->left = createNode(4);
    head->left->right = createNode(5);
    head->right->left = createNode(6);
    head->right->right = createNode(7);

    printf("��������ݹ��: ");
    preOrder(head);
    printf("\n");

    printf("��������ݹ��: ");
    inOrder(head);
    printf("\n");

    printf("��������ݹ��: ");
    postOrder(head);
    printf("\n");

    // ���������ڴ棨ʵ�ʴ����п�����Ҫ�������������ͷ�ÿ���ڵ���ڴ棩
    // ...

    return 0;
}
