//https://www.luogu.com.cn/problem/P11262
//这道题目和线段树结合  利用的是 区间和 和 区间平方和
//这道题目要求区间里面必须要一个是不一样的
//我们的整体思路是求  两个区间的 平方和 和 区间和
//区间和的差 即pos1 - pos2的值  平方和的差  即pos1*pos1 - pos2*pos2(pos1-pos2)*(pos1+pos2))
//那么可以知道pos1+pos2  从而知道pos1 pos2的对应的值
//接下来我们要做的就是判断第一个区间减去pos1  和 第二个区间减去pos2是否一样了
//我们可以使用哈希来判断  可问题是普通的哈希不行  因为类似于ad bc等数据容易造成以外判对
//所以这里使用了随机权值 来避免这个问题
//实际上这道题似乎不用使用线段树 前缀和即可维护区间和 和 平方和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int arr[MAXN];
map<int,int>h;
int sum[MAXN];

struct node{
    long long sum,squ;
}tree[MAXN<<2];

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

void up(int i){
    tree[i].sum=tree[i<<1].sum+tree[i<<1|1].sum;
    tree[i].squ=tree[i<<1].squ+tree[i<<1|1].squ;
}

void build(int l,int r,int i){
    if(l==r){
        tree[i].sum=(long long)arr[l];
        tree[i].squ=(long long)arr[l]*arr[l];
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

node query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        node ans={0,0};
        if(jobl<=mid){
            node tmp=query(jobl,jobr,l,mid,i<<1);
            ans.sum+=tmp.sum;
            ans.squ+=tmp.squ;
        }
        if(jobr>mid){
            node tmp=query(jobl,jobr,mid+1,r,i<<1|1);
            ans.sum+=tmp.sum;
            ans.squ+=tmp.squ;
        }
        return ans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        if(!h[arr[i]]){
            //表示这个数字以前没有出现
            h[arr[i]]=rand() / double(RAND_MAX)*1000000;
            //生成随机权值
        }
        sum[i]=sum[i-1]+h[arr[i]];
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int u,v,x,y;
        u=read(),v=read(),x=read(),y=read();
        node tmp1=query(u,v,1,n,1);
        node tmp2=query(x,y,1,n,1);
        //cout<<tmp1.sum<<' '<<tmp1.squ<<' '<<tmp2.sum<<' '<<tmp2.squ<<' ';
        long long v1=tmp1.sum-tmp2.sum;
        long long v2=tmp1.squ-tmp2.squ;
        if(v1==0||v2%v1){
            cout<<"NE"<<endl;
            continue;
        }
        v2/=v1;
        int a=(v1+v2)/2;
        int b=(v2-v1)/2;
        //cout<<a<<' '<<b<<endl;
        if((sum[v]-sum[u-1]-h[a])==(sum[y]-sum[x-1]-h[b])){
            cout<<"DA"<<endl;
        }
        else{
            cout<<"NE"<<endl;
        }
    }
    return 0;
}