#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string str, result;
    cin >> str;
    bool is_cpp = false, is_java = false, err = false;
    
    for(int i = 0; i<str.length(); i++){
        //java 변수 조건 만족
        if(isupper(str[i])){
            //대문자로 시작한 경우, cpp 조건 만족하는 경우
            if(i==0 || is_cpp){ 
                err = true;
                break;
            }
            result += '_';
            result += str[i] - 'A' + 'a';
            is_java = true;
        }
        //cpp 변수 조건 만족
        else if(str[i]=='_'){
            //_ 연속되는 경우, 문자열 시작/끝이 _인 경우, java 조건 만족하는 경우, _ 다음이 대문자인 경우
            if(str[i+1]=='_' || i == str.length() -1 || i==0 || is_java || isupper(str[i+1])){ 
                err = true;
                break;
            }
            result += str[i + 1] - 'a' + 'A';
            i++;
            is_cpp = true;   
        }
        else{
            result += str[i];
        }
    }
    
    if (err)
        cout << "Error!" << endl;
    else
        cout << result << endl;
}
