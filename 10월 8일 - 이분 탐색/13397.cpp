#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;

//구간의 점수의 최댓값이 score일 때 나뉘는 구간의 개수
int cntSection(int score) {
    //첫번째 구간의 시작
    int cnt = 1;//나눠지는 구간의 수 1로 초기화
    int min_value = arr[0], max_value = arr[0];//최솟값, 최댓값 arr[0]으로 초기화

    for (int i = 1; i < arr.size(); i++) {
        min_value = min(min_value, arr[i]);//최솟값 갱신
        max_value = max(max_value, arr[i]);//최댓값 갱신
        if (max_value - min_value > score) { //구간의 점수가 score를 초과한다면 새로운 구간 만들기
            cnt++;//새로운 구간 만들어져서 구간 수 + 1
            min_value = arr[i];//arr[i]로 최솟값 변경
            max_value = arr[i];//arr[i]로 최댓값 변경
        }
    }
    return cnt;//나눠지는 구간 수 반환
}

int lowerSearch(int left, int right, int target) {
    int ans = 0;//구간 점수의 최댓값의 최솟값
    while (left <= right) {//구간 점수 최솟값이 최댓값보다 작거나 같을때까지 반복
        //구간의 점수의 최댓값이 mid일 때, 몇 개의 구간이 만들어지는가?
        int mid = (left + right) / 2;//구간 점수 최댓값을 중간값으로 설정
        int section = cntSection(mid);//구간 점수 최댓값이 mid일 때 만들어지는 구간의 수

        if (section <= target) {//만들어지는 구간의 수가 만들 수 있는 구간 수 target보다 작으면
            ans = mid;//구간 점수의 최댓값의 최솟값 mid로 변경
            right = mid - 1;//구간 점수 범위 left ~ mid - 1로 재조정
        } else if (section > target)//만들어지는 구간 수가 target보다 크면
            left = mid + 1;//구간 점수 범위 mid+1 ~ right로 변경
    }
    return ans;//구간 점수의 최댓값의 최솟값 반환
}

/**
 * 배열을 M개 이하의 구간으로 나눈다. 나눈 구간의 점수의 최댓값을 최소로 만든 결과는?
 * -> 구간의 점수의 최댓값이 k라고 할 때, 몇 개의 구간이 필요한가?
 *
 * left (구간 점수의 최댓값의 최솟값) : 배열의 모든 원소가 같다면 구간의 점수는 항상 0이다. 그러므로 구간의 점수의 최댓값도 0이 된다.
 * right (구간 점수의 최댓값의 최댓값) : 구간이 1개라면 그 점수는 가장 큰 값과 가장 작은 값의 차이와 같다.
 */
int main() {
    int n, m;//배열 길이 n, 구간 개수 m
    int min_value = 10001, max_value = 0;//최소 10001, 최대 0으로 초기화

    //입력
    cin >> n >> m;//배열 길이, 구간 개수 입력
    arr.assign(n, 0);//int 벡터 arr 사이즈 n, 모두 0으로 초기화
    for (int i = 0; i < n; i++) {
        cin >> arr[i];//배열 값 입력
        min_value = min(min_value, arr[i]);//배열 원소 중 최솟값 갱신
        max_value = max(max_value, arr[i]);//배열 원소 중 최댓값 갱신
    }

    //연산 & 출력
    cout << lowerSearch(0, max_value - min_value, m);//구간 점수의 최댓값의 최솟값 연산 및 출력
}