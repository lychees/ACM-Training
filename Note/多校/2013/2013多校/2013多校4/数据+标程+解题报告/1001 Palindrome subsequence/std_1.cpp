#include <stdio.h>
#include <string.h>

char ch[1002];
int dp[1002][1002];
int main(){
	int T,len;
	scanf("%d",&T);
	for(int cas = 1; cas <= T; cas ++){
		scanf("%s",ch);
		len = strlen(ch);
		memset(dp,0,sizeof(dp));
		for(int i = 0; i < len; i ++){
			dp[i][i] = 1;
		}
		for(int i = 2; i <= len; i ++){
			for(int j = 0; j + i - 1 < len; j ++){
				int s = j;
				int e = j + i - 1;

				if(ch[s] == ch[e]){
					dp[s][e] ++;
					if(s + 1 <= e - 1){
						//dp[s][e] += dp[s+1][e - 1] * 2;
					}
				}else{	
					
					if(s + 1 <= e - 1){
						dp[s][e] -= dp[s+1][e - 1];
					}
				}
				dp[s][e] += dp[s + 1][e] + dp[s][e - 1];
				//printf("dp[%d][%d] = %d dp[%d][%d] = %d\n",s+1,e,dp[s + 1][e],s,e - 1,dp[s][e - 1]);
				dp[s][e] %= 10007;
				//printf("s = %d e = %d %d\n",s,e,dp[s][e]);
			}
		}
		printf("Case %d: %d\n",cas,(dp[0][len - 1]+10007)%10007);
	}
	return 0;
}