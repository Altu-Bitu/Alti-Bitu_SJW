//
// Created by BaeSuA on 2021-12-07.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//위상정렬 + DP
int topologicalSort(int n, int w, vector<int> &delay, vector<int> &indegree, vector<vector<int>> &graph) {
    //vector<int> result;
    queue<int> q;//탐색할 노드 큐
    vector<int> dp(n + 1, 0); //현재 건물(인덱스)을 짓기까지 걸린 최소 시간

    for (int i = 1; i <= n; i++) {
        dp[i] = delay[i]; //dp 배열 초기화
        if (!indegree[i]) //진입차수가 0이라면
            q.push(i);//큐에 삽입
    }
    while (!q.empty()) {
        int node = q.front();//큐에서 꺼내온 값 node에 저장
        q.pop();//큐에서 제거

        //result.push_back(node); //현재 정점 순서에 삽입
        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i];//next_node 선언 및 graph[node][i] 값으로 초기화
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node);//큐에 삽입

            //다음 정점의 최소 시간 계산 -> 이어진 전 정점(현재 정점) 중 가장 긴 시간의 건물을 선택
            dp[next_node] = max(dp[next_node], dp[node] + delay[next_node]);
        }
    }
    return dp[w];//건물 w 건설완료 하는데 드는 최소 시간 반환
}

int main() {
    int t, n, k, x, y, w;//테스트케이스 수 t, 건물 개수 n, 건물순서 규칙 개수 k, 건물 x,y, 승리위해 건설해야 할 건물 번호 w

    //입력
    cin >> t;//테스트 케이스 개수 입력
    while (t--) {
        cin >> n >> k;//건물 개수, 규칙 개수 입력
        vector<int> indegree(n + 1, 0); //진입차수
        vector<vector<int>> graph(n + 1, vector<int>(0)); //그래프
        vector<int> delay(n + 1, 0); //건설에 걸리는 시간
        for (int i = 1; i <= n; i++)
            cin >> delay[i];//각 건물당 건설에 걸리는 시간 입력
        while (k--) {
            cin >> x >> y; //x -> y
            indegree[y]++;//y의 진입차수 + 1
            graph[x].push_back(y);//x 리스트에 y 삽입
        }
        cin >> w; //승리하기 위해 건설해야 할 건물의 번호

        //연산 & 출력
        cout << topologicalSort(n, w, delay, indegree, graph) << '\n';//건물 w 건설완료 하는데 드는 최소 시간
    }
    return 0;
}