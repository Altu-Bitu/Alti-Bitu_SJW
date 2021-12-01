#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e9;

int mineLand(int n, int m, int b, int height, vector<vector<int>> &land) {
    int tot_time = 0;//땅 고르는데 걸리는 시간
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (land[i][j] > height) { //블록 제거
                b += (land[i][j] - height);//인벤토리에 블록 추가
                tot_time += 2 * (land[i][j] - height);//h-1의 높이를 만드는건 h보다 2*(N*M)의 시간이 더 소요
            } else if (land[i][j] < height) { //블록 쌓기
                b -= (height - land[i][j]);//인벤토리 블록 사용해서 블록 쌓은만큼 차감
                tot_time += (height - land[i][j]);// h+1의 높이를 만드는건 h보다 (N*M)의 시간이 더 소요
            }
        }
    }
    if (b < 0) //최종적으로 블럭이 음수면 불가능한 높이
        return INF + 1;//min_time 초기값인 INF보다 1 큰 수 반환, min_time 갱신안되게
    return tot_time;//땅 고르기에 걸리는 시간 반환
}

/**
 * 1. 가장 낮은 땅의 높이를 h라고 할 때, h-1의 높이를 만드는건 h보다 2*(N*M)의 시간이 더 소요됨
 * 2. 가장 높은 땅의 높이를 h라고 할 때, h+1의 높이를 만드는건 h보다 (N*M)의 시간이 더 소요됨
 * -> 따라서 땅의 높이가 될 수 있는 후보는 (가장 낮은 땅) ~ (가장 높은 땅)
 * -> 가능한 모든 높이에 대해 브루트포스 연산해도 시간 초과 X
 *
 * !주의! 당장 쌓을 블록이 없더라도 언젠가 다른 곳의 블록을 제거해서 쌓을 수 있음.
 */
int main() {
    int n, m, b, min_height = 256, max_height = 0;//집터 세로 n, 가로 m, 인벤토리에 있는 블록 개수 b

    //입력
    cin >> n >> m >> b;//집터 가로, 세로, 인벤토리 블록 개수 입력
    vector<vector<int>> land(n, vector<int>(m, 0));//땅의 높이 저장할 land 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> land[i][j];//땅의 높이 입력
            min_height = min(min_height, land[i][j]); //제일 낮은 땅 높이
            max_height = max(max_height, land[i][j]); //제일 높은 땅 높이
        }
    }

    //연산
    int min_time = INF, height = 0;//땅을 고르는 데 걸리는 시간, 땅의 높이
    for (int i = min_height; i <= max_height; i++) {
        int t = mineLand(n, m, b, i, land);////땅을 고르는 데 걸리는 시간 연산
        if (t <= min_time) { //가장 빨리 작업이 끝나는 높이
            min_time = t;//min_time 값 t로 갱신
            height = i;//땅의 높이 i로 갱신
        }
    }

    //출력
    cout << min_time << ' ' << height;//땅 고르는데 걸리는 시간, 땅 높이 출력
}