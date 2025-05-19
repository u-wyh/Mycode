/*
// ������Ʊ
// ������һ����m����Ŀ�������ĵ�i����Ŀ����������������
// game[i] = { Ki, Bi }��Ki��Biһ��������
// Ki�����ۿ�ϵ����Bi����Ʊ��
// �ٸ����� : Ki = 2, Bi = 10
// ���ֻ��1������Ʊ��������Ʊ�ļ۸�Ϊ : Bi - Ki * 1 = 8
// ������1�����������ĿҪ��8Ԫ
// �����2������Ʊ��������Ʊ�ļ۸�Ϊ : Bi - Ki * 2 = 6
// ������2�����������ĿҪ��6 * 2 = 12Ԫ
// �����5������Ʊ��������Ʊ�ļ۸�Ϊ : Bi - Ki * 5 = 0
// ������5�����������ĿҪ��5 * 0 = 0Ԫ
// ����и�������Ʊ������Ϊ��0Ԫ(��Ϊ����Ŀ����Ǯʵ����̫�ٵ���)
// ���ǿ�����Ϊ�������x������Ʊ��������Ʊ�ļ۸�Ϊ : Bi - Ki * x
// x�������������Ŀ���ܻ����� : max { x * (Bi - Ki * x), 0 }
// ��λһ����n���ˣ�ÿ����������ѡ1����Ŀ�����棬Ҳ���Բ�ѡ�κ���Ŀ
// ����Ա�����������ύѡ��Ȼ������ȥ��������Ĺ���ͳһ��Ǯ��Ʊ
// ����֪���Լ���Ҫ׼������Ǯ���Ϳ���Ӧ�����п��ܵ���������������յ�Ǯ��
// ���������� :
// 1 <= M��N��Ki��Bi <= 10^5
// ������ʵ�󳧱��ԣ�û�����߲��ԣ���������֤
*/







//����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int ki;
    int bi;
    int people;
    // ��������һ����׬����Ǯ�ĺ���
    int (*earn)(struct Game*);
} Game;

// ����Game�ṹ��������һ����׬����Ǯ
int game_earn(Game *g) {
    return g->bi - (g->people + 1) * g->ki - g->people * g->ki;
}

// ��ʼ��Game�ṹ��
Game* create_game(int k, int b) {
    Game *g = malloc(sizeof(Game));
    g->ki = k;
    g->bi = b;
    g->people = 0;
    g->earn = game_earn;
    return g;
}

// �Ƚ�����Game�ṹ�壨���ڶѣ�
int compare_games(const void *a, const void *b) {
    Game *ga = *(Game**)a;
    Game *gb = *(Game**)b;
    return (ga->earn(ga) - gb->earn(gb));
}

// ����������δʵ�֣���Ϊʱ�临�Ӷȹ��ߣ�

// ��ʽ����
int enough2(int n, int games[][2], int m) {
    Game **heap = malloc(m * sizeof(Game*));
    for (int i = 0; i < m; i++) {
        heap[i] = create_game(games[i][0], games[i][1]);
    }

    // ʹ��qsort��ʼ���ѣ���ΪC��׼��û��ֱ�ӵĴ����ʵ�֣�
    qsort(heap, m, sizeof(Game*), compare_games);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        Game *cur = heap[0];
        if (cur->earn(cur) <= 0) break;

        ans += cur->earn(cur);
        cur->people++;

        // ���������
        qsort(heap, m, sizeof(Game*), compare_games);
    }

    // �ͷ��ڴ�
    for (int i = 0; i < m; i++) {
        free(heap[i]);
    }
    free(heap);

    return ans;
}

// �������������������Ϸ����
int** randomGames(int *m, int v) {
    *m = rand() % 20 + 1; // �������20����Ϸ
    int **games = malloc(*m * sizeof(int*));
    for (int i = 0; i < *m; i++) {
        games[i] = malloc(2 * sizeof(int));
        games[i][0] = rand() % v + 1;
        games[i][1] = rand() % v + 1;
    }
    return games;
}

// �����������ڲ���
int main() {
    srand(time(NULL)); // ��ʼ�������������

    int N = 8, M = 8, V = 20, testTimes = 2000;
    printf("���Կ�ʼ\n");

    for (int i = 0; i < testTimes; i++) {
        int n = rand() % N + 1;
        int m;
        int **games = randomGames(&m, V);

        int ans1 = 0; // ���������Ľ����δʵ�֣�
        int ans2 = enough2(n, games, m);


    }

    printf("���Խ���\n");
    return 0;
}
