//
// Created by iw040 on 2021-11-23.
//

#include <iostream>
#include <vector>

using namespace std;

vector<bool> cycle;
vector<int> parent;

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //값이 음수면 루트 정점
        return node;//루트 값 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
void unionInput(int x, int y) {
    int xp = findParent(x);//x의 루트 정점
    int yp = findParent(y);//y의 루트 정점

    if (xp == yp) { //같은 집합에 있다면 유니온 할 수 없음
        cycle[xp] = true;//사이클 여부 true로, 같은 집합에 잇으면 사이클 발생해서 유니온 못함
        return;
    }
    if (cycle[xp] || cycle[yp]) //둘 중 하나라도 사이클이 있으면 표시
        cycle[xp] = cycle[yp] = true;//사이클 여부 true로
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];//xp 정점의 개수에 yp 정점의 개수 더해줌
        parent[yp] = xp;//xp를 yp의 새로운 부모로 
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];//yp 정점의 개수에 xp 정점의 개수 더해줌
        parent[xp] = yp;//yp를 xp의 새로운 부모로
    }
}

int cntTree(int n) {
    int cnt = 0;//트리 개수
    for (int i = 1; i <= n; i++) {
        if (parent[i] < 0 && !cycle[i]) //루트 정점인데 사이클도 없을 때
            cnt++;//트리 개수 +1
    }
    return cnt;//트리 개수 반환
}

void printResult(int num, int cnt) {
    cout << "Case " << num;//케이스 번호 출력
    if (cnt == 0)//트리 없으면
        cout << ": No trees.\n";//no trees 출력
    else if (cnt == 1)//트리 한개면
        cout << ": There is one tree.\n";
    else//트리 2개 이상이면
        cout << ": A forest of " << cnt << " trees.\n";//트리 개수 출력
}

int main() {
    int n, m, a, b, test_case = 0;//정점 개수 n, 간선 개수 m, 간선 나타내는 두 정수 a,b

    while (true) {
        test_case++;//테스트 케이스 번호 +1

        //입력
        cin >> n >> m;//정점, 간선 개수 입력
        if (n == 0 && m == 0) //종료 조건
            break;//무한루프 종료
        parent.assign(n + 1, -1);//parents 크기 n+1, 값은 -1로 초기화
        cycle.assign(n + 1, false);//cycle 크기 n+1, 값은 모두 false로 초기화
        while (m--) { //무방향 그래프
            cin >> a >> b;//간선 나타내는 두 정수 a,b 입력
            unionInput(a, b);//유니온 연산
        }

        //연산
        int tree_cnt = cntTree(n);//트리 개수 연산

        //출력
        printResult(test_case, tree_cnt);//테스트 케이스 번호, 결과 출력
    }
}