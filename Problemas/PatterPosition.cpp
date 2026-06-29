#include<bits/stdc++.h>
#define int long long
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int K = 26;

struct vertex{
    int go[K], pch,par,link = -1, super = -1, leaf = 0;
    vector<int> out;
    vertex(): link(0), super(0){
        mem(go, -1);
    }

    vertex(int ch, int from): pch(ch), par(from){
        mem(go, -1);
    }
};

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
    t[node].out.push_back(index);
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


signed main(){
    string tt; cin>>tt;
    int n; cin>>n;
    vector<int> tami(n);
    for(int i = 0; i < n; i++){
        string s; cin>>s;
        add(s, i);
        tami[i] = (int)s.size();
    }
    vector<int> ans(n, 1e9);
    int nodo = 0;
    for(int i = 0; i < tt.size(); i++){
        char ch = tt[i];
        nodo = go(nodo, ch-'a');
        int x = nodo;
        while(x){
            if(t[x].leaf){
                for(auto id: t[x].out){
                    ans[id] = min(ans[id], i-tami[id]+2);
                }
                t[x].out.clear();
            }
            x = superLink(x);
        }
    }

    for(int i = 0; i < n; i++){
        if(ans[i] > 1e8){
            cout<<-1<<"\n";
        }else cout<<ans[i]<<"\n";
    }

}