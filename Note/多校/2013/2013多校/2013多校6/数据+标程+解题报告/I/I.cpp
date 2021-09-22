#include<cstdio>
#include<cstring>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
#define fi first
#define se second
#define mp make_pair
int na,nb,nc;
PII operator * (int a,PII b) {return mp(a*b.fi,a*b.se);}
PII operator * (PII b,int a) {return mp(a*b.fi,a*b.se);}
PII operator + (PII a,PII b) {return mp(a.fi+b.fi,a.se+b.se);}
PII operator - (PII a,PII b) {return mp(a.fi-b.fi,a.se-b.se);}
const PII Vx(1,-1),Vy(1,1),Vz(-2,0);
const PII Vu(-1,0),Vd(1,0),Vl(0,-1),Vr(0,1);
bool odd(PII x)
{
	x=x-PII(0,na-1);
	return abs(x.fi+x.se)&1;
}
ll F0[2][16666];
void clr(ll*f){memset(f,0,sizeof(ll)*16384);}
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%d%d%d",&na,&nb,&nc);
		set<PII> po;
		PII V0=PII(0,na-1)-Vz*nc,V1=PII(0,na)-Vz*nc;
		PII V2=V0+Vz,V3=V1-Vy;
		PII V4=V2+Vy,V5=V1+Vz;
		for(int i=0;i<na;i++)
			for(int j=0;j<nb;j++)
				po.insert(V0+Vx*i+Vy*j),
				po.insert(V1+Vx*i+Vy*j);
		for(int i=0;i<na;i++)
			for(int j=0;j<nc;j++)
				po.insert(V2+Vx*i+Vz*j),
				po.insert(V3+Vx*i+Vz*j);
		for(int i=0;i<nb;i++)
			for(int j=0;j<nc;j++)
				po.insert(V4+Vy*i+Vz*j),
				po.insert(V5+Vy*i+Vz*j);
		//printf("%d\n",(int)po.size());
		//for(set<PII>::iterator i=po.begin();i!=po.end();i++)
		//	printf("%d %d\n",i->fi,i->se);
		bool F=0;
		int n;scanf("%d",&n);
		set<PII> v;
		for(int i=0;i<n;i++)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			PII Va=V0+Vx*x+Vy*y+Vz*z;
			if(po.find(Va)==po.end())F=1;
			v.insert(Va);
			PII Vb=V1+Vx*x+Vy*y+Vz*z;
			if(po.find(Vb)==po.end())F=1;
			v.insert(Vb);
		}
		if(F){puts("0");continue;}
		map<PII,int> pot,d;int mz=0;
		ll*f=F0[0],*g=F0[1];clr(f);f[0]=1;
		for(set<PII>::iterator i=po.begin();i!=po.end();i++)
		{
			bool mc=v.find(*i)!=v.end();
			PII VU,VD,VM;
			if(odd(*i))VU=(*i)+Vu,VD=(*i)+Vd,VM=(*i)+Vl;
			else VU=(*i)+Vu,VD=(*i)+Vd,VM=(*i)+Vr;
			int v0=-1,v1=-1,vw=-1;bool d0=0,d1=0;d[*i]=0;
#define trf(V) \
if(po.find(V)!=po.end())\
{\
	if(pot.find(V)==pot.end())d[*i]++;else\
	{\
		d[V]--;\
		if(v0==-1)v0=pot[V],d0=!!d[V];else v1=pot[V],d1=!!d[V];\
		if(!d[V])vw=pot[V];\
	}\
}
			trf(VU);trf(VD);trf(VM);
#undef trf
			if(vw==-1)vw=mz;
			pot[*i]=vw;
			clr(g);
			if(v0==-1)
			{
				if(!mc)
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
						g[j^(1<<vw)]+=f[j];
				}else
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
						g[j]+=f[j];
				}
			}else
			if(v1==-1)
			{
				if(!mc)
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
					{
						int c0=(j>>v0)&1;
						if(c0)g[j^(1<<v0)]+=f[j];
						if(!(c0&&!d0))g[j^(1<<vw)]+=f[j];
					}
				}else
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
					{
						int c0=(j>>v0)&1;
						if(!(c0&&!d0))g[j]+=f[j];
					}
				}
			}else
			{
				if(!mc)
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
					{
						int c0=(j>>v0)&1,c1=(j>>v1)&1;
						if(c0&&!(c1&&!d1))g[j^(1<<v0)]+=f[j];
						if(c1&&!(c0&&!d0))g[j^(1<<v1)]+=f[j];
						if(!(c0&&!d0)&&!(c1&&!d1))g[j^(1<<vw)]+=f[j];
					}
				}else
				{
					for(int j=0;j<(1<<mz);j++)if(f[j])
					{
						int c0=(j>>v0)&1,c1=(j>>v1)&1;
						if(!(c0&&!d0)&&!(c1&&!d1))g[j]+=f[j];
					}
				}
			}
			swap(f,g);
			if(vw==mz)mz++;
			//printf("%d %d %d %d %d %d\n",v0,v1,d0,d1,vw,mz);
			//for(int j=0;j<(1<<mz);j++)
			//	if(f[j])printf("%d %d\n",j,f[j]);
		}
		printf("%I64d\n",f[0]);
	}
	return 0;
}