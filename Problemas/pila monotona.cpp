#include <bits/stdc++.h>
#define int long long
using namespace std;



int histograma(vector<int> h){
    int n = (int)h.size();
    vector<int> L(n), R(n);
    stack<int> st;
    for(int i = 0; i <  n; i++){
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        if(st.empty()) L[i] = -1;
        else L[i] = st.top();
        st.push(i);
    }
    while(!st.empty()) st.pop();
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        if(st.empty()) R[i] = n;
        else R[i] = st.top();
        st.push(i);
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        int ancho = R[i]-L[i]-1;
        int area = ancho*h[i];
        ans = max(ans, area);
    }
    return ans;
}

signed main(){
    int n; cin>>n;
    vector<int> h(n);
    for(auto &x: h) cin>>x;
    cout<<histograma(h)<<endl;
}

