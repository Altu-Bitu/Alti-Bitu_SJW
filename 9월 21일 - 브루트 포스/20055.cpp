#include <iostream>
#include <vector>

using namespace std;

struct info { //내구도와 로봇 존재 여부
    int power; //내구도
    bool is_on; //로봇 존재 여부
};

vector<info> belt;  //컨테이너 벨트 정보(내구도, 로봇 여부)
int zero_power;     //내구도가 0인 벨트 칸의 개수

int minusPosition(int n, int pos) { //인덱스 감소
    if (--pos >= 0) //감소시킨 위치가 0보다 클 때(== 한바퀴 초과할 때)
        return pos; //pos 반환
    return n * 2 - 1; //맨 끝 위치로 
}

//2. 가장 먼저 벨트에 올라간 로봇부터, 벨트 회전 방향으로 한 칸 이동할 수 있다면 이동 (이동가능: 이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1 이상이어야 함)
void second(int n, int start, int end) {
    int cur = end; 
    while (cur != start) { //end - 1 부터 start 까지 검사
        cur = minusPosition(n, cur);
        int next = (cur + 1) % (n * 2); //다음 위치
        if (belt[cur].is_on && !belt[next].is_on && belt[next].power) { //현재 위치에 로봇이 있고, 다음 위치에 로봇이 없으며 내구성 1이상인 경우 -> 로봇 옮김
            belt[cur].is_on = false; //로봇 내림
            belt[next].power--; // 로봇 올려서 내구도 - 1
            if (next != end) //내리는 위치 아닐 경우만
                belt[next].is_on = true; //로봇 옮기기
            if (belt[next].power == 0) //내구도 0인 경우
                zero_power++; //내구도 0인 칸의 개수 + 1
        }
    }
}

// 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇 올림
void third(int start) { 
    if (belt[start].power) { //올리는 위치의 내구도가 0이 아니라면 로봇 올림
        belt[start].is_on = true; //로봇 존재 여부 true로 바꿈
        belt[start].power--; // 로봇 올려서 내구도 - 1
        if (belt[start].power == 0) //내구도 0인 경우
            zero_power++; //내구도 0인 칸의 개수 + 1
    }
}

/**
 * [컨베이어 벨트 위의 로봇 문제]
 * 1. 벨트가 각 칸 위의 로봇과 함께 한 칸 회전
 * 2. 가장 먼저 벨트에 올라간 로봇부터, 벨트 회전 방향으로 한 칸 이동할 수 있다면 이동 (이동가능: 이동하려는 칸에 로봇이 없고, 그 칸의 내구도가 1 이상이어야 함)
 * 3. 올리는 위치에 있는 칸의 내구도가 0이 아니면 올리는 위치에 로봇 올림
 * 4. 내구도가 0인 칸의 개수가 k개 이상이라면 과정 종료. 그렇지 않다면 1로 돌아감
 * -> 1 ~ 3까지가 1단계
 *
 * [문제 풀이]
 * 벨트의 로봇을 옮기는 게 아니라, 올리는 위치와 내리는 위치의 인덱스 값을 바꿔서 접근
 * 필요한 컨테이너: 내구도와 로봇의 존재여부를 체크할 배열
 * 1번: 벨트의 방향이 오른쪽이므로, 벨트 한 칸 회전 시 올리는 위치와 내리는 위치의 인덱스 값은 하나 감소
 * 2번: 가장 먼저 올라간 로봇부터 고려해야 하므로 (내리는 위치 - 1)부터 (올리는 위치)까지 검사 -> 로봇 옮기는 거 가능하면 존재여부 체크하고 내구도 감소
 * 3번: 올리는 위치 칸 내구도 0이 아니라면 해당 칸 로봇 존재 여부 체크 + 내구도 감소
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; //컨베이어 벨트 길이, 내구도 0인 칸의 개수

    //입력
    cin >> n >> k; //n, k 입력
    belt.assign(n * 2, {0, false}); //내구도 0, 로봇 존재 여부 false로 초기화
    for (int i = 0; i < n * 2; i++)
        cin >> belt[i].power; //각 칸의 내구도 입력

    //연산
    int start = 0;    //올리는 위치
    int end = n - 1;  //내리는 위치
    int step = 0;     //단계 수
    while (true) {
        start = minusPosition(n, start); // 올리는 위치의 인덱스 값 하나 감소
        end = minusPosition(n, end); // 내리는 위치의 인덱스 값 하나 감소
        if (belt[end].is_on) //벨트 회전 후, 로봇이 내리는 위치에 있다면 내리기
            belt[end].is_on = false; //로봇 존재 여부 false로 초기화
        second(n, start, end); //현재 위치에 로봇이 있고, 다음 위치에 로봇이 없으며 내구성 1이상인 경우 -> 로봇 옮김
        third(start); //올리는 위치의 내구도가 0이 아니라면 로봇 올림
        step++; //단계 수 증가
        if (zero_power >= k)
            break; //내구도 0인 칸의 개수가 k개 이상이면 종료
    }

    //출력
    cout << step << '\n'; //정답 출력

    return 0;
}