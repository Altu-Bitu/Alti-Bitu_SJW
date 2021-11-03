#include <iostream>
#include <vector>

using namespace std;

int steal(vector<int> &house, int n, int m, int k) {
    //윈도우 초기화
    int money = 0;//훔치는 돈의 합 money
    for (int i = 0; i < m; i++)
        money += house[i];//m개 집의 돈의 합

    if (n == m) //훔칠 수 있는 경우 딱 1개인 경우
        return money < k;//마을에 있는 집의 개수와 도둑이 훔칠 집의 개수가 같을 때 훔칠 돈이 방범 돈보다 작으면 1, 크면 0

    int ans = 0;//돈 훔치는 방법 가짓수 ans
    int left = 0, right = m - 1;//윈도우 위치
    do { //원형태로 윈도우를 옮겨야 하기 때문에 종료조건은 left가 초기값(=0)이 됐을 때
        if (money < k) //훔칠 수 있음
            ans++;//가짓수 +1

        money -= house[left];//돈의 합에서 house[left] 빼줌

        //윈도우의 양 끝 이동
        left = (left + 1) % n;//모듈러 연산으로 윈도우 양 끝 위치 조정
        right = (right + 1) % n;

        money += house[right];//이동한 right 집 돈 더해줌
    } while (left);
    return ans;//돈을 훔치는 방법의 가짓수 반환
}

/**
 * 1. 연속해서 훔쳐야 할 집이 m으로 고정됐기 때문에 슬라이딩 윈도우
 * 2. 직선이 아니라 원 형태의 배열! 모듈러 연산을 통해 윈도우의 양 끝 위치 조절하기
 * !주의! 마을에 있는 집의 개수와 도둑이 훔칠 집의 개수가 같을 때(n==m) 도둑이 훔칠 수 있는 경우의 수 1개!
 */
int main() {
    int t, n, m, k;//테스트 케이스 t,집 개수 n, 도둑이 훔쳐야 할 연속된 집의 개수 m, 방범장치 작동하는 최소 돈의 양 k

    cin >> t;//테스트 케이스 수 입력
    while (t--) {
        //입력
        cin >> n >> m >> k;//집 수, 훔칠 집 수, 방범 장치 작동하는 돈 값 입력
        vector<int> house(n, 0);//집이 보관하는 돈 저장하는 리스트
        for (int i = 0; i < n; i++)
            cin >> house[i];//각 집의 돈 입력

        //연산 & 출력
        cout << steal(house, n, m, k) << '\n';//돈을 훔치는 방법의 가짓수 출력
    }
}