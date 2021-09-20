#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int arr[500001];
int result[500001];

int main(){
    int N;
    cin >> N;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; //<높이, 인덱스>
    
    for(int i=1; i<=N; i++){
        cin >> arr[i];
    }
    
    pq.push({arr[N], N}); 
    //제일 마지막 탑부터 거꾸로 
    for(int i=N-1; i>=1; i--){
        while(1){
            if(pq.empty()) break;
            pair<int, int> tmp = pq.top();
            bool popped = false;
            
            if(tmp.first <= arr[i]){ //현재 인덱스 탑의 높이가 tmp 탑 높이보다 높으면 레이저 수신 가능
                pq.pop();
                result[tmp.second] = i; //tmp 탑가 발사한 레이저 수신하는 인덱스에 현재 인덱스 저장
                popped = true;
            }
            //제일 낮은 탑 신호도 못받은 경우
            if(!popped) break;
        }
        pq.push({arr[i],i});
    }
    
    
    for(int i=1; i<=N; i++){
        cout << result[i] << " ";
    }
}