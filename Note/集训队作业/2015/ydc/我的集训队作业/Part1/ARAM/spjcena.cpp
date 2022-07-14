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
	fscore=fopen("score.log","w");//�򿪵÷��ļ�
	freport=fopen("report.log","w");//�򿪱����ļ�
	fstd=fopen(argv[2],"r");//�򿪲��Ե��׼����ļ�
	int score=atoi(argv[1]);//ȡ�ò��Ե�ķ���
	
	fin=fopen("ARAM.in","r");//�򿪲��Ե��׼�����ļ�
	fout=fopen("ARAM.out","r");//���û�����������ļ�
	if (!fout)
	{
		fprintf(fscore,"%d",0);//����0��
		fprintf(freport,"no output");//����Judge���Ϊno output
	}
	else if (Judge())//Judge����Ϊ��
	{
		fprintf(fscore,"%d",score);//��������
		fprintf(freport,"right");//����Judge���Ϊright
	}
	else
	{
		fprintf(fscore,"%d",0);//����0��
		fprintf(freport,"wrong");//����Judge���Ϊwrong
	}

	fclose(fscore);//�رյ÷��ļ�
	fclose(freport);//�رձ����ļ�
	return 0;
}
