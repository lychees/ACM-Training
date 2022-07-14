#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
FILE *fscore,*freport,*fstd,*fin,*fout;
using namespace std;
bool Judge()
{
	double vu,vs;
	int T;
    fscanf(fin,"%d",&T);
    for(int i=1,x,y;i<=T;++i)
    {
		fscanf(fout,"Case #%d: %lf",&x,&vu);
		fscanf(fstd,"Case #%d: %lf",&y,&vs);
		if(x!=y||abs(vu-vs)>1e-10)
			return false;
	}
	return true;
}

int main(int argc,char *argv[])
{
	fscore=fopen("score.log","w");//打开得分文件
	freport=fopen("report.log","w");//打开报告文件
	fstd=fopen(argv[2],"r");//打开测试点标准输出文件
	int score=atoi(argv[1]);//取得测试点的分数
	
	fin=fopen("ARAM.in","r");//打开测试点标准输入文件
	fout=fopen("ARAM.out","r");//打开用户的数据输出文件
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
