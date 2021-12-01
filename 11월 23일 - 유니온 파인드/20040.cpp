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
bool unionInput(int x, int y) {
    int xp = findParent(x);//x의 루트 정점 xp
    int yp = findParent(y);//y의 루트 정점 yp

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false;//사이클 발생하니까 유니온 연산 불가(false) 반환
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];//xp 정점의 개수에 yp 정점의 개수 더해줌
        parent[yp] = xp;//xp를 yp의 새로운 부모로 
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];//yp 정점의 개수에 xp 정점의 개수 더해줌
        parent[xp] = yp;//yp를 xp의 새로운 부모로 
    }
    return true;//유니온 연산 성공(true) 반환
}

/**
 * 사이클이 발생한 순간 = 같은 집합에 있는 원소 두 개를 유니온하려 할 때
 * unionInput 함수의 반환형을 bool로 선언하여 cycle이 생성되는 순간 발견하기
 */
int main() {
    int n, m, x, y;//점의 개수 n, 진행된 차례 수 m, 플레이어가 선택한 두 점 번호 x,y

    //입력
    cin >> n >> m;//점의 개수, 진행된 차례 수 입력
    parent.assign(n, -1);//parent 크기 n, -1로 초기화
    for (int i = 0; i < m; i++) {
        cin >> x >> y;//플레이어가 선택한 두 점 번호 입력

        //연산 & 출력
        if (!unionInput(x, y)) { //유니온 할 수 없음 = 사이클이 생성됨
            cout << i + 1;//사이클이 처음으로 만들어진 차례의 번호 출력
            return 0;//종료
        }
    }
    cout << 0;//m 번의 차례를 모두 처리한 이후에도 종료되지 않았으면 0 출력
}