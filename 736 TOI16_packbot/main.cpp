#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    string str, post;
    cin >> str;
    stack<char> stk;
    for (char c : str) {
        if ('A' <= c and c <= 'Z') {
            post.push_back(c);
        } else if (c == '[') {
            stk.push(c);
        } else if (c == ']') {
            while (not stk.empty() and stk.top() != '[') {
                post.push_back(stk.top());
                stk.pop();
            }
            if (not stk.empty()) {
                stk.pop();
            }
        } else {
            while (not stk.empty() and stk.top() != '[' and c <= stk.top()) {
                post.push_back(stk.top());
                stk.pop();
            }
            stk.push(c);
        }
    }
    while (not stk.empty()) {
        post.push_back(stk.top());
        stk.pop();
    }
    stack<int> s;
    for (char c : post) {
        if ('A' <= c and c <= 'Z') {
            s.push(20);
        } else {
            int a = s.top(); s.pop();
            int b = s.top(); s.pop();
            if (c == '1') {
                s.push((a + b) * 104 / 100);
            } else if (c == '2') {
                s.push((a + b) * 108 / 100);
            } else if (c == '3') {
                s.push((a + b) * 116 / 100);
            }
        }
    }
    cout << s.top();
}