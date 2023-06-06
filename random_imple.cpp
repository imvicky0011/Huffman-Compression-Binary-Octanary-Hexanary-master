#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
    char ch;
    int freq;

    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }
};

Node* buildTree(string& str) {
    priority_queue<pair<int, Node*>> q;
    map<char, int> mp;
    for(auto &i : str)
        mp[i]++;
    
    if(mp.size() == 0)
        return NULL;

    for(auto &i : mp) {
        Node* temp = new Node();
        temp -> ch = i.first;
        temp -> freq = i.second;

        q.push(make_pair(i.second, temp));
    }

    while(q.size() > 1) {
        auto first = q.top(); q.pop();
        auto sec = q.top(); q.pop();

        Node* temp = new Node();
        temp -> ch = 'X';
        temp -> freq = (int)(first.second -> freq + sec.second -> freq);

        temp -> left = first.second;
        temp -> right = sec.second;

        q.push(make_pair(temp -> freq, temp));
    }

    return q.top().second;
}

void getEnCoding(Node* root, map<char, string>& mp, string code) {
    if(root -> left == NULL && root -> right == NULL) {
        mp[root -> ch] = code;
        return;
    }
    
    cout << root -> freq << " : " << root -> ch << endl;

    getEnCoding(root->left, mp, code + "0");
    getEnCoding(root->right, mp, code + "1");
}

int main() {
    string str, code = "";
    cin >> str;

    map<char, string> mp;
    Node* tree = buildTree(str);
    getEnCoding(tree, mp, code);

    for(auto &i : mp)
        cout << i.first << " : " << i.second << endl;
}