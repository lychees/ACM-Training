#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
//#include<unordered_map>
#include<map>
using namespace std;
#define rep(i,n) for (int i=0;i<n;++i)
const int N=100005;
//unordered_map<string,int> M,H[N],W;
map<string,int> M,H[N],W;
string s,t[N],MTA[N]; int n,m,x,y[N]; vector<int> r[N]; char line[N],buffer[N*10],tmp[N],*p;
int main()
{
//	freopen("G.in","r",stdin);
//	freopen("G.out","w",stdout);
	while (cin>>s,s[0]!='*'){
		cin>>s>>m,M[s]=x=++n,MTA[n]=s;
		while (m--) cin>>s,H[x][s]=1;
	}
	while (cin>>s,s[0]!='*'){
		W.clear(),m=0; strcpy(tmp,s.substr(s.find("@")+1).c_str());
		while (cin>>t[m],t[m][0]!='*') if (!W[t[m]])
			r[y[m]=M[t[m].substr(t[m].find("@")+1)]].push_back(m),W[t[m]]=1,++m;
		p=buffer,gets(line);
		while (gets(line),*line!='*') p+=sprintf(p,"     %s\n",line); sprintf(p,"     .");
		rep(i,m) if (r[x=y[i]].size()){
			bool have=0;
			printf("Connection between %s and %s\n",tmp,MTA[x].c_str());
			printf("     HELO %s\n     250\n     MAIL FROM:<%s>\n     250\n",tmp,s.c_str());
			rep(j,r[x].size()){
				int y=r[x][j]; printf("     RCPT TO:<%s>\n",t[y].c_str());
				bool flag=H[x][t[y].substr(0,t[y].find("@"))]; have|=flag;
				printf("     %d\n",flag?250:550);
			}
			if (have) puts("     DATA\n     354"),puts(buffer),puts("     250");
			puts("     QUIT\n     221"); r[x].clear();
		}
	}
	return 0;
}
