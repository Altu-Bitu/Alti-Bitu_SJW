#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //루트 정점
        return node;//루트 정점 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) {
    int xp = findParent(x);//x의 루트 정점 xp
    int yp = findParent(y);//y의 루트 정점 yp

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return;
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];//xp 정점의 개수에 yp 정점의 개수 더해줌
        parent[yp] = xp;//yp의 루트 정점 xp로 갱신
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];//yp 정점의 개수에 xp 정점의 개수 더해줌
        parent[xp] = yp;//xp의 루트 정점 yp로 갱신
    }
}

/**
 * 입력으로 주어지는 i, j 도시의 연결정보를 통해 서로소 집합을 만든 후,
 * 여행 계획으로 세운 도시들이 모두 같은 집합에 속하는지 확인하는 문제
 */

int main() {
    int n, m, a, b, input;//도시 수 n, 여행 계획에 속한 도시들의 수 m, 

    //입력
    cin >> n >> m;//도시 수, 여행 계획에 속한 도시들의 수 입력
    parent.assign(n + 1, -1);//parents 크기 n+1, 값은 모두 -1로 초기화
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> input;//연결 정보 입력(1-연결, 0-연결x)
            if (input) //두 정점이 연결되어 있다면
                unionInput(i, j);//연결된 두 정점 유니온 연산
        }
    }
    cin >> a; //시작 정점
    while (--m) {
        cin >> b;//여행 계획에 있는 도시 입력
        if (findParent(a) != findParent(b)) { //서로 다른 집합이라면 -> 해당 경로 불가능
            cout << "NO";//여행 불가능하면 no
            return 0;
        }
    }
    cout << "YES";//여행 가능하면 yes
}