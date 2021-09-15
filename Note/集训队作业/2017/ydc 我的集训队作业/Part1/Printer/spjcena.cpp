#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#define maxn 100010
FILE *fscore,*freport,*fstd,*fin,*fout;
using namespace std;
typedef long long LL;
struct Task
{
	int t,s,id,p;
	Task() {}
	friend bool operator < (const Task &a,const Task &b)
	{
		return a.p<b.p;
	}
}task[maxn];
bool cmp(const Task &a,const Task &b)
{
	return a.t<b.t;
}
LL T,ans[maxn];
int n,x;
bool check()
{
	sort(task+1,task+n+1,cmp);
	priority_queue<Task> Q;
	LL now=0;
	for(int i=1,j=1;i<=n;i=j)
	{
		LL last=now;
		now=task[i].t;
		while(!Q.empty()&&Q.top().s+last<=now)
			last+=Q.top().s,ans[Q.top().id]=last,Q.pop();
		if(!Q.empty())
		{
			Task a=Q.top();
			a.s-=now-last;
			Q.pop(),Q.push(a);
		}
		for(;task[j].t==task[i].t;++j)
			Q.push(task[j]);
	}
	while(!Q.empty())
	{
		Task a=Q.top();
		now+=Q.top().s,ans[Q.top().id]=now,Q.pop();
	}
	LL T;
	fscanf(fin,"%I64d",&T);
	if(ans[x]!=T)
		return false;
	for(int i=1;i<=n;++i)
	{
		if(fscanf(fout,"%I64d",&T)!=1)
			return false;
		if(T!=ans[i])
			return false;
	}
	return true;
}
bool Judge()
{
	int tmp;
	fscanf(fout,"%d",&tmp);
	if(tmp<1||tmp>1000000000)
		return false; 
	fscanf(fin,"%d",&n);
	for(int i=1;i<=n;++i)
	{
		fscanf(fin,"%d %d %d",&task[i].t,&task[i].s,&task[i].p);
		if(task[i].p<0)
			task[i].p=tmp,x=i;
		else if(task[i].p==tmp)
			return false;
		task[i].id=i;
	}
	return check();
}

int main(int argc,char *argv[])
{
	fscore=fopen("score.log","w");//打开得分文件
	freport=fopen("report.log","w");//打开报告文件
	fstd=fopen(argv[2],"r");//打开测试点标准输出文件
	int score=atoi(argv[1]);//取得测试点的分数
	
	fin=fopen("input.txt","r");//打开测试点标准输入文件
	fout=fopen("output.txt","r");//打开用户的数据输出文件
	
	if (!fout)
	{
		fprintf(fscore,"%d",0);//返回0分
		fprintf(freport,"no output");//报告Judge结果为no output
	}
	else if (Judge())//Judge后结果为真
	{
		fprintf(fscore,"%d",score);//返回满分
		fprintf(freport,"right");//报告Judge结果为right
	}
	else
	{
		fprintf(fscore,"%d",0);//返回0分
		fprintf(freport,"wrong");//报告Judge结果为wrong
	}
	fclose(fscore);//关闭得分文件
	fclose(freport);//关闭报告文件
	return 0;
}
