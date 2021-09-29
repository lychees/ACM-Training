#include <cstdio>
#include <cstdlib>

int param[112][4];

int main(){
  freopen("gen.in", "r", stdin);
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 4; j++) scanf("%d", &param[i][j]);
  freopen("gen.bat", "w", stdout);
  for (int i = 0; i < 100; i++){
    printf("gen %d %d %d %d\n", param[i][0], param[i][1], param[i][2], param[i][3]);
    printf("SEAEQ4\n");
    printf("copy SEAEQ.in data%d.in\n", i);
    printf("copy SEAEQ.out data%d.out\n", i);
  }
  return 0;
}
