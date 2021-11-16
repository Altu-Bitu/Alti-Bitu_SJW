#include <iostream>
#include <vector>

using namespace std;

//역추적
vector<int> back(int x, vector<int> &path) { //x = n부터 역추적 시작
    vector<int> result(0);//n->1되는 경로에 있는 수 저장하는 result
    while (x != 0) {
        result.push_back(x);//x를 경로 리스트에 push
        x = path[x];//path[x]에 저장된 값을 x로
    }
    return result;//경로 리스트 반환
}

//1로 만드는 최소 연산 횟수 리턴
int makeOne(int n, vector<int> &path) {
    vector<int> dp(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        int min_value = dp[i - 1]; //우선 i - 1 연산 적용한 것으로 저장
        path[i] = i - 1;//경로에 연산을 적용한 다음 수 저장
        if (!(i % 3) && min_value > dp[i / 3]) {//i%3이 0 아니고 dp[i/3]이 min_value인 경우
            min_value = dp[i / 3];//min_value 갱신
            path[i] = i / 3;//path[i]값도 갱신
        }
        if (!(i % 2) && min_value > dp[i / 2]) {//i%3이 0 아니고 dp[i/2]이 min_value인 경우
            min_value = dp[i / 2];//min_value 갱신
            path[i] = i / 2;//연산을 적용한 다음 수 저장
        }
        dp[i] = min_value + 1;//1로 만드는 연산 + 1
    }
    return dp[n];//N을 1로 만들 떄 소요되는 연산 수 반환
}

/**
 * 기본 문제: 1로 만들기
 *
 * [점화식]
 * dp[i] = (i에 가능한 연산을 적용한 수 중 최소 연산 횟수) + 1
 * dp[i] = min(dp[i / 3], dp[i / 2], dp[i - 1]) + 1
 *
 * [역추적]
 * path: 인덱스가 정수를 나타냄, 해당 수에서 연산을 적용한 다음 수를 저장
 * n부터 역추적 시작
 */

int main() {
    int n;//1로 만들 자연수 n

    //입력
    cin >> n;//n 입력
    vector<int> path(n + 1, 0); //경로 저장

    //연산
    int ans = makeOne(n, path);//N을 1로 만드는 연산 횟수
    vector<int> result = back(n, path);//N을 1로 만드는 방법에 포함되어 있는 수 리스트

    //출력
    cout << ans << '\n';
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << ' ';//N을 1로 만드는 방법에 포함되어 있는 수 출력
    return 0;
}