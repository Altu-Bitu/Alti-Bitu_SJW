#include<iostream>
 
#define MAX 100 + 1
#define mod 1000000000
typedef long long ll;
int n;
ll ans;
ll DP[MAX][11];

int main(void)
{
    scanf("%d", &n);
    
    //DP[a][b] : 숫자 길이가 a, 마지막 수가 b일 경우 가능한 계단의 수
    for (int i = 1; i <= 9; i++){
        DP[1][i] = 1;    // 0을 제외한 한자리 숫자는 모두 계단 수 
    }
    DP[1][0] = 0;
 
    for (int i = 2; i <= n; i++){
        for (int j = 0; j <= 9; j++){
            if (j == 0) DP[i][j] = DP[i - 1][j + 1] % mod;
            else if (j == 9) DP[i][j] = DP[i - 1][j - 1] % mod;
            else DP[i][j] = (DP[i - 1][j - 1] + DP[i - 1][j + 1]) % mod;
        }
    }

    for (int i = 0; i < 10; i++){
        ans = ans + DP[n][i];
    }

    printf("%d", ans % 1000000000);
 
}