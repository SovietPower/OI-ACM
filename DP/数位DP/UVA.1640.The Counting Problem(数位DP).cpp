/*
$Description$
求$[l,r]$中$0,1,\cdots,9$每个数字出现的次数(十进制表示)。
$Solution$
对每位分别DP。注意考虑前导0: 在最后统计时，把0的答案减掉对应位的即可，在第i位的前导0会产生额外的10^{i-1}个答案。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

int Ans[10],A[10],f[10][10],pw[10];
bool vis[10][10];

int DFS(int pos,int cnt,bool lim,int K)
{
	if(!pos) return cnt;
	if(!lim && vis[pos][cnt]) return f[pos][cnt];
	int up=lim?A[pos]:9, res=0;
	for(int i=0; i<=up; ++i)
		res+=DFS(pos-1,cnt+(i==K),i==up&&lim,K);
	if(!lim) vis[pos][cnt]=1,f[pos][cnt]=res;
	return res;
}

int main()
{
	pw[0]=1;
	for(int i=1; i<=8; ++i) pw[i]=pw[i-1]*10;
	int l,r;
	while(scanf("%d%d",&l,&r),l&&r)
	{
		if(l>r) std::swap(l,r);
		for(A[0]=0; r; r/=10) A[++A[0]]=r%10;
		for(int i=0; i<=9; ++i)//每个数答案都是不同的。。别忘清空。
			memset(vis,0,sizeof vis), Ans[i]=DFS(A[0],0,1,i);
		int bit=A[0];

		for(A[0]=0,--l; l; l/=10) A[++A[0]]=l%10;
		for(int i=0; i<=9; ++i)
			memset(vis,0,sizeof vis), Ans[i]-=DFS(A[0],0,1,i);
		while(bit!=A[0]) Ans[0]-=pw[--bit];
		for(int i=0; i<9; ++i) printf("%d ",Ans[i]);
		printf("%d\n",Ans[9]);
	}
	return 0;
}
