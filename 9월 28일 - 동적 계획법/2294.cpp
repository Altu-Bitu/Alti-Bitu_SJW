#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

int knapsackCoin(int n, int k, vector<int> &coin) {
    vector<int> dp(k + 1, INF); // 크기 k+1인 벡터 dp 모두 INF로 초기화하여 생성

    dp[0] = 0; //0가치를 만드는 경우 초기화

    // 점화식 i:0~n-1, j:coin[i]~k일 때 dp[j] = min(dp[j], dp[j - coin[i]] + 1)가 됨
    for (int i = 0; i < n; i++) {
        for (int j = coin[i]; j <= k; j++) { //!생각해보기! 배낭 문제에서의 1차원 dp구현과 다른 점은?
            if (dp[j - coin[i]] != INF) //dp[j-coin[i]]가 INF면 dp[j] = dp[j]니까
                dp[j] = min(dp[j], dp[j - coin[i]] + 1); //원래 만들 수 있는 동전 개수 dp[k]와 dp[j-coin[i]]+1 중 작은 값 dp[j]에 저장
        }
    }

    if (dp[k] == INF) 
        return -1; // 불가능한 경우 -1 반환
    return dp[k]; //dp[k]에 저장된 값 반환
}

/**
 * 배낭 문제(12865)와 유사
 * 현재 가치를 만드는 동전 개수의 최솟값 저장
 * = max(기존 값, [현재 가치 - 현재 사용하려는 동전 가치]의 동전 개수 최솟값 + 1)
 *
 * !주의! 최솟값을 찾는 문제이므로 dp 배열 초기화 중요
 * !주의! 배낭 문제와 다르게, 꼭 현재 가치를 정확하게 만드는 경우만 검사해야함
 */

int main() {
    int n, k; // 동전 종류, 가치의 합

    //입력
    cin >> n >> k; // 동전 종류 수, 만들어야하는 금액 입력
    vector<int> coin(n, 0); // 크기 n인 벡터 0으로 초기화하여 생성
    for (int i = 0; i < n; i++)
        cin >> coin[i]; // 동전의 가치 입력

    //연산 + 출력
    cout << knapsackCoin(n, k, coin) << '\n'; // 사용한 동전의 최소 개수 출력

    return 0;
}