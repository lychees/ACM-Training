/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/20 12:21:51
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£9\1001.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MOD = 1e9+7;
struct Matrix
{
	int mat[5][5];
	void clear()
	{
		memset(mat,0,sizeof(mat));
	}
	void output()
	{
		for(int i = 0;i < 5;i++)
		{
			for(int j = 0;j < 5;j++)
				printf("%d ",mat[i][j]);
			printf("\n");
		}
	}
	Matrix operator *(const Matrix &b)const
	{
		Matrix ret;
		for(int i = 0;i < 5;i++)
			for(int j = 0;j < 5;j++)
			{
				ret.mat[i][j] = 0;
				for(int k = 0;k < 5;k++)
				{
					long long tmp = (long long)mat[i][k]*b.mat[k][j]%MOD;
					ret.mat[i][j] = (ret.mat[i][j]+tmp);
					if(ret.mat[i][j]>MOD)
						ret.mat[i][j] -= MOD;
				}
			}
		return ret;
	}
};
Matrix pow_M(Matrix a,long long n)
{
	Matrix ret;
	ret.clear();
	for(int i = 0;i < 5;i++)
		ret.mat[i][i] = 1;
	Matrix tmp = a;
	while(n)
	{
		if(n&1)ret = ret*tmp;
		tmp = tmp*tmp;
		n>>=1;
	}
	return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    long long n;
	int A0,AX,AY;
	int B0,BX,BY;
	while(scanf("%I64d",&n) == 1)
	{
		scanf("%d%d%d",&A0,&AX,&AY);
		scanf("%d%d%d",&B0,&BX,&BY);
		if(n == 0)
		{
			printf("0\n");
			continue;
		}
		Matrix a;
		a.clear();
		a.mat[0][0] = AX%MOD;
		a.mat[0][2] = (long long)AX*BY%MOD;
		a.mat[1][1] = BX%MOD;
		a.mat[1][2] = (long long)AY*BX%MOD;
		a.mat[2][2] = (long long)AX*BX%MOD;
		a.mat[3][3] = 1;
		a.mat[4][0] = AY%MOD;
		a.mat[4][1] = BY%MOD;
		a.mat[4][2] = (long long)AY*BY%MOD;
		a.mat[4][4] = 1;
		a.mat[0][3] = a.mat[0][2];
		a.mat[1][3] = a.mat[1][2];
		a.mat[2][3] = a.mat[2][2];
		a.mat[4][3] = a.mat[4][2];
		//a.output();
		a = pow_M(a,n-1);
		//a.output();
		long long t1 = (long long)A0*B0%MOD;
		long long ans = t1*a.mat[2][3]%MOD + t1*a.mat[3][3]%MOD;
		if(ans > MOD)ans -= MOD;
		ans += (long long)A0*a.mat[0][3];
		ans %= MOD;
		ans += (long long)B0*a.mat[1][3];
		ans %= MOD;
		ans += (long long)a.mat[4][3];
		ans %= MOD;
		printf("%d\n",(int)ans);
	}
    return 0;
}
