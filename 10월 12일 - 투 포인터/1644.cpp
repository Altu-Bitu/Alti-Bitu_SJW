//
// Created by iw040 on 2021-10-12.
//

#include <iostream>
#include <vector>

using namespace std;

//에라토스테네스의 체로 n 이하인 모든 소수 구하기
vector<bool> isPrime(int n) {
    vector<bool> is_prime(n + 1, true); //소수 여부 저장

    is_prime[0] = is_prime[1] = false;//0과 1은 소수가 아님
    for (int i = 2; i * i <= n; i++) {//루트 n보다 작은 수까지 반복
        if (is_prime[i]) { //i가 소수라면
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false; //i의 배수 제거
        }
    }
    return is_prime;//n 이하 모든 수의 소수 여부 반환
}

//n 이하의 모든 소수
vector<int> primeList(vector<bool> &is_prime) {
    vector<int> prime_list;

    for (int i = 2; i <= is_prime.size(); i++) {
        if (is_prime[i])//i가 소수이면
            prime_list.push_back(i);//prime_list에 삽입
    }
    return prime_list;//n 이하 모든 소수 리스트 반환
}

//같은 위치에서 시작하여 같은 방향으로 이동하는 투 포인터
int findSum(vector<int> &prime_list, int target) {
    int ans = 0;//경우의 수 0으로 초기화
    int size = prime_list.size(), left = 0, right = 0;//소수의 수만큼 size, left, right 변수 0으로 초기화
    int sum = prime_list[left]; //초기 구간

    //left는 항상 right의 왼쪽 또는 같은 위치에 있어야 함
    //right는 항상 size보다 작은 값이어야 함
    while (left <= right && right < size) {
//        if (sum == target) { //구간의 합이 target과 같을 때
//            ans++; left++; right++; //모든 포인터 이동
//            if (right == size)
//                break;
//            sum -= prime_list[left - 1]; //이번 구간에 제외되는 값
//            sum += prime_list[right]; //이번 구간에 추가되는 값
//        } else if (sum > target) { //구간의 합이 target보다 클 때
//            left++; //합을 작게하기 위해 left 이동
//            sum -= prime_list[left - 1];
//        } else if (sum < target) { //구간의 합이 target보다 작을 때
//            right++; //합을 크게하기 위해 right 이동
//            if (right == size)
//                break;
//            sum += prime_list[right];
//        }
        if (sum >= target) { //구간의 합이 target보다 크거나 같다면
            if (sum == target) //같다면
                ans++;//경우의 수 +1
            left++; //합을 작게하기 위해 left 이동
            sum -= prime_list[left - 1];//이번 구간에 제외되는 값
        } else if (sum < target) { //구간의 합이 target보다 작을 때
            right++; //합을 크게하기 위해 right 이동
            if (right == size)//끝까지 이동했을 때
                break;//무한루프 종료
            sum += prime_list[right];//이번 구간에 추가되는 값
        }
    }
    return ans;//경우의 수 반환
}

int main() {
    int n;//자연수 n

    //입력
    cin >> n;//자연수 n 입력

    //연산
    vector<bool> is_prime = isPrime(n);//n 이하인 모든 수의 소수 여부 구하기
    vector<int> prime_list = primeList(is_prime);//n 이하의 모든 소수 구하기
    int ans = findSum(prime_list, n);//n을 연속된 소수의 합으로 나타낼 수 있는 경우의 수 연산

    //출력
    cout << ans;//연속된 소수의 합으로 나타낼 수 있는 경우의 수 출력
}