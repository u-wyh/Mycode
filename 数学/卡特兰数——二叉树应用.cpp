// 叶子节点数的期望
// 一共有n个节点，认为节点之间无差别，能形成很多不同结构的二叉树
// 假设所有不同结构的二叉树，等概率出现一棵，返回叶子节点的期望
// 1 <= n <= 10^9
// 答案误差小于10的-9次方
// 测试链接 : https://www.luogu.com.cn/problem/P3978
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

int main()
{
    double n;
    cin>>n;
    printf("%.9lf",n*(n+1)/(2*(2*n-1)));
    return 0;
}