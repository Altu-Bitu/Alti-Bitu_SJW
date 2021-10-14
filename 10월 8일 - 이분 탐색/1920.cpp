//
// Created by iw040 on 2021-10-08.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr; //정수 벡터 arr

//이분 탐색
bool binarySearch(int left, int right, int target) {
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        if (arr[mid] == target) //target을 찾음
            return true; // true 반환(1)
        if (arr[mid] > target) //중간값이 target보다 크다면 target은 왼쪽에 있음
            right = mid - 1; //mid 왼쪽으로 위치 옮겨서 탐색 범위를 조정
        if (arr[mid] < target) //중간값이 target보다 작다면 target은 오른쪽에 있음
            left = mid + 1; // mid 오른쪽으로 위치 옮겨서 탐색 범위 조정
    }
    return false; //target을 찾지 못함, false 반환(0)
}

int main() {
    ios::sync_with_stdio(false); //입출력 속도 향상
    cin.tie(NULL);

    int n, m, input; // 정수 개수 n, 존재하는지 확인할 정수 개수 m, 정수 값 input

    //입력
    cin >> n; // 정수 개수 입력
    arr.assign(n, 0); // 벡터 arr 사이즈 n, 0으로 초기화
    for (int i = 0; i < n; i++)
        cin >> arr[i]; // 정수값 입력받기

    //연산
    sort(arr.begin(), arr.end()); //이분 탐색을 하기 위해선 반드시 정렬을 해야함

    //입력
    cin >> m; //존재 여부 확인해볼 수의 개수
    while (m--) {
        cin >> input; //존재 여부 확인할 정수값 입력

        //연산 & 출력
        cout << binarySearch(0, n - 1, input) << '\n'; // 존재 여부 확인 연산 및 출력(존재하면 1, 없으면 0)
        //cout << binary_search(arr.begin(), arr.end(), input) << '\n';
    }
}