#include <iostream>
#include <vector>

using namespace std;

//단절점, 단절선 파악 함수
string isTrue(int t, int k, vector<vector<int>> &tree) {
    if (t == 2)//k번째 간선이 단절선인지
        return "yes";//트리는 모든 정점이 연결되어 있고, 싸이클이 존재하지 않기 때문에 모든 간선이 단절선
    if (tree[k].size() >= 2)//k번 정점이 단절점인지 질의
        return "yes";//연결된 간선이 2개 이상이면 단절점
    return "no";//단절점이 아닌 경우
}

/**
 * 부모 노드를 알 수 없기에 트리를 양방향 그래프로 저장
 * 단절점: 트리는 모든 정점이 연결되어 있고, 싸이클이 존재하지 않기 때문에 연결된 간선이 2개 이상이면 단절점
 * 단절선: 트리는 모든 정점이 연결되어 있고, 싸이클이 존재하지 않기 때문에 모든 간선이 단절선
 */

int main() {
    ios_base::sync_with_stdio(false);//입력 속도 향상
    cin.tie(NULL);
    int n, a, b, q, t, k;//트리 정점 개수 n, 간선의 정보 a,b, 질의의 개수 q, 질의 t,k

    //입력
    cin >> n;//트리 정점 개수 입력
    vector<vector<int>> tree(n + 1, vector<int>(0));//정점 개수 n에 따라 트리 배열 생성
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;//간선 정보 입력
        tree[a].push_back(b);//a,b 연결
        tree[b].push_back(a);//b,a 연결
    }
    cin >> q;//질의 개수 입력
    while (q--) {
        cin >> t >> k;//질의 입력(t가 1일 때는 k번 정점이 단절점인지에 대한 질의, t가 2일 때는 입력에서 주어지는 k번째 간선이 단절선인지에 대한 질의)
        cout << isTrue(t, k, tree) << '\n';//질의 답 출력
    }
    return 0;
}