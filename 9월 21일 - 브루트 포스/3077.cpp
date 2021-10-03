#include <iostream>
#include <vector>
#include <map>

using namespace std;

/**
 * 맵, 셋에서 다루었던 '추월' 문제와 어떤 점에서 다른지 생각해보세요
 */
int main() {
    int n, ans = 0; //해전의 개수, 정답
    string input; //답안 
    map<string, int> seq; //각 입력과 입력의 인덱스

    //입력
    cin >> n; //해전의 개수 입력
    vector<string> answer(n); //현우가 적은 정답
    for (int i = 0; i < n; i++) {
        cin >> input; //올바른 정답 입력 
        seq[input] = i; //맵에 정답과 정답의 인덱스 저장
    }
    for (int i = 0; i < n; i++)
        cin >> answer[i]; // 현우의 답안 입력

    //연산
    //모든 n(n-1)/2개의 쌍에서 올바른 순서로 적힌 답안 찾기
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (seq[answer[i]] < seq[answer[j]]) //두 답안의 상대적인 관계가 맞음
                ans++; //점수 + 1
        }
    }

    //출력
    cout << ans << '/' << n * (n - 1) / 2; //최종 점수 a/b 형식으로 출력
}