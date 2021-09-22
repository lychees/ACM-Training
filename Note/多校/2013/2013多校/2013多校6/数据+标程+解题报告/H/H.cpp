#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000010
char s[N];int n;
int main()
{
	int _;scanf("%d",&_);
	while(_--)
	{
		scanf("%s",s);
		bool F=1;
		if(s[0]!='M')F=0;
		int S=0;n=strlen(s);
		for(int i=1;i<n;i++)
			if(s[i]=='I')S++;else
			if(s[i]=='U')S+=3;else F=0;
		if(S%6!=4&&S%6!=2&&S!=1)F=0;
		puts(F?"Yes":"No");
	}
	return 0;
}