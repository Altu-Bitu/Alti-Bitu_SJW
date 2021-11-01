//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); //입력 속도 향상

    int n, m, num;//수의 개수 n, 합을 구해야 하는 횟수 m, n개의 수 입력받을 num

    //입력
    cin >> n >> m;//수, 합의 횟수 입력
    vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) { //인덱스를 1부터 시작하면 i=0인 경우를 따로 처리할 필요 없음
        cin >> num;//n개의 수 입력
        sum[i] = sum[i - 1] + num; //첫번째 수부터 i번째 수까지의 누적합
    }

    while (m--) {
        int s, e;//합을 구해야 하는 시작 구간, 끝 구간
        cin >> s >> e;//합을 구해야 하는 구간 입력

        //출력
        cout << sum[e] - sum[s - 1] << '\n';//s번째 수부터 e번째 수까지의 합 출력
    }
}