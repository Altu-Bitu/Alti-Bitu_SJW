//
// Created by iw040 on 2021-11-16.
//

#include <iostream>
#include <map>

using namespace std;

map<char, pair<char, char>> tree;//루트, <왼쪽자식, 오른쪽자식> 정보 저장하는 트리 맵

//전위 순회 (루트) (왼쪽 자식) (오른쪽 자식)
void preorder(char node) {
    if (node == '.')//자식 노드 없는 경우
        return;
    cout << node;//루트 노드 출력
    preorder(tree[node].first);///왼쪽 자식 노드부터 전위 순회
    preorder(tree[node].second);//오른쪽 자식 노드 전위 순회
}

//중위 순회 (왼쪽 자식) (루트) (오른쪽 자식)
void inorder(char node) {
    if (node == '.')//자식 노드 없는 경우
        return;
    inorder(tree[node].first);//왼쪽 자식 노드 중위 순회
    cout << node;//루트 노드 출력
    inorder(tree[node].second);//오른쪽 자식 노드 중위 순회
}

//후위 순회 (왼쪽 자식) (오른쪽 자식) (루트)
void postorder(char node) {
    if (node == '.')//자식 노드 없는 경우
        return;
    postorder(tree[node].first);//왼쪽 자식 노드 후위 순회
    postorder(tree[node].second);//오른쪽 자식 노드 후위 순회
    cout << node;//루트 노드 출력
}

int main() {
    int n;//이진트리 노드 개수
    char root, left, right;//루트, 왼쪽 자식 노드, 오른쪽 자식 노드

    //입력
    cin >> n;//노드 개수 입력
    while (n--) {
        cin >> root >> left >> right;//루트, 왼쪽 자식, 오른쪽 자식 입력
        tree[root] = make_pair(left, right);//트리에 저장
    }

    //연산 & 출력
    preorder('A');//전위 순회 연산
    cout << '\n';

    inorder('A');//중위 순회 연산
    cout << '\n';

    postorder('A');//후위 순회 연산
    cout << '\n';
}
