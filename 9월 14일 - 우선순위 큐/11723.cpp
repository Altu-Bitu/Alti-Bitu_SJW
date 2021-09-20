#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, x;
    cin >> M;
    string s;
    bool S[20]={false,};
    
    while(M--){
        cin >> s;
        if(s == "all"){
            memset(S, true, sizeof(S));
        }
        else if(s == "empty"){
            memset(S, false, sizeof(S));
        }
        else{
            cin >> x;
            if(s == "add"){
                S[x-1] = true;
            }
            if(s == "check"){
                S[x-1] ? (puts("1")) : (puts("0"));
            }
            if(s == "remove"){
                S[x-1] = false;
            }
            if(s == "toggle"){
                S[x-1] ? (S[x-1]=false) : (S[x-1]=true);
            }
        }
    }
}