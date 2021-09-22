/*
 *  Author:kuangbin
 *  1002.cpp
 */

#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <math.h>
using namespace std;
/*
 * 后缀数组
 * DC3算法，复杂度O(n)
 * 所有的相关数组都要开三倍
 */
const int MAXN = 2010;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[MAXN*3],wb[MAXN*3],wv[MAXN*3],wss[MAXN*3];
int c0(int *r,int a,int b)
{
	return r[a] == r[b] && r[a+1] == r[b+1] && r[a+2] == r[b+2];
}
int c12(int k,int *r,int a,int b)
{
	if(k == 2)
		return r[a] < r[b] || ( r[a] == r[b] && c12(1,r,a+1,b+1) );
	else return r[a] < r[b] || ( r[a] == r[b] && wv[a+1] < wv[b+1] );
}
void sort(int *r,int *a,int *b,int n,int m)
{
	int i;
	for(i = 0;i < n;i++)wv[i] = r[a[i]];
	for(i = 0;i < m;i++)wss[i] = 0;
	for(i = 0;i < n;i++)wss[wv[i]]++;
	for(i = 1;i < m;i++)wss[i] += wss[i-1];
	for(i = n-1;i >= 0;i--)
		b[--wss[wv[i]]] = a[i];
}
void dc3(int *r,int *sa,int n,int m)
{
	int i, j, *rn = r + n;
	int *san = sa + n, ta = 0, tb = (n+1)/3, tbc = 0, p;
	r[n] = r[n+1] = 0;
	for(i = 0;i < n;i++)if(i %3 != 0)wa[tbc++] = i;
	sort(r + 2, wa, wb, tbc, m);
	sort(r + 1, wb, wa, tbc, m);
	sort(r, wa, wb, tbc, m);
	for(p = 1, rn[F(wb[0])] = 0, i = 1;i < tbc;i++)
		rn[F(wb[i])] = c0(r, wb[i-1], wb[i]) ? p - 1 : p++;
	if(p < tbc)dc3(rn,san,tbc,p);
	else for(i = 0;i < tbc;i++)san[rn[i]] = i;
	for(i = 0;i < tbc;i++) if(san[i] < tb)wb[ta++] = san[i] * 3;
	if(n % 3 == 1)wb[ta++] = n - 1;
	sort(r, wb, wa, ta, m);
	for(i = 0;i < tbc;i++)wv[wb[i] = G(san[i])] = i;
	for(i = 0, j = 0, p = 0;i < ta && j < tbc;p++)
		sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
	for(;i < ta;p++)sa[p] = wa[i++];
	for(;j < tbc;p++)sa[p] = wb[j++];
}
//str和da也要三倍
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
	for(int i = n;i < n*3;i++)
		str[i] = 0;
	dc3(str, sa, n+1, m);
	int i,j,k = 0;
	for(i = 0;i < n;i++)rank[sa[i]] = i;
	for(i = 0;i <= n;i++)rank[sa[i]] = i;
	for(i = 0;i < n; i++)
	{
		if(k) k--;
		j = sa[rank[i]-1];
		while(str[i+k] == str[j+k]) k++;
		height[rank[i]] = k;
	}
}

char str[MAXN];
int r[3*MAXN];
int sa[3*MAXN];
int rank[MAXN];
int height[MAXN];

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    int m,L,R;
    while(T--)
    {
        scanf("%s",str);
        int len = strlen(str);
        for(int i = 0;i < len;i++)
            str[i] = str[i]-'a'+1;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d",&L,&R);
            int n = R-L+1;
            for(int i = 0;i < n;i++)
                r[i] = str[L+i-1];
            r[n] = 0;
            da(r,sa,rank,height,n,30);
            int ans=n*(n+1)/2;
            for(int i=2;i<=n;i++)ans-=height[i];
            printf("%d\n",ans);
        }
    }
    return 0;
}

