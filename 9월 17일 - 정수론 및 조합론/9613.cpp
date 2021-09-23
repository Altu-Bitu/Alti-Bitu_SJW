#include <iostream>
using namespace std;

//유클리드호제법으로 최대공약수 구하는 함수
int gcd(int a, int b) {
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}


int main(){
    int t, n;
    int arr[101]={0,}; 
    long result[101]={0,}; //테스트 케이스마다 가능한 모든 쌍의 gdc 합 

    cin >> t;
    for(int i=0;i<t;i++){
        cin >> n;
        for(int j=0;j<n;j++){
            cin >> arr[j];
        }
        for(int j=0;j<n;j++){ //가능한 모든 쌍의 gdc 합 구하기
            for(int k=j+1;k<n;k++){
                result[i] += gcd(max(arr[j], arr[k]), min(arr[j], arr[k]));
            }
        }
    }
    for(int i=0;i<t;i++){
        cout << result[i] << endl;
    }
}