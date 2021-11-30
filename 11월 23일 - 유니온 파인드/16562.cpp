//
// Created by iw040 on 2021-11-23.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node;//루트 정점 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) {
    int xp = findParent(x);//x의 루트 정점
    int yp = findParent(y);//y의 루트 정점

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return;
    if (parent[xp] > parent[yp]) //새로운 루트 xp
        parent[yp] = xp;//yp의 부모 xp로 갱신
    else //새로운 루트 yp
        parent[xp] = yp;//xp의 부모 yp로 갱신
}

int friendshipCost(int n) {
    int sum = 0;//친구로 만드는 최소비용 sum
    for (int i = 1; i <= n; i++) {
        if (parent[i] < 0) //루트 정점이라면
            sum += -parent[i];//sum에 -친구비 더함
    }
    return sum;//최소비용 반환
}

int main() {
    int n, m, k, v, w, cost;//학생 수 n, 친구관계 수 m, 가지고 있는 돈 k, 학생 v w, 친구비 cost

    //입력
    cin >> n >> m >> k;//학생 수, 친구관계 수, 가진 돈 입력
    parent.assign(n + 1, 0);//parents 크기 n+1, 0으로 초기화
    for (int i = 1; i <= n; i++) {
        cin >> cost;//친구비 입력
        parent[i] = -cost; //루트 정점에 필요한 친구비(음수)를 저장
    }

    //연산
    while (m--) {
        cin >> v >> w;//서로 친구인 학생 v,w 입력
        unionInput(v, w);//유니온 연산
    }

    int ans = friendshipCost(n);//모든 학생을 친구로 만드는 최소 비용 연산

    //출력
    if (ans <= k)//최소비용이 가진 돈보다 작으면
        cout << ans;//최소비용 출력
    else//가진 돈보다 커서 친구 다 사귈 수 없으면
        cout << "Oh no";//oh no 출력
}