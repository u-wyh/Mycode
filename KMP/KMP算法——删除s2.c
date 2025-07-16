#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define MAX 100000+5

char s1[MAX],s2[MAX];
int stack1 [MAX];
int stack2 [MAX];
int next [MAX];

// ????next????
void nextArray() {
    int m=strlen(s2);
    if (m == 1) {
        next[0] = -1;
    }
    else{
        next[0] = -1;
        next[1] = 0;

        int i = 2, cn = 0;
        while (i < m) {
            if (s2[i - 1] == s2[cn]) {
                next[i++] = ++cn;
            } else if (cn > 0) {
                cn = next[cn];
            } else {
                next[i++] = 0;
            }
        }
    }
}

void compute() {
    int size = 0;
    int n = strlen(s1), m = strlen(s2), x = 0, y = 0;
    nextArray();
    while (x < n) {
        if (s1[x] == s2[y]) {
            stack1[size] = x;
            stack2[size] = y;
            size++;
            x++;
            y++;
        } else if (y == 0) {
            stack1[size] = x;
            stack2[size] = -1;
            size++;
            x++;
        } else {
            y = next[y];
        }
        if (y == m) {
            // ?????????????m?????
            size -= m;
            y = size > 0 ? (stack2[size - 1] + 1) : 0;
        }
    }
    for(int i=0;i<size;i++){
        printf("%c",s1[stack1[i]]);
    }
}


// ???????????????
int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    compute();
    return 0;
}