#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M; //롤케이크 개수, 자를 수 있는 최대 횟수
int ans; //길이가 10인 롤케이크 수

void cut(int cake){
    if(M <= 0) return;
    int length;
    M--;
    ans++;
    length = cake - 10;
    if(length > 10) {
        cut(length);
    }
    else if(length==10) {
        ans++;
        return;
    }
}

int main(){
    int tmp; 
    vector<int> v1; //길이가 10의 배수인 롤케이크 
    vector<int> v2; //길이 10의 배수아닌 롤케이크
    
    cin >> N >> M;
    for(int i=0; i<N; i++){
        cin >> tmp;
        if(tmp < 10) continue;
        if(tmp == 10){
            ans++;
            continue;
        }
        if(tmp % 10 == 0) v1.push_back(tmp);
        else v2.push_back(tmp);
    }
    sort(v1.begin(), v1.end(), greater<int>());
    sort(v2.begin(), v2.end());
    
    while(M && !v1.empty()){
        tmp = v1.back();
        v1.pop_back();
        cut(tmp);
    }
    
    while(M && !v2.empty()){
        tmp = v2.back();
        v2.pop_back();
        cut(tmp);
    }

    cout << ans;
}