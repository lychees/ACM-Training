#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
void setResult(double score) // 输出评测结果
{
    printf("%0.1lf\n", score); // 输出分数
    exit(0); // 结束程序运行，程序返回值应为0
}
int main(int argc,const char *argv[])
{
    const char *inputFileName = argv[1];// 输入文件
    const char *outputFileName = argv[2];// 被评测者的输出文件
    const char *standardFileName = argv[3];// 命题人的参考输出
    const char *logFileName = argv[4];// 检验结果
    freopen(logFileName, "w", stdout); // 直接打开结果文件，使用标准输出
    
    double vu, vs; // 用于记录被评测者的输出和参考输出
    FILE *fout = fopen(outputFileName, "r"); // 打开被评测者的输出
    if (!fout)
        setResult(0.0);
    FILE *fstd = fopen(standardFileName, "r"); // 打开命题人的参考输出
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
