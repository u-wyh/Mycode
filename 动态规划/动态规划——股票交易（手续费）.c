#include <stdio.h>
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize, int fee) {
    // prepare: �ڽ��״��������Ƶ�����£��۳��˹����������֮���ܻ�õ�������棨��ʼ��Ϊ���ĵ�һ��ļ۸��ȥ�����ѣ�
    int prepare = -prices[0] - fee;
    // done: �ڽ��״��������Ƶ�����£��ܻ�õ�������棨��ʼ��Ϊ0��
    int done = 0;

    for (int i = 1; i < pricesSize; i++) {
        // ����done������������Ʊ�ܻ�õ��������
        done = (done > prepare + prices[i]) ? done : prepare + prices[i];
        // ����prepare��������������ƱȻ��δ��ĳ�������ܻ�õ�������棨��Ҫ�۳������ѣ�
        prepare = (prepare > done - prices[i] - fee) ? prepare : done - prices[i] - fee;
    }

    return done;
}

int main() {
    // ʾ���÷�
    int n,fee;
    scanf("%d %d",&n,&fee);
    int prices[n];
    for(int i=0;i<n;i++)
        scanf("%d",&prices[i]);
    int result = maxProfit(prices, n, fee);
    printf("Maximum Profit: %d\n", result);
    return 0;
}
