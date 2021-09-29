#include <iostream>
using namespace std;

char a[10][10]={
"6","7","2EA","2BA","2AE","2AB","2EE","2BB","2FA","2AF"
};
int num;
char cmd[100];
int main(){
	for (int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			sprintf(cmd,"echo %s >> image%d.in",a[i],++num);
			system(cmd);
			sprintf(cmd,"echo %s >> image%d.in",a[j],num);
			system(cmd);
		}
}
