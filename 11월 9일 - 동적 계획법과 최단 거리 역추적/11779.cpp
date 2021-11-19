//
// Created by BaeSuA on 2021-11-09.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;
const int INF = 1e8;

//역추적
vector<int> back(int x, vector<int> &path) { //x: 도착정점 부터
    vector<int> result(0);//경로 저장할 리스트
    while (x != 0) {
        result.push_back(x);//경로 벡터에 삽입
        x = path[x]; //다음 정점
    }
    return result;//경로(역순) 반환
}

int dijkstra(int n, int s, int e, vector<vector<ci>> &graph, vector<int> &path) {
    vector<int> dist(n + 1, INF);//가중치 저장할 배열 dist
    priority_queue<ci, vector<ci>, greater<>> pq;//우선순위 큐 pq 선언

    //시작 위치 초기화
    dist[s] = 0;
    pq.push({0, s});//(가중치, 시작정점) 삽입

    while (!pq.empty()) {
        int weight = pq.top().first;//현재 정점까지의 가중치 값 
        int node = pq.top().second; //중간 정점
        pq.pop();//우선순위 큐에서 원소 제거

        if (weight > dist[node]) //이미 탐색한 정점 (이 코드 없으면 시간초과)
            continue;

        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i].first; //연결된 정점
            int next_weight = weight + graph[node][i].second; //시작점으로부터 연결된 정점까지의 거리
            if (dist[next_node] > next_weight) { //더 짧은 경로
                dist[next_node] = next_weight;//가중치 갱신
                path[next_node] = node; //경로 저장
                pq.push({next_weight, next_node});//(가중치, 노드) 우선순위 큐에 삽입
            }
        }
    }
    return dist[e];//최소 비용 반환
}

/**
 * 다익스트라 역추적
 * - 기본 문제: 최소 비용 구하기
 */

int main() {
    int n, m, a, b, c, s, e;//도시의 개수n, 버스 개수 m

    //입력
    cin >> n >> m;//도시, 버스 수 입력
    vector<vector<ci>> graph(n + 1, vector<ci>(0)); //인접 리스트
    vector<int> path(n + 1, 0); //경로 저장
    while (m--) {
        cin >> a >> b >> c;//출발 도시 a, 도착 도시 b, 버스 비용 c
        graph[a].push_back({b, c}); //단방향 그래프
    }
    cin >> s >> e;//출발 도시, 도착 도시 입력

    //연산
    int ans = dijkstra(n, s, e, graph, path);//최소 비용 연산
    vector<int> result = back(e, path);//경로 역추적

    //출력
    cout << ans << '\n' << result.size() << '\n';//최소 비용, 경로에 포함되어 있는 도시 개수 출력
    for (int i = result.size() - 1; i >= 0; i--)
        cout << result[i] << ' ';//경로 출력
    return 0;
}