#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> board;
int dr[2] = {1, 0};//오른쪽, 아래 방향 이동
int dc[2] = {0, 1};

int cntCandy(int n, int row, int col, int dir) {
    int ans = 0, cnt = 0;//사탕 개수 ans, 같은 색 사탕 카운트하는 cnt
    char cur = ' ';//이전 사탕 색 저장하는 cur
    for (int i = 0; i < n; i++) {
        if (cur == board[row][col]) { //연속된 사탕
            cnt++;//cnt+1
            ans = max(ans, cnt);//사탕 최대값 갱신
        } else { //불연속
            cnt = 1;//cnt값 1로 갱신
            cur = board[row][col];//cur값 현재 사탕 색으로 갱신
        }
        row += dr[dir];//행 이동
        col += dc[dir];//열 이동
    }
    return ans;//사탕 개수 반환
}

int findCandy(int n) {
    int ans = 0;//사탕 개수
    for (int i = 0; i < n; i++) {
        ans = max(ans, cntCandy(n, 0, i, 0)); //같은 열에 대해
        ans = max(ans, cntCandy(n, i, 0, 1)); //같은 행에 대해
    }
    return ans;//사탕 개수 반환
}

int switchCandy(int n, int row, int col, char candy) {
    int ans = 0;//최대 사탕 개수
    for (int i = 0; i < 2; i++) { //오른쪽, 아래에 있는 사탕과 바꿔보기
        int nr = row + dr[i], nc = col + dc[i];//행, 열 위치 이동
        if (nr < n && nc < n && candy != board[nr][nc]) {//보드 범위 내에 있으면
            swap(board[row][col], board[nr][nc]);//사탕 교환
            ans = max(ans, findCandy(n));//사탕 최대값 계산
            swap(board[row][col], board[nr][nc]);//다시 사탕 교환
        }
    }
    return ans;//최대 사탕 개수 반환
}

/**
 * 입력 범위가 크지 않으므로 바꿀 수 있는 사탕을 모두 바꿔보며 먹을 수 있는 사탕 계산
 * 오른쪽, 아래에 있는 사탕과만 바꿔도 모든 경우 고려 가능(왼쪽, 위 고려 X)
 *
 * 1. 사탕의 색이 다른 사탕만 교환하기
 * 2. 각 열, 행이 모두 같은 사탕일 때 사탕의 개수가 갱신되지 않도록 주의 (ans 갱신을 line 18~21에서 하는 경우)
 */
int main() {
    int n, max_candy = 0;//보드 크기 n

    //입력
    cin >> n;//보드 크기 입력
    board.assign(n, vector<char>(n, ' '));//크기 n인 보드, 값 ' '로 초기화
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];//보드 각 위치의 사탕 색상 입력

    //연산
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            max_candy = max(max_candy, switchCandy(n, i, j, board[i][j]));//먹을 수 잇는 사탕의 최대 개수 연산
    }

    //출력
    cout << max_candy;//사탕의 최대 개수 출력
}