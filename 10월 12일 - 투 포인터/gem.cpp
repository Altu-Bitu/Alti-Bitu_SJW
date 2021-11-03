//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

//시간복잡도 O(n^2) -> 정확성 O, 효율성 X
vector<int> gemList(vector<string> &gems, int gem_size) {
    int size = gems.size();//gems 벡터의 크기로 size 변수 초기화
    vector<int> ans = {1, size};//진열대 번호 ans 벡터 1,size로 초기화

    for (int i = 0; i < size; i++) { //i로 시작하는 구간
        map<string, int> m; //구간에 있는 보석
        for (int j = i; j < size; j++) { //j에서 끝나는 구간
            m[gems[j]]++; //보석 추가
            if (m.size() == gem_size) { //모든 종류의 보석이 있음
                if (j - i < ans[1] - ans[0]) //최단 구간 갱신
                    ans = {i + 1, j + 1};//ans 벡터 시작 진열대 번호 i+1, 끝 진열대 번호 j+1로 갱신
                break; //더이상 구간을 늘릴 필요 없음
            }
        }
    }
    return ans;//진열대 번호 반환
}

//시간복잡도 O(n) -> 정확성 O, 효율성 O
vector<int> gemListTwoPointer(vector<string> &gems, int gem_size) {
    int left = 0, right = 0, size = gems.size();//left, right 0으로 초기화, size는 gems의 사이즈 값으로 초기화
    vector<int> ans = {1, size};//진열대 번호 ans 벡터 1,size로 초기화
    map<string, int> m;//맵 m 생성
    m[gems[left]]++; //초기 구간

    //left는 항상 right의 왼쪽 또는 같은 위치에 있어야 함
    while (left <= right && right < size) {
        if (m.size() == gem_size) { //모든 종류의 보석이 있음
            if (right - left < ans[1] - ans[0]) //최단 구간 갱신
                ans = {left + 1, right + 1};//ans 진열대 번호 left+1, right+1로 갱신
            left++; //구간을 짧게하기 위해 left 이동
            m[gems[left - 1]]--;//key가 gems[right]인 맵의 value -1 
            if (m[gems[left - 1]] == 0) //더이상 이 보석이 없다면 제거
                m.erase(gems[left - 1]);//맵에서 삭제
        } else if (m.size() < gem_size) { //모든 종류의 보석이 있는게 아니라면
            right++; //구간을 길게하기 위해 right 이동
            if (right == size) //런타임 에러 방지
                break;//끝까지 갔으면 break
            m[gems[right]]++;//key가 gems[right]인 맵의 value +1 
        }
    }
    return ans;//진열대 번호 반환
}

vector<int> solution(vector<string> gems) {
    vector<int> answer;//정답 int 벡터

    set<string> unique_gem;//셋 unique_gem 생성
    for (int i = 0; i < gems.size(); i++)//gems 벡터 크기만큼 반복
        unique_gem.insert(gems[i]);//gems[i]값 셋에 삽입
    int gem_size = unique_gem.size(); //보석의 종류

    answer = gemListTwoPointer(gems, gem_size);//진열대 번호 연산
    return answer;//정답 반환
}

int main() {
    //입력
    vector<string> gems = {"DIA", "RUBY", "RUBY", "DIA", "DIA", "EMERALD", "SAPPHIRE", "DIA"};

    //연산
    vector<int> ans = solution(gems);

    //출력
    cout << ans[0] << ' ' << ans[1];
}