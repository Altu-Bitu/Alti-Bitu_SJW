#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 401;
typedef pair<int, int> ci;

pair<int, ci> nextPos(int n, int shark_size, ci &shark, vector<vector<int>> &board) {
    int dr[4] = {-1, 1, 0, 0};//상하좌우 탐색
    int dc[4] = {0, 0, -1, 1};

    int min_dist = INF;//최단거리 min_dist
    queue<ci> q; //상어가 갈 수 있는 곳
    vector<vector<int>> visited(n, vector<int>(n, 0)); //상어의 방문 여부
    vector<ci> list; //상어가 먹을 수 있는 물고기들의 위치

    visited[shark.first][shark.second] = 1;//현재 상어 위치 방문 거리 1로 표시
    q.push(shark);//현재 상어 위치 탐색할 큐에 삽입
    while (!q.empty()) {
        int row = q.front().first;//탐색할 위치 row
        int col = q.front().second;//탐색할 위치 col
        int dist = visited[row][col];//상어의 방문 거리 dist에 저장
        q.pop();//큐에서 제거

        if (dist >= min_dist) //최단거리 이상은 탐색할 필요 없음
            continue;
        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];//row 위치 이동
            int nc = col + dc[i];//col 위치 이동
            if (nr < 0 || nr >= n || nc < 0 || nc >= n || visited[nr][nc] || board[nr][nc] > shark_size)//탐색할 위치가 범위 밖에 있을 떄
                continue;

            visited[nr][nc] = visited[row][col] + 1;//현재 위치의 이동 거리 값 갱신
            if (board[nr][nc] && board[nr][nc] < shark_size) { //먹을 수 있는 물고기 발견
                list.emplace_back(nr, nc);//먹을 수 있는 물고기 위치 list에 삽입
                min_dist = visited[nr][nc];//최단거리 갱신
                continue;
            }
            q.push({nr, nc});//탐색할 큐에 현재 위치 삽입
        }
    }

    if (list.empty()) //상어가 갈 수 있는 곳이 없음
        return {min_dist, {-1, -1}};//최단 거리 반환

    sort(list.begin(), list.end(), [](const ci &p1, const ci &p2) { //정렬
        if (p1.first != p2.first)//거리 가까운 물고기 많을 때 가장 위->가장 왼쪽 물고기 먹음
            return p1.first < p2.first;//가장 위에 있는 물고기
        return p1.second < p2.second;//가장 왼쪽에 있는 물고기
    });
    return {min_dist - 1, list[0]};//최단 거리, 다음에 물고기 위치 반환
}

int simulation(int n, pair<int, int> &shark, vector<vector<int>> &board) {
    int ans = 0, size = 2, cnt = 0;//최단 거리, 상어 크기, 상어가 먹은 물고기 수
    while (true) {
        pair<int, ci> result = nextPos(n, size, shark, board);//최단 거리, 물고기 위치 연산
        if (result.first == INF) //더 이상 먹을 수 있는 물고기가 공간에 없음
            break;//탐색 종료
        ans += result.first;//ans + 최단거리 값으로 ans 갱신
        cnt++;//먹은 물고기 수 + 1
        if (cnt == size) { //상어 크기 증가
            cnt = 0;//먹은 물고기 수 다시 0으로
            size++;//상어 크기 + 1
        }

        //상어 이동
        ci pos = result.second;//상어 이동할 위치 pos
        board[shark.first][shark.second] = 0;//상어 이동하니까 칸 비움
        shark = pos;//상어 위치 pos로 갱신
    }
    return ans;//물고기 잡아먹을 수 있는 시간 반환
}

/**
 * 1. 상어로부터 가장 가까운 거리에 있는 모든 물고기 탐색 (BFS)
 * 2. 우선순위 조건에 맞추어 먹으러 갈 물고기 확정
 *    탐색하는 방향에 우선순위를 두는 걸로 해결되지 않음! (예제 입력 4) 정렬 필요
 * 3. 상어가 이동할 수 있는 곳이 없을 때까지 BFS 탐색 반복
 *
 * 입력 범위가 작기 때문에 매번 BFS 탐색을 반복해도 시간 초과 X
 * 가능한 물고기의 최대 마리 수 : 399마리
 * 최대 BFS 탐색 횟수 : 399회, 1회 탐색마다 while 문은 최대 400회 미만으로 순회
 * 총 연산 횟수 약 160000번으로 충분히 가능
 *
 * 해설 : https://myunji.tistory.com/378
 * *글 자체는 별로 도움이 안되고...그냥 리팩토링하면 코드가 이렇게 되는구나 정도만 봐주세요
 */
int main() {
    int n;//공간 크기 n
    pair<int, int> shark_pos;//상어 위치

    //입력
    cin >> n;//공간의 크기 n 입력
    vector<vector<int>> board(n, vector<int>(n));//공간의 상태 나타내는 2차원 배열 board 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];//공간의 상태 입력(0-빈칸, 123456-물고기크기, 9-아기 상어 위치)
            if (board[i][j] == 9) //상어의 초기 위치
                shark_pos = make_pair(i, j);//상어 위치 i,j 
        }
    }

    //연산 & 출력
    cout << simulation(n, shark_pos, board);//엄마 상어 도움 없이 물고기를 잡아먹을 수 있는 시간 출력
}