/*
592ms 8400KB
题意:有n个数，将其分为k段，每段的值为这一段的总共数字种类，问最大总值是多少 
DP，用f[i][j]表示当前在i 分成了j份(第j份包括i) 
那枚举前边的断点k，即 
	f[i][j]=max{f[k][j-1]+val(k+1,1)}
val(a,b)表示[a,b]这段区间的价值(数字种数) 
O(n^2*k)
第二维可以滚动数组优化掉，只在最外层枚举即可 
优化求val()的过程 
val是与数的种类数有关，所以对于a[i]，在计算[1,las[a[i]]]的val[]时，a[i]不会做出贡献；
而用[las[a[i]]+1,i]计算val时，a[i]会有1的贡献 
即用f[k](k∈[1,las[a[i]]-1])时，不会有a[i]的贡献；
而用f[k](k∈[las[a[i]],i-1])更新时，a[i]会对其产生贡献(k这个点是不在后一个区间里的) 
在这段区间+1，然后查询最优值，更新f[i] 
区间加、区间查询最优值 -> 线段树 
注意1.可以从f[0]更新 
2.查询位置与第一层循环的关系 
3.开四倍空间...

基本线段树都不会写了...
*/
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
//#define gc() getchar()
#define gc() (SS==IN &&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
const int N=35005,MAXIN=5e6;

int n,k,A[N],f[N],las[N],tmp[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
struct Seg_Tree
{
	int maxv[N<<2],tag[N<<2];
	inline void PushUp(int rt)
	{
		maxv[rt]=std::max(maxv[rt<<1],maxv[rt<<1|1]);
	}
	inline void PushDown(int rt)
	{
		maxv[rt<<1]+=tag[rt], maxv[rt<<1|1]+=tag[rt];
		tag[rt<<1]+=tag[rt], tag[rt<<1|1]+=tag[rt];
		tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		tag[rt]=0;
		if(l==r) {maxv[rt]=f[l]; return;}
		int m=l+r>>1;
		Build(l,m,rt<<1), Build(m+1,r,rt<<1|1);
		PushUp(rt);
	}
	void Modify(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R)
		{
			++maxv[rt], ++tag[rt];
			return;
		}
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(l,m,rt<<1,L,R);
		if(m<R) Modify(m+1,r,rt<<1|1,L,R);
		PushUp(rt);
	}
	int Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return maxv[rt];
		if(tag[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return std::max(Query(l,m,rt<<1,L,R),Query(m+1,r,rt<<1|1,L,R));
			else return Query(l,m,rt<<1,L,R);
		else return Query(m+1,r,rt<<1|1,L,R);
	}
}t;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("D.in","r",stdin);
#endif

	n=read(),k=read();
	for(int i=1;i<=n;++i)
		A[i]=read(), las[i]=tmp[A[i]], tmp[A[i]]=i;
//	for(int i=1;i<=n;++i) printf("%d %d\n",A[i],las[i]);
	for(int i=1;i<=k;++i)
	{
		t.Build(0,n,1);
		for(int j=i;j<=n;++j)
			t.Modify(0,n,1,las[j],j-1),f[j]=t.Query(0,n,1,i-1,j-1);
	}
	printf("%d",f[n]);

	return 0;
}
