/*
$Description$
给定n个区间，要求将每个区间染成0(red)/1(blue)两种颜色，使得任何一个点被两种颜色覆盖次数差的绝对值<=1.输出方案。
$Solution$
参照上题 再画一下图，可以发现 对于一条线段[l,r]，由l向r+1连边，若有线段能使r+1回到l，则这一段蓝红色覆盖数相同 
(端点是会被覆盖的，比如线段[1,3]和[3,5]，3被覆盖两次，所以将r+1)
但是会存在一些奇度数的点，没有欧拉回路 
对于这些点，如果走完它的欧拉路径，那么颜色覆盖数不相同的情况一定是出现在起点和终点之间的 
如果从一个奇度数点走到另一个奇度数的点，若这条线段跨越了多个奇度数点，则这段区间可能会多次含有某种颜色 
这时我们可以把奇数点两两配对 再染色，这样不同颜色一定是出现在配对后产生的起点和终点之间且只多一次，原因: 
若相邻奇点在同一连通块，那么它们配对后会形成一个大连通块，要么现在连通块本身已经是个环了，只有它们之间多一次颜色；
要么现在连通块还是有两个奇点构成起点终点，但起点终点一定是在这两个配对点之后了，所以不会影响这两个配对点之间多的一次颜色。
若相邻奇点不在同一连通块中， 


*/
#include <cstdio>
#include <cctype>
#define gc() getchar()
const int N=



inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	
	
	
	
	
	
	
	
	

	return 0;
}
