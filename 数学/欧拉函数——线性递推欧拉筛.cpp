#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

long long f[MAXN];
int phi[MAXN];
int prime[MAXN];
int cnt=0;
bool vis[MAXN];

void euler(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0){
                phi[i*prime[j]]=prime[j]*phi[i];
            }
            else{
                phi[i*prime[j]]=(prime[j]-1)*phi[i];
            }
        }
    }
}

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


int main()
{
    int n=1000000;
    euler(n);
    for(int i=1;i<=n;i++){
        f[i]+=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            f[j]+=(1ll*phi[i]*i)/2;
        }
    }
    int T;
    T=read();
    while(T--){
        n=read();
        printf("%lld\n",f[n]*n);
    }
    return 0;
}