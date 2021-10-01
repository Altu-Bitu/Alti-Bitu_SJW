#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 10;

int k; //부등호 갯수
bool is_find; //값 찾았는지 여부 
vector<char> op(SIZE); //부등호
vector<int> arr(SIZE), num(SIZE); //최대/최소값 수열 저장을 위한 벡터, 
vector<bool> check(SIZE); //숫자 사용 여부 표시

//수열을 문자열로 바꾸는 함수
string arrToString(vector<int> &arr) {
    string result;
    for (int i = 0; i <= k; i++)
        result += (arr[i] + '0'); //수열을 문자열로 변환
    return result; //문자열 결과 반환
}

//과정에서의 답이 가능성 있는 답인지 체크하는 함수
bool promising(int idx) {
    if (op[idx] == '<' && arr[idx] > arr[idx + 1]) //부등호가 '<'인데 '>'관계일 때
        return false; // 부등호 관계를 만족시키지 못해서 false를 return
    if (op[idx] == '>' && arr[idx] < arr[idx + 1]) //부등호가 '>'인데 '<'관계일 때
        return false; // 부등호 관계를 만족시키지 못해서 false를 return
    return true; //부등호 관계 만족시켜서 true를 return
}

//최댓값 or 최솟값 구하는 백트래킹 함수 (num배열을 통해 구분)
void findValue(int cnt) {
    //수가 2개 이상이 배치됐다면, 주어진 부등호 만족하는지 검사, 만족하지 않으면 바로 리턴 (가지치기)
    if (cnt >= 2 && !promising(cnt - 2))
        return;
    if (cnt == k + 1) { //부등호 만족하는 수를 찾음 (기저조건)
        is_find = true; //부등호 관계 만족
        return;
    }
    for (int i = 0; i <= k; i++) { //num[i]: 최댓값이면 9 ~ (9-k), 최솟값이면 0 ~ k
        if (!check[num[i]]) { //숫자 사용된 적 없는 경우
            check[num[i]] = true; //숫자 사용 표시
            arr[cnt] = num[i];  //해당 수를 수열에 저장
            findValue(cnt + 1); //다음 수에 대하여 반복
            if (is_find) //부등호 관계 만족하는 값 찾으면
                return; //함수 종료
            check[num[i]] = false; //check 다시 false로 초기화
            arr[cnt] = 0; //arr 값 다시 0으로 초기화
        }
    }
}

/**
 * [백트래킹 풀이] (0ms)
 * 수를 중복없이 배치함 (N과 M(1)과 동일)
 * 수를 배치할 때마다 해당 수가 그 전 수와 부등호 관계를 만족하는지 확인, 만족하지 않으면 back (가지치기)
 */

int main() {
    string max_num, min_num; //정답

    //입력
    cin >> k; //부등호 개수 입력
    for (int i = 0; i < k; i++) {
        cin >> op[i]; //부등호 입력
    }

    //최댓값 연산
    for (int i = 0; i <= k; i++) //num배열에 값 미리 저장
        num[i] = 9 - i; //최댓값은 9부터 (9-k)까지 숫자로 이루어짐
    findValue(0); //최댓값 구하기
    max_num = arrToString(arr); //최댓값 문자열로 바꾸기

    //초기화 !주의! 전역변수 사용 시 초기화 빼먹기 쉬우니 잘 체크하자
    is_find = false; //is_find 다시 false로 초기화
    check.assign(SIZE, false); //check 벡터의 값을 false로 채우기
    arr.assign(SIZE, 0); //arr 벡터의 값을 0으로 채우기

    //최솟값 연산
    for (int i = 0; i <= k; i++)
        num[i] = i; //최솟값은 0부터 k까지 숫자로 이루어짐
    findValue(0); //최솟값 구하기
    min_num = arrToString(arr); //최솟값 문자열로 바꾸기

    //출력
    cout << max_num << '\n' << min_num; //최댓값, 최솟값 차례로 출력

    return 0;
}