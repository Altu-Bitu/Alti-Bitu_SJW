#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int makeTriangle(int n, vector<int> &straw) {
    int ans = -1; // 세 변의 길이 합 최댓값 -1로 초기화

    for (int i = 0; i < n - 2; i++) {
        if (straw[i] < straw[i + 1] + straw[i + 2]) { //삼각형이라면
            ans = straw[i] + straw[i + 1] + straw[i + 2]; // 세 변의 합 ans에 저장
            break; // 최댓값 찾았으니까 반복문 종료
        }
    }

    return ans;
}

/**
 * 세 변의 길이의 합이 최대가 되도록 삼각형을 만드는 문제
 * 주어지는 빨대의 길이를 내림차순 정렬한 후, 길이가 긴 빨대부터 그리디적으로 탐색
 * 현재 빨대 길이를 가장 긴 변의 길이라 가정하고 삼각형이 만들어지는지 확인하면 된다
 */

int main() {
    int n; //빨대의 개수

    //입력
    cin >> n; // 빨대 개수 입력
    vector<int> straw(n, 0); // 빨대 길이 저장할 벡터, 크기 n 모두 0으로 초기화
    for (int i = 0; i < n; i++)
        cin >> straw[i]; //빨대 길이 입력

    //연산
    sort(straw.begin(), straw.end(), greater<>()); // 빨대 길이 내림차순으로 정렬

    //출력
    cout << makeTriangle(n, straw); //만들 수 있는 삼각형 세 변의 길이 합의 최댓값 출력

    return 0;
}