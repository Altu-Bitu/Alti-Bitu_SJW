#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    vector<int> v;
    int arr[8001] ={0,}; //0-4000까지는 음수, 4001-8000은 양수
    
    int N;
    int sum = 0; //평균 계산 위한 전체 값의 합
    int cnt = 0; //2번째 최빈값 구할 때 사용
    
    int num, most_num, most_index; //숫자 입력, 최빈값, 최빈값의 인덱스
    
    cin >> N;
    
    for(int i=0; i<N; i++){ //숫자 입력받아서 벡터에 저장
        cin >> num;
        sum += num;
        
        arr[num+4000]++;
        v.push_back(num);
    }
    
    sort(v.begin(), v.end()); //벡터 정렬
    
    most_index = *max_element(arr, arr+8001); //최대 빈도수 
    
    for(int i=0; i<8001; i++){
        if(cnt==2) break;
        if(arr[i] == most_index){ //빈도수가 최대 빈도수랑 같으면
            most_num = i; //해당 인덱스를 최빈값으로
            cnt++; 
        }
    }
    
    cout << round((float)sum/N) << endl;
    cout << v[v.size()/2] << endl;
    cout << most_num - 4000 << endl;
    cout << v.back()-v.front();
}
