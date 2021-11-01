//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <vector>

using namespace std;

//슬라이딩 윈도우로 최대 방문자 수를 구하고, 그 기간의 수를 리턴
pair<int, int> maxVisitor(int n, int x, vector<int> &visitor) {
    //윈도우 초기화
    int section_visitor = 0;
    for (int i = 0; i < x; i++) //첫날부터 x일 동안의 방문자 수
        section_visitor += visitor[i];//누적 방문자 수 계산

    int ans = section_visitor; //최대 방문자 수
    int cnt = 1; //최대 방문자 수인 기간의 수

    //슬라이딩
    for (int i = x; i < n; i++) {
        section_visitor -= visitor[i - x]; //이번 윈도우에 제외되는 값
        section_visitor += visitor[i]; //이번 윈도우에 추가되는 값
        if (section_visitor > ans) { //최대 방문자 수가 갱신된다면
            cnt = 1;//최대 방문자 수인 기간의 수 1로 초기화
            ans = section_visitor;//최대 방문자 수의 값 갱신
        } else if (section_visitor == ans) //최대 방문자 수와 같다면
            cnt++;//최대 방문자 수의 기간 +1
    }
    return make_pair(ans, cnt);//최대 방문자 수, 기간의 수 반환
}

int main() {
    int n, x;//블로그 시작하고 지난 일수 n

    //입력
    cin >> n >> x;//블로그 시작하고 지난 일수 n, x일 입력
    vector<int> visitor(n, 0);//visitor 벡터 크기 n, 0으로 초기화
    for (int i = 0; i < n; i++)
        cin >> visitor[i];//방문자 수 입력

    //연산
    pair<int, int> ans = maxVisitor(n, x, visitor);//최대 방문자 수, 기간의 수 연산

    //출력
    if (ans.first == 0) { //최대 방문자 수가 0명이라면
        cout << "SAD\n";//최대 방문자 수 0명이면 sad 출력
        return 0;
    }
    cout << ans.first << '\n' << ans.second;//최대 방문자 수, 기간 수 출력
}