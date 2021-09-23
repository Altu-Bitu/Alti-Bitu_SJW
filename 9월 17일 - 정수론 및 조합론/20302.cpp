#include <iostream>
using namespace std;

int prime[100001];
bool result;

void multiply(int n){ //입력받은 n 소인수분해해서 소수 개수 ++
    for(int i=2; i*i<=n; i++){
        while(n%i == 0){
            n/=i;
            prime[i]++;
        }
    }
    if(n>1){
        prime[n]++;
    }
}

void divide(int n){ //입력받은 n 소인수분해해서 소수 개수 --
    for(int i=2; i*i<=n; i++){
        while(n%i == 0){
            n/=i;
            prime[i]--;
        }
    }
    if(n>1){
        prime[n]--;
    }
}

int main(){
    int N, num;
    char oper;

    cin >> N;
    
    for(int i=0; i<N; i++){
        if(i==0){ 
            cin >> num;
            if(num < 0){ //음수면 -1 곱해서 multiply 
                num*=-1;
            }
            else if(num==0){ //입력값이 0이면 무조건 결과 정수
                result = true;
            }
            multiply(num);
        }
        else{
            cin >> oper >> num;
            if(num < 0){
                num*=-1;
            }
            else if(num==0){
                result = true;
            }
            if(oper == '*'){
                multiply(num);
            }
            else if(oper == '/'){
                divide(num);
            }
        }
    }
    
    if(result){
        cout << "mint chocolate";
        return 0;
    }
    for(int i=2;i<100000;i++){ //prime 배열에 하나라도 음수가 있으면 결과값이 정수가 될 수 없음
        if(prime[i]<0){
            cout << "toothpaste";
            return 0;
        }
    }
    cout << "mint chocolate";
}