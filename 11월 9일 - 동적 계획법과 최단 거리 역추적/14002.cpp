//
// Created by BaeSuA on 2021-11-09.
//

#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> ci;

vector<int> back(int x, vector<int> &path) {
    vector<int> result(0); //Lis의 마지막 원소 인덱스부터 들어감
    while (x != -1) {//경로가 없을때까지 반복
        result.push_back(x);//현재 위치 result에 넣어줌
        x = path[x]; //다음 경로
    }
    return result;//부분 수열 인덱스 배열 반환
}

//시간 복잡도 O(n^2) Lis
ci lis(int n, vector<int> &arr, vector<int> &path) {
    vector<int> dp(n, 1);//dp를 위한 배열
    ci ans = {1, 0}; //최장 길이, 마지막 원소 인덱스

    for (int i = 1; i < n; i++) {
        int index = -1; //경로 저장할 변수
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) { //증가하는 관계, 가장 큰 dp[j] + 1
                dp[i] = dp[j] + 1;//dp[i]값 가장 큰 dp[j]+1로 갱신
                index = j;//해 i에서의 위치 j를 인덱스로 갱신
            }
        }
        path[i] = index;//경로에 index를 저장
        if (ans.first < dp[i]) //최장 길이 + 마지막 원소 인덱스 갱신
            ans = {dp[i], i};//ans 값 갱신
    }
    return ans;//최장 길이, 마지막 원소 인덱스 반환
}

/**
 * 동적계획법 역추적
 * - 기본 문제: 가장 긴 증가하는 부분 수열
 */

int main() {
    int n;//수열의 크기

    //입력
    cin >> n;//수열의 크기 입력
    vector<int> arr(n); //수열
    vector<int> path(n, -1); //경로 저장 배열
    for (int i = 0; i < n; i++)
        cin >> arr[i];//수열의 원소 입력

    //연산
    ci ans = lis(n, arr, path); //first: 최장 길이, second: 최장 길이의 마지막 원소 인덱스
    vector<int> result = back(ans.second, path);//부분 수열 인덱스 result 배열에 저장

    //출력
    cout << ans.first << '\n';//부분 수열 길이 출력
    for (int i = result.size() - 1; i >= 0; i--)
        cout << arr[result[i]] << ' ';//result 마지막 인덱스부터 해당하는 원소 출력
    return 0;
}