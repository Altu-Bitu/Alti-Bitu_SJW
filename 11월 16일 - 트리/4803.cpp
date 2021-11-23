//
// Created by iw040 on 2021-11-16.
//

#include <iostream>
#include <vector>

using namespace std;

bool is_tree;//트리 여부 
vector<bool> visited;//방문 표시
vector<vector<int>> graph;//트리 그래프

void dfs(int node, int parent) {
    if (visited[node]) { //이미 방문한 정점이라면 사이클이 발생한 것
        is_tree = false;//트리는 사이클이 없는 연결 요소니까 이미 방문한 정점 또 방문하게 되면 트리가 아님
        return;
    }

    visited[node] = true; //방문 처리
    for (int i = 0; i < graph[node].size(); i++) {
        if (graph[node][i] != parent) //부모 정점이 아니라면
            dfs(graph[node][i], node);//트리 여부 dfs 연산
    }
}

void printResult(int num, int cnt) {
    cout << "Case " << num;
    if (cnt == 0)//트리 없으면
        cout << ": No trees.\n";
    else if (cnt == 1)//트리 한개 있으면
        cout << ": There is one tree.\n";
    else//트리 개수 2개 이상이면 
        cout << ": A forest of " << cnt << " trees.\n";
}

int main() {
    int n, m, a, b, test_case = 0;//정점 개수 n, 간선 개수 m, 간선 나타내는 두 정수 a,b, 테스트 케이스 번호 test_case

    while (true) {
        test_case++;//테스트 케이스 번호 +1

        //입력
        cin >> n >> m;//정점, 간선 개수 입력
        if ((n == 0) && (m == 0)) //종료 조건
            break;
        visited.assign(n + 1, false);
        graph.assign(n + 1, vector<int>(0));
        while (m--) { //무방향 그래프
            cin >> a >> b;//간선 정보
            graph[a].push_back(b);//a,b 정점 연결 표시
            graph[b].push_back(a);//a,b 정점 연결 표시
        }

        //연산
        int tree_cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (visited[i]) //이미 방문한 정점
                continue;
            is_tree = true;
            dfs(i, -1);//트리 여부 dfs 연산
            if (is_tree) //트리가 맞다면
                tree_cnt++;//트리 개수 +1
        }

        //출력
        printResult(test_case, tree_cnt);//결과 출력
    }
}