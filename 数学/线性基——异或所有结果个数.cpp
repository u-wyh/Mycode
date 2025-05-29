// �ʵ�
// һ����n�����ݣ���ʼ���ǲ�����״̬����m������
// ÿ�������ܸı����ɵ��ݵ�״̬���ı���ָ�����䲻������������
// ����n=5��ĳ������ΪXXOOO����ʾ�������ֻ�ܸı��3�����ݵ�״̬
// ��������ʹ�ÿ��أ������ж��������Ƶ���ϣ�ȫ����Ҳ��һ�����
// �𰸿��ܴܺ󣬶� 2008 ȡģ
// 1 <= n <= 50
// 1 <= m <= 50
// �������� : https://www.luogu.com.cn/problem/P3857
// �ύ���µ�code���ύʱ��������ĳ�"Main"������ͨ�����в�������
#include<bits/stdc++.h>
using namespace std;
const int MOD = 2008;
const int MAXN = 51;

long long arr[MAXN];
long long basis[MAXN];
int n,m;
string s;

bool insert(long num) {
    for (int i = n; i >= 0; i--) {
        if (num >> i == 1) {
            if (basis[i] == 0) {
                basis[i] = num;
                return true;
            }
            num ^= basis[i];
        }
    }
    return false;
}

// ��ͨ��Ԫ
// �������Ի��Ĵ�С
int compute() {
	int size = 0;
	for (int i = 1; i <= m; i++) {
        if (insert(arr[i])) {
			size++;
		}
	}
	return size;
}

int main()
{
    cin>>n>>m;
    n--;
    for (int i = 1; i <= m; i++) {
        cin>>s;
        long num = 0;
        for (int j = 0; j <= n; j++) {
            if (s[j] == 'O') {
                num |= 1LL << j;
            }
        }
        arr[i] = num;
    }
    int size = compute();
    //ͳ�Ƴ����Ի��ĸ���
    //��Ϊ���Ի����Ԫ�ز���������Ϊ0�Ľ��   ��ôÿ������Ҫ��Ҫ��ѡ��ʽ
    //������2��size�η�
    cout<<((1LL << size) % MOD);
    return 0;
}