#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<int> sa(string s) {
    s += '$';
    int n = s.size(), N = max(256LL, n);
    vector<int> sa(n), c(n), cnt(N);
    for(char x : s) cnt[x]++;
    for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
    for(int i = 0; i < n; i++)
        sa[--cnt[s[i]]] = i;
    c[sa[0]] = 0;
    for(int i = 1; i < n; i++)
        c[sa[i]] = c[sa[i-1]] + (s[sa[i]] != s[sa[i-1]]);
    for(int k = 0; (1 << k) < n; k++) {
        vector<int> sa2(n), c2(n);
        for(int i = 0; i < n; i++)
            sa2[i] = (sa[i] - (1 << k) + n) % n;
        fill(cnt.begin(), cnt.begin() + n, 0);
        for(int x : c) cnt[x]++;
        for(int i = 1; i < n; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i >= 0; i--)
            sa[--cnt[c[sa2[i]]]] = sa2[i];
        c2[sa[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int,int> a = {c[sa[i]], c[(sa[i] + (1 << k)) % n]};
            pair<int,int> b = {c[sa[i-1]], c[(sa[i-1] + (1 << k)) % n]};
            c2[sa[i]] = c2[sa[i-1]] + (a != b);
        }
        c = c2;
    }
    sa.erase(sa.begin());
    return sa;
}

vector<int> lcp(string s, vector<int> &sa) {
    int n = s.size(), k = 0;
    vector<int> rank_(n), lcp_(n);
    for(int i = 0; i < n; i++)
        rank_[sa[i]] = i;
    for(int i = 0; i < n; i++) {
        if(rank_[i] == n-1) { k = 0; continue; }
        int j = sa[rank_[i] + 1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k])
            k++;
        lcp_[rank_[i] + 1] = k;
        k = max(0LL, k-1);
    }
    return lcp_;
}

int histograma(vector<int> &h, vector<int> &good) {
    int n = (int)h.size();
    vector<int> prefix(n+1, 0);
    for(int i = 0; i < n; i++)
        prefix[i+1] = prefix[i] + good[i];

    vector<int> L(n), R(n);
    stack<int> st;
    for(int i = 0; i < n; i++){
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        L[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    while(!st.empty()) st.pop();
    for(int i = n-1; i >= 0; i--){
        while(!st.empty() && h[st.top()] >= h[i]) st.pop();
        R[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        if(h[i] == 0) continue;
        int l = max(0LL, L[i]);
        int r = R[i]-1;
        int cant = prefix[r+1]-prefix[l];
        ans = max(ans, cant*h[i]);
    }
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n; cin>>n;
    string s; cin>>s;
    string t; cin>>t;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    auto suff = sa(s);
    auto lcp1 = lcp(s, suff);
    vector<int> good(n, 0);
    for(int i = 0; i < n; i++){
        good[i] = (t[suff[i]] == '0');
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(t[i] == '0') ans = max(ans, n-i);
    }

    ans = max(ans, histograma(lcp1, good));
    cout<<ans<<endl;
}