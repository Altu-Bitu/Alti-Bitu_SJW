#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 8
using namespace std;

int N, M, tmp;
vector<int> arr;
int result[MAX];
bool num_check[10001];

void dfs(int cnt){
    if(cnt==M){
        for(int i=0; i<M; i++){
            cout<<result[i]<<" ";
        }
        cout << "\n";
        return;
    }
    for(int i=0; i<arr.size(); i++){
        result[cnt]=arr[i];
        dfs(cnt+1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin>>N>>M;
    for(int i=0; i<N; i++){
        cin>>tmp;
        if(!num_check[tmp]){
            arr.push_back(tmp);
            num_check[tmp]=true;
        }
    }
    sort(arr.begin(), arr.end());

    dfs(0);
}