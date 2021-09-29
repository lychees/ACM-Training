#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
int b[3001][3001],n,m,d[3001],x[3001],len,mo=998244353,dfs[3001],low[3001],sign,pd[3001],in[3001],head,s[3001],bo[3001];
unsigned int w[3001][100];
char ch[3001];
queue<int>Q;
int quick(int k1,int k2){
	int k3=1;
	while (k2){
		if (k2&1) k3=1ll*k3*k1%mo; k1=1ll*k1*k1%mo; k2>>=1;
	}
	return k3;
}
void solve(int k){
	dfs[k]=++sign; low[k]=sign; s[++head]=k; in[k]=1; pd[k]=1;
	for (int i=1;i<=n;i++){
		if (b[k][i]==0) continue;
		if (pd[i]==0){
			solve(i); low[k]=min(low[k],low[i]);
		} else if (in[i]) low[k]=min(low[k],dfs[i]);
	}
	if (low[k]==dfs[k]){
		if (s[head]==k){
			head--; in[k]=0; return;
		}
		while (s[head+1]!=k){
			bo[s[head]]=1; in[s[head]]=0; head--;
		}
	}
}
void dfs2(int k){
	pd[k]=1; bo[k]=1;
	for (int i=1;i<=n;i++)
		if (b[i][k]&&pd[i]==0) dfs2(i);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (i!=j){
				b[i][j]=1; d[j]++;
			}
	for (int i=1;i<=n;i++){
		scanf("%s",ch+1);
		for (int j=1;j<=n;j++) if (ch[j]=='1'){
			b[i][j]--; d[j]--;
		}
	}
	for (int i=1;i<=n;i++) if (pd[i]==0) solve(i);
	memset(pd,0x00,sizeof pd);
	for (int i=1;i<=n;i++) if (pd[i]==0&&bo[i]==1) dfs2(i);
	for (int i=1;i<=n;i++) if (bo[i])
		for (int j=1;j<=n;j++) if (b[i][j]) d[j]--;
	for (int i=1;i<=n;i++) if (d[i]==0) Q.push(i);
	while (!Q.empty()){
		int k=Q.front(); Q.pop(); if (bo[k]) continue; x[++len]=k;
		for (int i=1;i<=n;i++)
			if (b[k][i]){
				d[i]--; if (d[i]==0) Q.push(i);
			}
	}
	for (int i=1;i<=n;i++){
		w[i][i-1>>5]|=(1ll<<((i-1)&31));
		for (int j=0;j<n;j++) if (b[i][j+1]) w[i][j>>5]|=(1ll<<(j&31));
	}
	int lim=(n-1>>5);
	int ans1=0,ans2=0;
	for (int i=1;i<=len;i++){
		int k=x[i];
		for (int j=1;j<=n;j++)
			if (b[k][j])
				for (int k1=0;k1<=lim;k1++) w[k][k1]|=w[j][k1];
	}
	for (int i=1;i<=len;i++){
		int k=x[i],num=0;
		for (int j=1;j<=len;j++) if (w[x[j]][k-1>>5]&(1ll<<((k-1)&31))) num++;
		ans1=(ans1+1ll*(quick(2,num)-1)*quick(2,len-num))%mo;
		ans2=(ans2+quick(2,len-num))%mo;
	}
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}

