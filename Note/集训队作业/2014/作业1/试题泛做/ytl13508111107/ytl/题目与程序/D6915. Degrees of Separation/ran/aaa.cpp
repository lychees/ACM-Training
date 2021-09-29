#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main(){
	freopen("degree.in","w",stdout);
	printf("50 50\n");
	for (int i=1;i<=26;i++) printf("%c  %c  ",'a'+i-1,'a'+i-1);
	for (int i=1;i<=24;i++) printf("%c  %c  ",'A'+i-1,'A'+i-1);
	printf("0\n");
	return 0;
}
