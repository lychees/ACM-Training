#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
void setResult(double score) // ���������
{
    printf("%0.1lf\n", score); // �������
    exit(0); // �����������У����򷵻�ֵӦΪ0
}
int main(int argc,const char *argv[])
{
    const char *inputFileName = argv[1];// �����ļ�
    const char *outputFileName = argv[2];// �������ߵ�����ļ�
    const char *standardFileName = argv[3];// �����˵Ĳο����
    const char *logFileName = argv[4];// ������
    freopen(logFileName, "w", stdout); // ֱ�Ӵ򿪽���ļ���ʹ�ñ�׼���
    
    double vu, vs; // ���ڼ�¼�������ߵ�����Ͳο����
    FILE *fout = fopen(outputFileName, "r"); // �򿪱������ߵ����
    if (!fout)
        setResult(0.0);
    FILE *fstd = fopen(standardFileName, "r"); // �������˵Ĳο����
    if (!fstd)
        setResult(0.0);
    FILE *fin=fopen(inputFileName,"r");
    int T;
    fscanf(fin,"%d",&T);
    for(int i=1,x,y;i<=T;++i)
    {
		fscanf(fout,"Case #%d: %lf",&x,&vu);
		fscanf(fstd,"Case #%d: %lf",&y,&vs);
		if(x!=y||abs(vu-vs)>1e-10)
			setResult(0.0);
	}
	setResult(5.0);
	return 0;
}
