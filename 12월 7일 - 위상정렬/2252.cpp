//
// Created by BaeSuA on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//위상정렬
vector<int> topologicalSort(int n, vector<int> &indegree, vector<vector<int>> &graph) {
    vector<int> result;//정렬 결과 
    queue<int> q;//탐색할 노드 저장하는 큐

    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) //진입차수가 0이라면
            q.push(i);//큐에 삽입
    }
    while (!q.empty()) {//큐가 빌때까지
        int node = q.front();//현재 순서에 둘 노드 큐에서 빼오기
        q.pop();//큐에서 제거

        result.push_back(node); //현재 정점 순서에 삽입
        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i];//next_node 선언 및 graph[node][i]로 초기화
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node);//큐에 삽입
        }
    }
    return result;//정렬된 순서 반환 
}

int main() {
    int n, m, a, b;//학생 수 n, 키 비교 횟수 m, 학생 a,b

    //입력
    cin >> n >> m;//학생 수, 키 비교 회수 입력
    vector<int> indegree(n + 1, 0); //각 정점의 진입차수
    vector<vector<int>> graph(n + 1, vector<int>(0)); //인접 리스트 그래프
    while (m--) {
        cin >> a >> b; //a < b
        indegree[b]++;//b의 진입차수 + 1
        graph[a].push_back(b);//a 리스트에 b 삽입
    }

    //연산
    vector<int> result = topologicalSort(n, indegree, graph);//위상정렬 연산

    //출력
    for (int i = 0; i < n; i++)
        cout << result[i] << ' ';//학생들 키 순서대로 줄 세운 결과 출력

    return 0;
}