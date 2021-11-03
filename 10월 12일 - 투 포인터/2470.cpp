//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//다른 위치에서 시작하여 서로를 향해 가까워지는 투 포인터
pair<int, int> liquid(vector<int> &arr, int left, int right) {
    pair<int, int> ans;//정답이 되는 두 용액의 값 저장할 ans
    int min_diff = 2 * 1e9 + 1;//두 용액 값의 최소값 min_diff 

    //left는 항상 right의 왼쪽에 있어야 함
    while (left < right) {//left가 right보다 작을때까지 계속
        int mix = arr[left] + arr[right]; //두 용액을 혼합
        if (mix == 0) //그 값이 0이라면 이보다 더 0에 가까워질 수 없기 때문에 바로 리턴
            return make_pair(arr[left], arr[right]);//두 용액의 값 반환
        if (abs(mix) < min_diff) { //0에 가까운 값을 갱신할 수 있는지 확인
            min_diff = abs(mix);//min_diff abs(mix) 값으로 갱신
            ans = make_pair(arr[left], arr[right]);//두 용액의 값 ans에 저장
        }
        if (mix > 0) //0보다 크면 더 작은 값을 만들어야 함
            right--;//범위 right-1로 조정
        else if (mix < 0) //0보다 작으면 더 큰 값을 만들어야 함
            left++;//범위 left+1로 조정
    }
    return ans;//두 용액의 특성값 반환
}

int main() {
    int n;//전체 용액의 수

    //입력
    cin >> n;//전체 용액의 수 입력
    vector<int> arr(n, 0);//용액의 특성값 벡터 arr 크기 n, 값 0으로 초기화
    for (int i = 0; i < n; i++)
        cin >> arr[i];//용액의 특성값 입력

    //연산
    sort(arr.begin(), arr.end());//arr 정렬
    pair<int, int> ans = liquid(arr, 0, n - 1);//특성값이 0에 가장 가까운 용액을 만들어내는 두 용액의 특성값 계산

    //출력
    cout << ans.first << ' ' << ans.second;//출력해야 하는 두 용액 오름차순으로 출력
}