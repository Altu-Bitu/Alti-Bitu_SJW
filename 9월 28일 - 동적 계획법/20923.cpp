#include <iostream>
#include <vector>
#include <deque>

using namespace std;

//그라운드에 있는 카드를 덱으로 옮기는 함수
void moveCard(deque<int> &deck, deque<int> &ground) {
    while (!ground.empty()) { //그라운드에 카드가 존재하면
        deck.push_back(ground.back()); //덱 뒤에 그라운드의 마지막 카드 합침
        ground.pop_back(); // 그라운드 마지막 카드 꺼내기
    }
}

//게임을 진행하는 함수
pair<int, int> playGame(int m, vector<deque<int>> &deck, vector<deque<int>> &ground) {
    bool turn = false; //도도부터 시작

    while (m--) {
        //이번 턴의 사람이 카드 뒤집어서 그라운드에 올려놓기
        int card = deck[turn].front(); //deck의 첫번째 요소 반환해서 card에 저장
        ground[turn].push_front(card); // ground의 첫번째 원소 앞에 card 값 추가
        deck[turn].pop_front(); // deck의 첫번째 원소 꺼낵기

        //게임 진행 도중 둘 중 한 명의 덱에 있는 카드의 수가 0개가 되는 즉시 게임 종료
        if (deck[turn].empty()) // 카드 한 장 꺼낸 후 카드 수가 0이면
            break; // 게임 종료

        //이번에 종을 칠 사람
        int bell = -1;
        if (card == 5)  //카드 숫자가 5가 나온 경우
            bell = 0; // 도도가 종을 침
        // 그라운드와 카드 더미 수의 합이 5가 된 경우
        else if (!ground[0].empty() && !ground[1].empty() && (card + ground[!turn].front() == 5)) 
            bell = 1; // 수연이가 종을 침

        if (bell != -1) { //누군가가 종을 쳤다면
            moveCard(deck[bell], ground[!bell]); // 상대의 그라운드 카드 더미를 뒤집어 자신의 덱 아래로 합침
            moveCard(deck[bell], ground[bell]); // 자신의 그라운드 카드 더미를 자신의 덱 아래에 합침
        }
        turn = !turn; //차례 바꾸기
    }
    return make_pair(deck[0].size(), deck[1].size()); //도도의 덱 사이즈, 수연의 덱 사이즈 반환
}

/**
 * 1. 카드 덱과 그라운드의 카드를 관리하기 위해 덱 사용
 * 2. 게임을 진행하던 도중 언제든지 누군가의 카드 덱이 비게되면 게임을 종료
 */
int main() {
    int n, m, num1, num2; //n 카드 개수, m 게임 진행 횟수
    vector<deque<int>> deck(2), ground(2); // 도도, 수연의 덱, 그라운드

    cin >> n >> m; //카드 개수, 게임 진행 횟수 입력
    while (n--) { // 카드 개수가 0이 될 때까지 
        cin >> num1 >> num2; // 도도와 수연이가 가진 덱의 맨 아래 위치한 카드부터 위까지 차례대로 입력
        deck[0].push_front(num1); // 도도의 덱 첫 원소에 num1 추가
        deck[1].push_front(num2); // 수연의 덱 첫 원소에 num2 추가
    }

    pair<int, int> result = playGame(m, deck, ground); //게임 진행 및 결과 연산

    if (result.first == result.second) // 비겼을 경우
        cout << "dosu\n"; // dosu 출력
    else if (result.first > result.second) // 도도가 이긴 경우
        cout << "do\n"; // do 출력
    else if (result.first < result.second) // 수연이 이긴 경우
        cout << "su\n"; // su 출력
}