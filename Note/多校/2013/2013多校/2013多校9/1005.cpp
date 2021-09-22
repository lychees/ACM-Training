/* ***********************************************
Author        :kuangbin
Created Time  :2013/8/20 13:11:33
File Name     :F:\2013ACM¡∑œ∞\2013∂‡–£9\1005.cpp
************************************************ */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
string str[] =
{
"NUL","SOH","STX","ETX","XXXXXXX","HT","XXXXXXX","DEL","XXXXXXX","XXXXXXX","XXXXXXX","VT","FF","CR","SO","SI",
"DLE","DC1","DC2","DC3","XXXXXXX","XXXXXXX","BS","XXXXXXX","CAN","EM","XXXXXXX","XXXXXXX","IFS","IGS","IRS","IUS ITB",
"XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","LF","ETB","ESC","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","ENQ","ACK","BEL",
"XXXXXXX","XXXXXXX","SYN","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","EOT","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","DC4","NAK","XXXXXXX","SUB",
"SP","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",".","<","(","+","|",
"&","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","!","$","*",")",";","XXXXXXX",
"-","/","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",",","%","_",">","?",
"XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","`",":","#","@","\'","=","\"",
"XXXXXXX","a","b","c","d","e","f","g","h","i","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"XXXXXXX","j","k","l","m","n","o","p","q","r","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"XXXXXXX","~","s","t","u","v","w","x","y","z","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"^","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","[","]","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"{","A","B","C","D","E","F","G","H","I","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"}","J","K","L","M","N","O","P","Q","R","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"\\","XXXXXXX","S","T","U","V","W","X","Y","Z","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX",
"0","1","2","3","4","5","6","7","8","9","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX","XXXXXXX"
};
string str2[]=
{
	"NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL","BS","HT","LF","VT","FF","CR","SO","SI",
"DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB","CAN","EM","SUB","ESC","IFS","IGS","IRS","IUS ITB",
"SP","!","\"","#","$","%","&","\'","(",")","*","+",",","-",".","/",
"0","1","2","3","4","5","6","7","8","9",":",";","<","=",">","?",
"@","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
"P","Q","R","S","T","U","V","W","X","Y","Z","[","\\","]","^","_",
"`","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
"p","q","r","s","t","u","v","w","x","y","z","{","|","}","~","DEL"
};
char s[10000000];
int change(char ch)
{
	if(ch <='9')return ch-'0';
	else return ch-'A'+10;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%s",s)==1)
	{
		int n = strlen(s);
		for(int i = 0;i < n;i+=2)
		{
			int p = change(s[i])*16 + change(s[i+1]);
			int t = 0;
			while(t < 128 && str2[t] != str[p])t++;
			printf("%02X",t);
		}
		printf("\n");
	}
    return 0;
}
