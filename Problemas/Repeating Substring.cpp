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
            pair<int,int> a = {
                c[sa[i]],
                c[(sa[i] + (1 << k)) % n]
            };
            pair<int,int> b = {
                c[sa[i-1]],
                c[(sa[i-1] + (1 << k)) % n]
            };
            c2[sa[i]] = c2[sa[i-1]] + (a != b);
        }
        c = c2;
    }
    sa.erase(sa.begin());
    return sa;
}


vector<int> lcp(string s, vector<int> &sa) {
    int n = s.size(), k = 0;
    vector<int> rank(n), lcp(n);
    for(int i = 0; i < n; i++)
        rank[sa[i]] = i;
    for(int i = 0; i < n; i++) {
        if(rank[i] == n-1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i] + 1] = k;
        k = max(0LL, k-1);
    }
    return lcp;
}



signed main(){
    string s; cin>>s;
    int n = (int)s.size();
    auto suff = sa(s);
    auto lcp1 = lcp(s, suff);
    int idx = -1;
    int maxi = 0;
    for(int i = 0; i < n; i++){
        if(lcp1[i] > maxi){
            idx = i;
            maxi = lcp1[i];
        }
    }
    if(idx == -1){
        cout<<-1<<endl;
    }else{
        for(int i = suff[idx]; i < suff[idx]+lcp1[idx]; i++){
            cout<<s[i];
        }
    }
    cout<<endl;
}

