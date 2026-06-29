#include<bits/stdc++.h>
#define int long long
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;


//pq no son sus ojos
//TLE ASEGURADO
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


vector<int> peso;
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string text; cin>>text;
    int n; cin>>n;
    vector<int> ks(n);
    vector<int> tamis(n);
    for(int i = 0; i <  n; i++){
        int k; cin>>k;
        string s; cin>>s;
        tamis[i] = (int)s.size();
        ks[i] = k;
        add(s, i);
    } 
    vector<int> ans(n, 1e18);
    deque<int> cola[n];  
    int nodo = 0;
    for(int i = 0; i < text.size(); i++){
        char ch = text[i];
        ch -= 'a';
        nodo = go(nodo, ch);
        int x = nodo;
        while(x){
            if(t[x].leaf){
                //que hago?
                for(auto id: t[x].out){
                    if(cola[id].size() < ks[id]){
                        //meter
                        cola[id].push_back(i-tamis[id]+1);
                    }
                    if(cola[id].size() == ks[id]){
                        ans[id] = min(ans[id], cola[id].back() - cola[id].front() + tamis[id]);
                        cola[id].pop_front();
                    }
                }
            }
            x = superLink(x);
        }
    }
    for(auto x: ans){
        if(x > 1e9) cout<<-1<<"\n";
        else cout<<x<<"\n";
    }

}