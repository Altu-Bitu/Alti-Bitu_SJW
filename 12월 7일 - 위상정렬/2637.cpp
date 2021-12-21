#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;

//위상정렬 + DP
vector<vector<int>> topologicalSort(int n, vector<int> &indegree, vector<vector<ci>> &graph) {
    queue<int> q;//탐색 노드 저장할 큐
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); //각 부품이 몇 개 필요한지 저장

    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) { //진입차수가 0이라면 -> 기본 부품
            q.push(i);//큐에 삽입
            dp[i][i] = 1; //기본 부품 초기화
        }
    }
    while (!q.empty()) {
        int node = q.front();//큐 맨 앞 원소 node에 저장
        q.pop();//큐에서 제거

        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i].first;//graph[node][i].first 값 next_node에 저장
            int cnt = graph[node][i].second; //필요한 부품 수
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node);//next_node 큐에 삽입

            for (int j = 1; j <= n; j++)
                dp[next_node][j] += dp[node][j] * cnt; //(현재 정점을 이루는 부품 개수 * 필요한 현재 정점의 개수)를 더함
        }
    }
    return dp;//기본 부품 번호 순서대로 필요한 개수
}

/**
 * 각 부품마다 종류별 필요한 부품 개수를 저장하기 위해 2차원 배열 사용 (행: 부품, 열: 행을 이루는데 각 부품별 필요한 개수)
 * 위상 정렬 순서에 따라, 이어진 다음 정점의 부품별 개수를 (현재 정점을 이루는 부품별 개수 * 필요한 현재 정점 수)를 더해주며 구함
 */

int main() {
    int n, m, x, y, k;//완제품 번호 n, 부품들 간의 관계 수 m, 부품들 간의 관계 xyk

    //입력
    cin >> n >> m;//완제품 번호, 부품들 관계 수 입력
    vector<vector<ci>> graph(n + 1, vector<ci>(0));//그래프 
    vector<int> indegree(n + 1, 0);//진입차수
    while (m--) {//관계 수만큼 반복
        cin >> x >> y >> k; //y -> x
        indegree[x]++;//x의 진입차수 +1
        graph[y].push_back({x, k});//y에 x,k 연결
    }

    //연산
    vector<vector<int>> result = topologicalSort(n, indegree, graph);//완제품 조립에 필요한 기본 부품 수 연산

    //출력
    for (int i = 1; i <= n; i++) {
        if (result[i][i]) //기본 부품이라면
            cout << i << ' ' << result[n][i] << '\n';//부품번호 소요개수 출력 
    }
    return 0;
}