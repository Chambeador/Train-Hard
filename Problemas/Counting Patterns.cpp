#include<bits/stdc++.h>
#define int long long
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int K = 26;

struct vertex{
    int go[K], pch,par,link = -1, super = -1, leaf = 0;
    vertex(): link(0), super(0){
        mem(go, -1);
    }

    vertex(int ch, int from): pch(ch), par(from){
        mem(go, -1);
    }
};


vector<int> terminal;

vector<vertex> t(1);
int go(int node, int ch);
int suff(int node);
int superLink(int node);

void add(string &s, int index){
    int node = 0;
    for(auto ch: s){
        ch -= 'a';
        if(t[node].go[ch] == -1){
            t[node].go[ch] = t.size();
            t.emplace_back(ch, node);
        }
        node = t[node].go[ch];
    }
    terminal[index] = node;
    t[node].leaf = 1;
}


//suffix link que hace?
//sufijo propio mas largo que existe en el trie como prefijo
int suff(int node){
    if(t[node].link == -1){
        if(t[node].par == 0){
            t[node].link = 0;
        }else{
            t[node].link = go(suff(t[node].par), t[node].pch);
        }
    }
    return t[node].link;
}


//gogogogo avanzar con una letra
//a que estado me muevo?
int go(int node, int ch){
    if(t[node].go[ch] == -1){
        if(node == 0) t[node].go[ch] = 0;
        else t[node].go[ch] = go(suff(node), ch);
    }
    return t[node].go[ch];
}

//desde este nodo cual es le siguiente ancetro
//suffix link que es terminal
int superLink(int node){
    if(t[node].super == -1){
        int next = suff(node);
        if(t[next].leaf) t[node].super = next;
        else t[node].super= superLink(next);
    }
    return t[node].super;
}


vector<int> ans;

void dfs(int u, vector<vector<int>> &g,int p = -1){
    for(auto &v: g[u]){
        if(v == p) continue;
        dfs(v,g,u);
        ans[u] += ans[v];
    }
}

signed main(){
    string tt; cin>>tt;
    int n; cin>>n;
       terminal.resize(n);
    for(int i = 0; i < n; i++){
        string s; cin>>s;
        add(s, i);
    }
    ans.resize(t.size(), 0);    
 
    vector<vector<int>> g(t.size());
    for(int i = 1; i < t.size(); i++){
        int p = suff(i);
        g[p].push_back(i);
    }

    int node = 0;
    for(auto &ch: tt){
        node = go(node, ch-'a');
        ans[node]++;
    }

    dfs(0,g);

    for(int i = 0; i < n; i++){
        cout<<ans[terminal[i]]<<"\n";
    }


}