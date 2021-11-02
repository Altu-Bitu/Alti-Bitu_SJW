#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 26;

//알파벳별 등장횟수 저장
vector<int> alphaMap(string str) {
    vector<int> result(SIZE, 0);//알파벳 크기만한 result 배열 모두 0으로 초기화
    for (int i = 0; i < str.size(); i++)
        result[str[i] - 'A']++;//등장한 알파벳 위치의 배열값 +1
    return result;//알파벳 등장횟수 배열 반환
}

/**
 * 단어가 같은 구성일 조건
 * 1. 두 개의 단어가 같은 종류의 문자로 이루어짐
 * 2. 같은 문자는 같은 개수만큼 있음
 *
 * 비슷한 단어의 조건
 * 1. 한 단어에서 한 문자를 더하거나, 빼면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 1개
 * 2. 한 단어에서 한 문자를 바꾸면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 2개
 *    -> !주의! 이때, 두 단어의 길이가 같아야 함 cf) doll | do
 */
int main() {
    int n, ans = 0;//단어의 개수 n, 비슷한 단어 수 ans
    string source, target;//첫번째 단어 source, 비슷한 단어 target

    //입력
    cin >> n >> source;//단어 개수, 첫번쨰 단어 입력

    //연산
    vector<int> source_alpha = alphaMap(source);//첫번째 단어의 알파벳별 등장횟수 연산 후 source_alpha에 저장
    while (--n) {//단어 개수만큼 반복
        cin >> target;//비슷한 단어 입력

        int diff = 0;//두 단어의 차이값 저장할 변수 diff
        vector<int> target_alpha = alphaMap(target);//비교할 단어의 알파벳별 등장횟수 연산 후 target_alpha에 저장
        for (int i = 0; i < SIZE; i++) //두 단어의 차이
            diff += abs(source_alpha[i] - target_alpha[i]);//두 단어의 차이 값 계산 후 절대값 diff에 저장
        if (diff <= 1 || (diff == 2 && source.size() == target.size())) //문자를 더하거나, 빼거나, 바꾸거나
            ans++;//비슷한 단어니까 ans+1
    }

    //출력
    cout << ans;//비슷한 단어 수 출력
}
