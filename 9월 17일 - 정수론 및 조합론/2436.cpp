#include <iostream>
using namespace std;

//유클리드호제법으로 최대공약수 구하는 함수
int gcd(int a, int b) {
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}

int main(){
    int g, l, tmp;
    int ans1=0, ans2=0;
    cin >> g >> l;
    
    tmp = l/g; 
    //A*B = gcd*lcm
    //ans1 = A/gcd, ans2 = B/gcd --> lcm = gcd*ans1*ans2

    for(int i=1; i*i<=tmp; i++){
        if(tmp%i==0){
            if(gcd(max(i, tmp/i), min(i, tmp/i))==1){ //ans1, ans2가 서로소여야 함
                ans1 = i;
                ans2 = tmp/i;
            }
        }
    }
   
    ans1 *= g;
    ans2 *= g;
    
    cout << ans1 << " " << ans2;
}