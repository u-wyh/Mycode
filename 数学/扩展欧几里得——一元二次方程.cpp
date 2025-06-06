// 二元一次不定方程模版
// 给定a、b、c，求解方程ax + by = c
// 如果方程无解打印-1
// 如果方程无正整数解，但是有整数解
// 打印这些整数解中，x的最小正数值，y的最小正数值
// 如果方程有正整数解，打印正整数解的数量，同时打印所有正整数解中，
// x的最小正数值，y的最小正数值，x的最大正数值，y的最大正数值
// 1 <= a、b、c <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P5656
// 如下实现是正确的，但是洛谷平台对空间卡的很严，只有使用C++能全部通过
// java的版本就是无法完全通过的，空间会超过限制，主要是IO空间占用大
// 这是洛谷平台没有照顾各种语言的实现所导致的
// 在真正笔试、比赛时，一定是兼顾各种语言的，该实现是一定正确的
// C++版本就是Code01_DiophantineEquation2文件
// C++版本和java版本逻辑完全一样，但只有C++版本可以通过所有测试用例
//在跑完扩展欧几里得之后 我们可以得到最大公约数和一组特解
#include <iostream>
#include <cstdio>
using namespace std;

long long d, x, y, px, py;

void exgcd(long long a, long long b) {
    if (b == 0) {
        d = a;
        x = 1;
        y = 0;
    } else {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

long long a, b, c, xd, yd, times;

int main()
{
    int cases;
    scanf("%d", &cases);
    for (int t = 1; t <= cases; t++) {
        scanf("%lld %lld %lld", &a, &b, &c);
        exgcd(a, b);
        if (c % d != 0) {
            //c甚至不是gcd(a,b)的倍数 那么一定无解
            printf("-1\n");
        } else {
            x *= c / d;
            y *= c / d;
            //找到特解
            xd = b / d;
            yd = a / d;
            if (x < 0) {
                times = (xd - x) / xd;
                x += xd * times;
                y -= yd * times;
            } else {
                times = (x - 1) / xd;
                x -= xd * times;
                y += yd * times;
            }
            //x为大于0的最小正值时  y此时应当是在x>0的情况下最大的
            //因为x、y是此消彼长的关系
            if (y <= 0) {
                //说明不存在正整数解
                printf("%lld ", x);
                printf("%lld\n", y + yd * ((yd - y) / yd));
            } else {
                printf("%lld ", ((y - 1) / yd + 1));
                printf("%lld ", x);
                printf("%lld ", (y - (y - 1) / yd * yd));
                printf("%lld ", (x + (y - 1) / yd * xd));
                printf("%lld\n", y);
            }
        }
    }
    return 0;
}