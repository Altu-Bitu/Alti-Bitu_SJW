#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int INF = 1e4 + 1;

map<int, pair<int, int>> tree;
vector<int> level_left, level_right;
int width;

//너비가 가장 넓은 레벨 구하는 함수
pair<int, int> findMaxWidth(int level) {
    int ans_width = 1, ans_level = 1;//레벨의 너비, 가장 너비 넓은 레벨
    while (level_right[++level] != 0) {
        int level_width = level_right[level] - level_left[level] + 1;//해당 레벨의 너비 계산
        if (ans_width < level_width) {//기존 너비가 더 넓으면 
            ans_width = level_width;//너비값 갱신
            ans_level = level;//레벨값 갱신
        }
    }
    return {ans_level, ans_width};//(너비가 가장 넓은 레벨, 해당 레벨의 너비) 반환
}

//중위 순회를 하며 열 번호 구하는 함수
void inorder(int node, int level) {
    if (node == -1)//노드 존재하지 않는 경우
        return;

    inorder(tree[node].first, level + 1);//왼쪽 노드를 루트로 중위 순회 연산
    level_left[level] = min(level_left[level], width);//가장 왼쪽에 위치한 노드
    level_right[level] = max(level_right[level], width++);//가장 오른쪽에 위치한 노드
    inorder(tree[node].second, level + 1);//오른쪽 노드를 루트로 중위 순회 연산
}

//루트 노드 찾는 함수
int findRoot(int n, vector<int> &node_cnt) {
    for (int i = 1; i <= n; i++)
        if (node_cnt[i] == 1)//해당 노드의 카운트 값이 1이면 루트니까
            return i;//루트 인덱스 반환
}

/**
 * tree: key 값을 부모 노드로 해서 value에 왼쪽, 오른쪽 자식노드를 저장
 * level_left: 레벨을 인덱스로 해당 레벨의 가장 왼쪽 노드의 열 번호 저장
 * level_right: 레벨을 인덱스로 해당 레벨의 가장 오른쪽 노드의 열 번호 저장
 *
 * 루트 노드가 1이 아닐 수 있으므로 루트 노드를 찾아주고 시작해야 함 -> 부모 노드가 없으면 루트 노드 -> 입력으로 한 번 주어진 경우 루트 노드
 * 각 노드의 열 번호는 중위 순회를 했을 때, 출력 순서와 같음 -> 이를 이용해서 중위 순회를 하며 가장 작은 열 번호와 큰 열 번호를 구함
 */

int main() {
    int n, p, l, r;//노드 개수 n, 노드 번호 p, 왼쪽 자식 l, 오른쪽 자식 r

    //입력
    cin >> n;//노드 개수 입력
    level_left.assign(n + 1, INF);//왼쪽 노드 트리
    level_right.assign(n + 1, 0);//오른쪽 노드 트리
    vector<int> node_cnt(n + 1, 0); //루트 노드 찾기 위해서 카운트 저장
    for (int i = 0; i < n; i++) {
        cin >> p >> l >> r;//노드 정보 입력
        node_cnt[p]++;//루트 노드의 카운트 + 1
        if (l != -1)//왼쪽 자식 있는 경우
            node_cnt[l]++;//왼쪽 자식 노드의 카운트 + 1
        if (r != -1)//오른쪽 자식 있는 경우
            node_cnt[r]++;//오른쪽 자식 노드의 카운트 + 1
        tree[p] = make_pair(l, r);//tree 배열의 루트 노드 인덱스에 (왼쪽 노드, 오른쪽 노드) 정보 저장
    }

    //연산
    int root = findRoot(n, node_cnt);//루트 노드 찾는 연산
    inorder(root, 1);//중위 순회
    pair<int, int> ans = findMaxWidth(0);//너비가 가장 넓은 레벨, 해당 레벨의 너비 구하기

    //출력
    cout << ans.first << ' ' << ans.second << '\n';//너비가 가장 넓은 레벨, 해당 레벨의 너비 출력
    return 0;
}