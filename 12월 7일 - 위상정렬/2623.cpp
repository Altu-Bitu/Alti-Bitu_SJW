#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//위상정렬
vector<int> topologicalSort(int n, vector<int> &indegree, vector<vector<int>> &graph) {
    vector<int> result;//출연 순서 result 
    queue<int> q;//탐색할 큐

    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) //진입차수가 0이라면
            q.push(i);//큐에 i 삽입
    }

    while (!q.empty()) {//큐가 빌때까지
        int node = q.front();//큐 맨 앞 원소 노드에 저장
        q.pop();//큐에서 제거

        result.push_back(node); //현재 정점 순서에 삽입
        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i];//next_node에 graph[node][i] 저장
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node);//큐에 next_node 삽입
        }
    }
    return result;//출연 순서 반환
}

/**
 * 기본적인 위상 정렬 문제
 * 현재 가수와 바로 전 가수 사이의 선후관계를 정의
 * 순서를 정하는 것이 불가능한 경우(위상정렬을 할 수 없는 경우)는 모든 정점을 탐색하지 못한 경우
 */

int main() {
    int n, m, cnt, prev, cur;//가수 수 n, 보조 pd 수 m

    //입력
    cin >> n >> m;//가수, 보조 pd 수 입력
    vector<int> indegree(n + 1, 0);//진입차수
    vector<vector<int>> graph(n + 1, vector<int>(0));//그래프
    while (m--) {//보조 피이 수많큼 반복
        cin >> cnt; //담당 가수의 수
        cin >> prev; //처음 가수 입력
        while (--cnt) { //선후관계 정의
            cin >> cur;//담당한 가수들 순서대로 입력
            indegree[cur]++;//가수의 진입차수 + 1
            graph[prev].push_back(cur);//prev에 cur 삽입
            prev = cur;//prev 값 cur로 바꿈
        }
    }

    //연산
    vector<int> result = topologicalSort(n, indegree, graph);//가수들의 출연 순서 연산

    //출력
    if (result.size() != n) { //순서를 정하는 것이 불가한 경우
        cout << "0\n";//불가능하면 0 출력
        return 0;
    }
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << '\n';//가수들 출연 순서 출력
}