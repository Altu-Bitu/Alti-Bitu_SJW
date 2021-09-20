#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, x;
    priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    //pair 첫번째 - 절대값, 두번째 - 원래 입력받은 값
    
    cin >> N;
    while(N--){
        cin >> x;
        if(x == 0){
            if(pq.empty())
                cout << 0 << endl;
            else{
                cout << pq.top().second << endl;
                pq.pop();
            }
        }
        else{
            pq.push({abs(x),x});
        }
    }
}