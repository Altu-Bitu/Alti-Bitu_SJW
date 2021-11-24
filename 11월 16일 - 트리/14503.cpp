#include <iostream>
#include <vector>

using namespace std;

int cntCleanRobot(int r, int c, int d, vector<vector<int>> &board) {
    //상, 우, 하, 좌
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    int step = 0, ans = 0;//회전 카운트 step, 청소하는 칸 개수 ans
    while (true) {
        if (board[r][c] == 0) {//현재 위치 청소 안 된 빈칸이면
            board[r][c] = 2;//청소
            ans++;//청소하는 칸 개수 + 1
        }

        if (step == 4) {//한 바퀴 돌아서 제자리로 온 경우
            if (board[r - dr[d]][c - dc[d]] == 1)//후진할 위치가 벽인 경우 작동 멈춤
                return ans;//청소 칸 개수 반환
            r -= dr[d];//row 방향 유지한채 한 칸 후진
            c -= dc[d];//col 방향 유지한채 한 칸 후진
            step = 0;//회전 카운트 다시 0으로
        } else {
            d = (d + 3) % 4;//방향 회전
            if (board[r + dr[d]][c + dc[d]]) {//청소할 공간 없으면
                step++;//그 방향으로 회전
                continue;//다시 현재 방향 기준 왼쪽부터 인접칸 탐색
            }
            r += dr[d];//해당 방향으로 전진
            c += dc[d];//해당 방향으로 전진
            step = 0;//회전 카운트 다시 0으로 
        }
    }
}

/**
 * board 정보 -> 0: 빈 칸, 1: 벽, 2: 청소한 공간
 * step: 회전 카운트. 4가 되면 한 바퀴 돌아 다시 제자리로 돌아왔음을 의미
 *
 * 항상 첫 행, 마지막 행, 첫 열, 마지막 열은 벽이라고 문제에서 주어졌으므로 범위 검사를 할 필요가 없음
 */

int main() {
    int n, m, r, c, d;//세로 n, 가로 m, 로봇 총소기 좌표(r,c), 로봇 청소기 방향 d(북 0, 동 1, 남 2, 서 3)

    //입력
    cin >> n >> m >> r >> c >> d;//세로,가로,좌표,방향 입력
    vector<vector<int>> board(n, vector<int>(m, 0));//장소 상태 저장할 board
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];//장소의 상태 입력(빈 칸 0, 벽 1)
        }
    }

    //연산 & 출력
    cout << cntCleanRobot(r, c, d, board);//청소하는 칸의 개수 연산 및 출력
    return 0;
}