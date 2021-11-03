#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef pair<int, int> ci;

//상, 하, 좌, 우, 좌상향 대각선, 우상향 대각석, 좌하향 대각선, 우하향 대각선
int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dc[8] = {0, 0, -1, 1, -1, 1, -1, 1};

vector<vector<int>> board;
int h, w;

//dfs 탐색
void dfs(int cr, int cc) {
    board[cr][cc] = 0; //방문 체크

    for (int i = 0; i < 8; i++) { //가능한 방향의 정점(자식노드) 모두 탐색
        int nr = cr + dr[i];//상, 하, 좌, 우, 좌상향 대각선, 우상향 대각석, 좌하향 대각선, 우하향 대각선 row, col 값 계산
        int nc = cc + dc[i];
        if (nr >= 0 && nr < h && nc >= 0 && nc < w && board[nr][nc]) //탐색하려는 정점이 범위 내에 있고, 땅이라면
            dfs(nr, nc); //바로 탐색(깊게 탐색)
    }
}

//bfs 탐색
void bfs(int row, int col) {
    queue<ci> q;//행,열 정보 저장할 큐

    q.push(ci(row, col));//큐에 현재 위치 삽입
    board[row][col] = 0; //처음 위치 방문 체크

    while (!q.empty()) {
        int cr = q.front().first; //현재 정점의 행 정보
        int cc = q.front().second; //현재 정점의 열 정보
        q.pop();//큐에서 제거

        for (int i = 0; i < 8; i++) { //가능한 방향의 정점(자식노드) 모두 탐색
            int nr = cr + dr[i];//상, 하, 좌, 우, 좌상향 대각선, 우상향 대각석, 좌하향 대각선, 우하향 대각선 탐색
            int nc = cc + dc[i];
            if (nr >= 0 && nr < h && nc >= 0 && nc < w && board[nr][nc]) { //탐색하려는 정점이 범위 내에 있고, 땅이라면
                board[nr][nc] = 0;//방문했으니까 0으로 값 바꿈
                q.push(ci(nr, nc));//해당 위치 큐에 다시 삽입
            }
        }
    }
}

/**
 * 섬의 개수를 구하는 문제 -> 섬의 개수만큼 탐색을 하면 된다
 * 모든 정점을 검사해야 하므로 dfs, bfs 풀이 모두 가능
 * 입력으로 들어오는 보드를 방문 탐색 배열로 함께 사용 (방문하면 1(땅)을 0(바다)으로 바꾸기)
 */

int main() {
    while (true) {
        cin >> w >> h;//지도 너비 w, 높이 h 입력
        if (w == 0)//너비가 0이면 종료
            break;

        //보드 입력
        board.assign(h, vector<int>(w, 0));//h*w 2차원 배열
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> board[i][j];//지도 정보 입력

        //연산 & 출력
        int ans = 0;//섬의 개수 ans
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (board[i][j]) { //땅을 찾았다면 바로 탐색 시작
                    ans++;//섬의 개수+1
                    bfs(i, j);//bfs 연산
                    //dfs(i, j);
                }
            }
        }
        cout << ans << '\n';//섬의 개수 출력
    }
    return 0;
}