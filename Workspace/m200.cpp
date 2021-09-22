#include<bits/stdc++.h>
using namespace std;
int m,n,k;
int w[61][3],v[61][3];
int f[32001];
int num,ans;
int main()
{


#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    //freopen("/Users/minakokojima/Documents/GitHub/ACM-Training/Workspace/out.txt", "w", stdout);
#endif
     scanf("%d%d",&m,&n);
  for (int i=1;i<=n;i++)
  { int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    if (!z) {w[i][0]=x*y;v[i][0]=x;}
    else { if (!w[z][1]) {w[z][1]=x*y;v[z][1]=x;}
	       else {w[z][2]=x*y;v[z][2]=x;}
		 }
  }
  for (int i=1;i<=n;i++)
  { for (int j=m;j>=v[i][0];j--)
    { f[j]=max(f[j],f[j-v[i][0]]+w[i][0]);//第一种情况，只要主件
      if (v[i][0]+v[i][1]+v[i][2]<=j) f[j]=max(f[j],f[j-v[i][1]-v[i][2]-v[i][0]]+w[i][1]+w[i][2]+w[i][0]);//第二种情况，要主件，也要两个附件
      if (v[i][0]+v[i][1]<=j) f[j]=max(f[j],f[j-v[i][1]-v[i][0]]+w[i][1]+w[i][0]);//第三种情况，要第一个附件
      if (v[i][0]+v[i][2]<=j) f[j]=max(f[j],f[j-v[i][2]-v[i][0]]+w[i][2]+w[i][0]);//第四种情况，要第二个附件
	}
  }
  printf("%d",f[m]);
  return 0;
}
