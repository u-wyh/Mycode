// 洗牌
// 一共有n张牌，n一定是偶数，每张牌的牌面从1到n，洗牌规则如下
// 比如n = 6，牌面最初排列为1 2 3 4 5 6
// 先分成左堆1 2 3，右堆4 5 6，然后按照右堆第i张在前，左堆第i张在后的方式依次放置
// 所以洗一次后，得到 4 1 5 2 6 3
// 如果再洗一次，得到 2 4 6 1 3 5
// 如果再洗一次，得到 1 2 3 4 5 6
// 想知道n张牌洗m次的之后，第l张牌，是什么牌面
// 1 <= n <= 10^10，n为偶数
// 0 <= m <= 10^10
// 测试链接 : https://www.luogu.com.cn/problem/P2054
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这道题是真的很难想到  我们将给出的例子进行分析
//发现：1->2->4->1->2->'''     3->6->5->3->'''
//这种一开始按照规律然后突然不按照规律的  我们称之为剃刀感  往往与%运算有关
//我们可以推测 %的是n+1
//那么假设答案是x  即存在  (x*(2^m))%(n+1)==l  求解x
//也就是  x *  (2^m)  =  k  *  (n+1)  +   l
//可以变成x*a+b*y=l这种形式    (n+1)一定是奇数  所以和2^m一定互质
#include <iostream>
using namespace std;

// 扩展欧几里得算法
// 对于方程ax + by = gcd(a,b)
// 当a和b确定，那么gcd(a,b)也确定
// 扩展欧几里得算法可以给出a和b的最大公约数d、以及其中一个特解x、y
// 特别注意要保证入参a和b没有负数
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

// 原理来自，讲解033，位运算实现乘法
// a * b的过程自己实现，每一个中间过程都%mod
// 这么写目的是防止溢出，也叫龟速乘
long long multiply(long long a, long long b, long long mod) {
	// 既然是在%mod的意义下，那么a和b可以都转化成非负的
	// 本题不转化无所谓，但是其他题目可能需要转化
	// 尤其是b需要转化，否则while循环会跑不完
	a = (a % mod + mod) % mod;
	b = (b % mod + mod) % mod;
	long long ans = 0;
	while (b != 0) {
		if ((b & 1) != 0) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}

// 原理来自，讲解098，乘法快速幂
// 计算a的b次方，最终 % mod 的结果
long long power(long long a, long long b, long long mod) {
	long ans = 1;
	while (b > 0) {
		if ((b & 1) == 1) {
			ans = multiply(ans, a, mod);
		}
		a = multiply(a, a, mod);
		b >>= 1;
	}
	return ans;
}

long long compute(long long n, long long m, long long l) {
	long long mod = n + 1;
	exgcd(power(2, m, mod), mod);
	long long x0 = (x % mod + mod) % mod;
	return multiply(x0, l, mod);
}

int main()
{
    long long n,m,l;
    cin>>n>>m>>l;
    cout<<compute(n,m,l);
    return 0;
}