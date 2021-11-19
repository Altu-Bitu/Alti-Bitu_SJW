#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e7; //최대 n-1개의 간선을 지나게 됨

//역추적
vector<int> back(int s, int x, vector<vector<int>> &path) { //x: 도착점부터
    vector<int> result(0);//역추적 경로 정보
    while (x != 0) {
        result.push_back(x);//경로에 x push
        x = path[s][x]; //다음 경로
    }
    return result;//역추적 경로 반환
}

//모든 (i, j)쌍의 역추적 결과값
vector<vector<int>> allPath(int n, vector<vector<int>> &path) {
    vector<vector<int>> ans(n * n);//모든 (i, j)쌍의 역추적 결과값
    for (int i = 1; i <= n; i++) { //시작점(i)
        for (int j = 1; j <= n; j++) { //도착점(j)
            if (!path[i][j])
                continue;//못가면 반복문 처음으로
            vector<int> result = back(i, j, path);//역추적 경로 연산
            ans[(i - 1) * n + (j - 1)] = result;//i->j의 역추적 경로 ans[(i-1)*n+(j-1)]에 저장
        }
    }
    return ans;//모든 역추적 경로 반환
}

//플로이드-워셜
void floydWarshall(int n, vector<vector<int>> &graph, vector<vector<int>> &path) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int new_dist = graph[i][k] + graph[k][j]; //중간에 k를 거쳐서 i에서 j로 감
                if (new_dist < graph[i][j]) { //i->k->j가 i->j보다 빠른 경로라면
                    graph[i][j] = new_dist;
                    path[i][j] = path[k][j]; //경로(가장 마지막 정점) 저장
                }
            }
        }
    }
}

/**
 * graph: 플로이드-워셜 결과 행렬 그래프
 * path: 경료표. i->k->j로 갈 때 거치는 가장 마지막 정점. 즉, k와 j의 경로에 저장된 정점 <=> path[i][j] = path[k][j]
 * ans: 모든 (i, j)쌍의 역추적 결과값 저장
 *
 * 1. i->j의 중간 경로를 i로 초기화
 * 2. i->k->j가 i->j보다 짧다면 i->j의 중간 경로를 k->j의 중간 경로(path[k][j])로 갱신
 *    k로 갱신하는 게 아니라 path[k][j]로 갱신하는 이유는?
 *    만약 k->j의 경로가 k->t->j라면 최종 경로는 i->k->t->j
 *    바로 k로 갱신하면 t를 놓치고, 이러면 역추적을 할 수 없기 때문에 항상 j의 바로 전 경로를 저장해야 함
 */

int main() {
    int n, m, a, b, c;//도시 수 n, 버스 수 m

    //입력
    cin >> n >> m;//도시, 버스 수 입력
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> path(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) //자기 자신으로 가는 경로 초기화
        graph[i][i] = 0;//자기 자신으로 가는 경로 0으로

    while (m--) {
        cin >> a >> b >> c;//시작 도시 a, 도착 도시 b, 비용 c
        graph[a][b] = min(graph[a][b], c); //단방향 그래프, 중복 간선 들어올 수 있음
        path[a][b] = a; //경로 초기화
    }

    //연산
    floydWarshall(n, graph, path);//플로이드-워셜 연산
    vector<vector<int>> ans = allPath(n, path);//모든 역추적 경로 구하기

    //출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << ((graph[i][j] == INF) ? 0 : graph[i][j]) << ' ';//i->j 가는 최소비용 출력(못가면 0)
        cout << '\n';
    }
    for (int i = 0; i < ans.size(); i++) {
        int size = ans[i].size();//i->j 가는 최소비용에 포함된 도시 수 출력
        cout << size << ' ';
        for (int j = size - 1; j >= 0; j--)
            cout << ans[i][j] << ' ';//i->j가는 경로 출력
        cout << '\n';
    }
    return 0;
}