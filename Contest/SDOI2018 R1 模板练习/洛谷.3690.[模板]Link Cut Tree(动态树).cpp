#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace LCT
{
	#define lson son[x][0]
	#define rson son[x][1]

	int fa[N],son[N][2],sum[N],val[N],sk[N];
	bool rev[N];
	inline void Update(int x){
		sum[x]=sum[lson]^sum[rson]^val[x];
	}
	inline bool n_root(int x){
		return son[fa[x]][0]==x||son[fa[x]][1]==x;
	}
	inline void Rev(int x){
		std::swap(lson,rson), rev[x]^=1;
	}
	inline void PushDown(int x){
		if(rev[x]) Rev(lson),Rev(rson),rev[x]=0;
	}
	void Rotate(int x)
	{
		int a=fa[x],b=fa[a],l=son[a][1]==x,r=l^1;
		if(n_root(a)) son[b][son[b][1]==a]=x;
		if(son[x][r]) fa[son[x][r]]=a;
		fa[a]=x, fa[x]=b, son[a][l]=son[x][r], son[x][r]=a;
		Update(a);
	}
	void Splay(int x)
	{
		int t=1,a=x; sk[1]=x;
		while(n_root(a)) sk[++t]=a=fa[a];
		while(t) PushDown(sk[t--]);
		while(n_root(x))
		{
			if(n_root(a=fa[x])) Rotate(son[a][1]==x^son[fa[a]][1]==a?x:a);
			Rotate(x);
		}
		Update(x);
	}
	void Access(int x){
		for(int pre=0; x; x=fa[pre=x])
			Splay(x), rson=pre, Update(x);
	}
	void Make_root(int x){
		Access(x), Splay(x), Rev(x);
	}
	void Split(int x,int y){
		Make_root(x), Access(y), Splay(y);
	}
	int Find_root(int x)
	{
		Access(x), Splay(x);
		while(lson) x=lson;
		return x;
	}
	void Link(int x,int y)
	{
		Make_root(x);
		if(Find_root(y)!=x) fa[x]=y;
	}
	void Cut(int x,int y)
	{
		Make_root(x);
		if(Find_root(y)==x&&fa[x]==y&&!rson)
			fa[x]=son[y][0]=0, Update(y);
	}
}
using namespace LCT;

int main()
{
	int n=read(),m=read(),opt,x,y;
	for(int i=1; i<=n; ++i) val[i]=read();
	while(m--)
		switch(opt=read(),x=read(),y=read(),opt)
		{
			case 0: Split(x,y),printf("%d\n",sum[y]); break;
			case 1: Link(x,y); break;
			case 2: Cut(x,y); break;
			case 3: Splay(x), val[x]=y; break;
		}
	return 0;
}
