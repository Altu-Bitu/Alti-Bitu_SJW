#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main(){
    int n,m;
    long long num, tmp1, tmp2, result = 0;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> num; 
        pq.push(num);
    }
    //첫번째로 작은 수, 두번째로 작은 수 더해서 카드 두 장 모두에 덮어 쓰는 과정
    for(int j = 0; j < m; j++){
        tmp1 = pq.top(); 
        pq.pop();
        tmp2 = pq.top();
        pq.pop();
        pq.push(tmp1+tmp2); 
        pq.push(tmp1+tmp2);
    }
    //모든 카드의 수 더하는 과정
    while(!pq.empty()){
        result += pq.top();
        pq.pop();
    }
    cout << result;
}