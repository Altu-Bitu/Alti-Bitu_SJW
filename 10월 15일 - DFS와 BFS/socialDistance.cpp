#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
const int SIZE = 5;

//특정 응시자에 대해 거리두기가 지켜지는지 확인
bool bfs(vector<string> &place, int row, int col) {
    int dr[4] = {-1, 1, 0, 0};//상하좌우 위치 row 갱신
    int dc[4] = {0, 0, -1, 1};//상하좌우 위치 col 갱신

    vector<vector<int>> dist(SIZE, vector<int>(SIZE, 0)); //방문 여부, 각 정점까지의 맨허튼 거리
    queue<pair<int, int>> q;//좌표 넣어둘 큐

    dist[row][col] = 1; //초기값이 0이기 때문에 1로 초기화
    q.push(make_pair(row, col));//큐에 row, col 좌표 삽입

    while (!q.empty()) {//큐가 빌때까지 반복
        int cr = q.front().first;//큐 맨 앞 pair 중 첫번째가 row
        int cc = q.front().second;//두번째 원소가 col
        q.pop();//큐에서 제거

        if (dist[cr][cc] == 3) //맨허튼 거리 2이하까지만 탐색
            continue;//맨허튼 거리 2보다 크니까 continue

        for (int i = 0; i < 4; i++) {
            int nr = cr + dr[i];//상하좌우 탐색
            int nc = cc + dc[i];

            //범위를 벗어나거나, 방문했거나, 파티션이 있음
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE || dist[nr][nc] || place[nr][nc] == 'X')
                continue;
            if (place[nr][nc] == 'P') //응시자가 있으면 거리두기 지키지 못함
                return false;//거리두기 실패해서 false 반환
            dist[nr][nc] = dist[cr][cc] + 1;//맨허튼 거리 +1
            q.push(make_pair(nr, nc));//새로운 좌표 큐에 삽입  
        }
    }
    return true; //거리두기 지킴
}

//특정 대기실에 대해 거리두기가 지켜지는지 확인
bool socialDistance(vector<string> &place) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //응시자가 있다면, 거리두기 확인
            if (place[i][j] == 'P' && !bfs(place, i, j))
                return false;//응시자 있는데 거리두기 안지켰으면 false 반환
        }
    }
    return true;//응시자 있고 거리두기도 지킨 경우 true 반환
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for (int i = 0; i < SIZE; i++)
        answer.push_back(socialDistance(places[i]));
    return answer;
}

/**
 * 맨허튼 거리가 2이하 == BFS 또는 DFS 했을 때의 거리가 2이하
 *
 * 각 대기실의 모든 응시자에 대해 거리두기를 지키고 있는지 확인
 * 5x5 크기의 대기실 5개이기 때문에 모든 응시자에 대해 bfs 또는 dfs를 수행해도 시간 초과 발생하지 않음
 */
int main() {
    vector<vector<string>> places = {{"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
                                     {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
                                     {"PXOPX", "OXOXP", "OXPOX", "OXXOP", "PXPOX"},
                                     {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
                                     {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};
    vector<int> ans = solution(places);
    for (int i = 0; i < SIZE; i++)
        cout << ans[i] << ' ';
}