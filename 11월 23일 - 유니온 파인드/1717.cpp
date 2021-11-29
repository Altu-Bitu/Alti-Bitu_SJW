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
        return node;//본인이 루트니까 node 다시 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) {
    int xp = findParent(x);//x의 루트 정점 찾기
    int yp = findParent(y);//y의 루트 정점 찾기

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return;
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];//xp 정점의 개수에 yp 정점의 개수 더해줌
        parent[yp] = xp;//xp를 yp의 새로운 부모로 
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];//yp 정점의 개수에 xp 정점의 개수 더해줌
        parent[xp] = yp;//yp를 xp의 새로운 부모로
    }
}

int main() {
    ios::sync_with_stdio(false);//입력 속도 향상
    cin.tie(NULL);

    int n, m, cmd, a, b;//집합 크기 n, 연산의 개수 m, 연산 cmd(합집합-0, 같은 집합에 포함되어 있는지-1)

    //입력
    cin >> n >> m;//집합 크기, 연산 개수 입력
    parent.assign(n + 1, -1);//parents 크기 n+1, 값은 모두 -1로 초기화
    while (m--) {
        cin >> cmd >> a >> b;//연산 종류, 수 a,b 입력

        //연산
        if (cmd == 0) { //유니온
            unionInput(a, b);//합집합 연산
        }
        if (cmd == 1) { //파인드
            if (findParent(a) == findParent(b))//루트가 같으면 같은 집합
                cout << "YES\n";//같은 집합이면 yes 출력
            else//같은 집합에 포함안된 경우
                cout << "NO\n";//아니면 no 출력
        }
    }
}