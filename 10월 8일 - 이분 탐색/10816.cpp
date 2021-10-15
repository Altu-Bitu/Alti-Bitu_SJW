//
// Created by iw040 on 2021-10-08.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;

//lower bound, 찾고자 하는 값 x 이상의 수가 처음으로 나오는 위치 계산
int lowerBound(int left, int right, int target) {
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        //중간값이 target보다 크다면 target은 왼쪽에 있음
        //중간값이 target과 같다면 왼쪽에 target과 같은 값이 더 있을 수 있음
        if (arr[mid] >= target)
            right = mid - 1; // left ~ mid - 1로 범위 조정 
        if (arr[mid] < target) //중간값이 target보다 작다면 target은 오른쪽에 있음
            left = mid + 1;// mid + 1 ~ right로 범위 조정
    }
    /**
     * right + 1을 리턴하는 이유
     * right가 움직일 때는 arr[mid]가 target 이상일 때
     * 값이 target 이상이면서, 인덱스가 가장 작은 mid값이 lower bound!
     * right는 mid - 1이므로 right + 1은 lower bound
     */
    return right + 1; //target 이상의 수가 처음 나오는 위치 반환
}

//upper bound, 찾고자 하는 값 x 초과하는 수가 처음으로 나오는 위치 반환
int upperBound(int left, int right, int target) {
    while (left <= right) { //left 포인터가 right 포인터보다 뒤에 있으면 break
        int mid = (left + right) / 2; //중간값
        if (arr[mid] > target) //중간값이 target보다 크다면 target은 왼쪽에 있음
            right = mid - 1; // left ~ mid - 1로 범위 조정 
        //중간값이 target보다 작다면 target은 오른쪽에 있음
        //중간값이 target과 같다면 오른쪽에 target과 같은 값이 더 있을 수 있음
        if (arr[mid] <= target)
            left = mid + 1; // mid + 1 ~ right로 범위 조정
    }
    /**
     * right + 1을 리턴하는 이유
     * break 직전 left와 right는 같은 곳을 가리킴
     * 이 상태에서 right(mid)가 가리키는 값은 target 이하기 때문에 left 포인터가 이동하고 break
     * 이 때의 left값은 target을 처음으로 초과하는 upper bound이며 직전에 left와 right의 위치가 같았으므로 right + 1 == left
     */
    return right + 1; //target 초과하는 수가 처음 나오는 위치 반환
}

int main() {
    ios::sync_with_stdio(false); //입출력 속도 향상
    cin.tie(NULL);

    int n, m, input; //숫자 카드 개수 n, 연산해볼 카드 수 m, 연산할 카드 값 input

    //입력
    cin >> n; //숫자 카드 개수 입력
    arr.assign(n, 0); //벡터 사이즈 n 0으로 초기화
    for (int i = 0; i < n; i++)
        cin >> arr[i]; // 숫자 카드에 적혀있는 정수 입력

    //연산
    sort(arr.begin(), arr.end()); //이분 탐색을 하기 위해선 반드시 정렬을 해야함

    //연산
    cin >> m; // 점수 입력
    while (m--) {
        cin >> input; // 몇 개인지 구해야하는 숫자 카드 입력

        //연산 & 출력
        cout << upperBound(0, n - 1, input) - lowerBound(0, n - 1, input) << ' '; // 숫자 카드 개수 구하는 연산 및 출력
        //cout << upper_bound(arr.begin(), arr.end(), input) - lower_bound(arr.begin(), arr.end(), input) << ' ';
    }
}