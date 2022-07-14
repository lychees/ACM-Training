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
void setResult(double score) // ���������
{
    printf("%0.1lf\n", score); // �������
    exit(0); // �����������У����򷵻�ֵӦΪ0
}
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
 	const char *inputFileName = argv[1];// �����ļ�
    const char *outputFileName = argv[2];// �������ߵ�����ļ�
    const char *standardFileName = argv[3];// �����˵Ĳο����
    const char *logFileName = argv[4];// ������
    freopen(logFileName, "w", stdout); // ֱ�Ӵ򿪽���ļ���ʹ�ñ�׼���
	
    fout = fopen(outputFileName, "r"); // �򿪱������ߵ����
    if (!fout)
        setResult(0.0);
    fin=fopen(inputFileName,"r");
    
	if (Judge())//Judge����Ϊ��
		setResult(5.0);
	else
		setResult(0.0);
	fclose(fscore);//�رյ÷��ļ�
	fclose(freport);//�رձ����ļ�
	return 0;
}
