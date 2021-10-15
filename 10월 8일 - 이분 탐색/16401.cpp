#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int childNum(vector<int> &snacks, int len) {
    int cnt = 0; //몇 명에게 나누어주는지
    for (int i = snacks.size() - 1; i >= 0; i--) { //가장 긴 과자부터 검사
        if (snacks[i] < len) //나누어주려는 길이보다 작아지면 더 이상 못 나눠줌
            break; //못나눠주니까 for문 중지
        cnt += (snacks[i] / len);//cnt + snacks[i] len으로 나눴을 때 만들어지는 조각 수
    }

    return cnt;//과자 길이 len일 때 나눠줄 수 있는 수 반환
}

int upperSearch(vector<int> &snacks, int left, int right, int target) {
    int ans = 0;//1명 당 막대 과자 최대 길이
    while (left <= right) {//최소 길이가 최대 길이보다 작거나 같을때까지 반복
        int mid = (left + right) / 2; //과자의 길이
        int cnt = childNum(snacks, mid); //과자 길이가 mid일 때 몇 명에게 나눠주는지

        if (cnt >= target) { //target보다 더 많은 아이들에게 나눠준다면 -> 과자 길이를 더 늘릴 수 있음
            left = mid + 1;//최소 길이 mid+1로 변경
            ans = mid;//최대 길이 mid로 변경
        } else {//나눠줘야 하는 아이들보다 과자 수 작으니까 범위 left ~ mid-1로 변경
            right = mid - 1;
        }
    }

    return ans;//1명 당 막대 과자 최대 길이 반환
}

/**
 * n개의 과자가 있을 때 m명의 조카에게 각각 같은 길이로 줄 수 있는 과자의 최대 길이를 구하는 문제
 * -> 특정 과자 길이에 대하여 m명의 조카에게 나누어 줄 수 있는가?
 *
 * left: 과자 길이의 최솟값 -> 1
 * right: 과자 길이의 최댓값
 *
 * 과자를 몇 명에게 나누어줄 수 있는지 차례로 검사하다 나누어줄 수 없으면 빠져나오기 위해 정렬을 먼저 해주면 좋음
 */

int main() {
    int m, n, left = 1, right = 0;//조카 m명, 과자 n개

    //입력
    cin >> m >> n;//조카 수, 과자 수 입력
    vector<int> snacks(n, 0);//과자 길이 벡터 snack 사이즈 n 값은 모두 0으로 초기화 
    for (int i = 0; i < n; i++)
        cin >> snacks[i];//과자 길이 입력

    //연산
    sort(snacks.begin(), snacks.end());//과자 길이 정렬
    right = snacks[n - 1];//가장 긴 과자 길이를 right으로

    //연산 & 출력
    cout << upperSearch(snacks, left, right, m);//막대 과자 최대 길이 연산 및 출력

    return 0;
}