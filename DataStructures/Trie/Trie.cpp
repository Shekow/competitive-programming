#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<vvpll> vvvpll;
typedef vector<string> vs;
typedef vector<vs> vvs;

template<class T>
struct Trie
{
    struct Node
    {
        bool terminal;
        map<T, Node*> children;
        Node(): terminal(false){}
    };
    Node *root;
    Trie(): root(new Node()){}
    bool exists(vector<T> data)
    {
        Node *cu = root;
        for (auto &e: data)
        {
            if (!cu->children.count(e))
                return false;
            cu = cu->children[e];
        }
        return cu->terminal;
    }
    void insert(vector<T> data)
    {
        Node *cu = root;
        for (auto &e: data)
        {
            if (!cu->children.count(e))
                cu->children[e] = new Node();
            cu = cu->children[e];
        }
        cu->terminal = true;
    }
    Node *retrieve(vector<T> data)
    {
        if (!exists(data))
            return NULL;
        Node *cu = root;
        for (auto &e: data)
            cu = cu->children[e];
        return cu;
    }
    Node *erase(vector<T> &data, Node *node, ll idx)
    {
        if (idx == data.size())
            node = NULL;
        else
        {
            node->children[data[idx]] = erase(data, node->children[data[idx]], idx + 1);
            if (node->children[data[idx]] == NULL)
                node->children.erase(data[idx]);
            if (node->children.empty() && !node->terminal)
                node = NULL;
        }
        return node;
    }
    void dfs(vector<T> &data, Node *node, vector<vector<T>> &res)
    {
        if (node == NULL)
            return;
        if (node->terminal)
            res.pb(data);
        for (auto &e: node->children)
        {
            data.pb(e.first);
            dfs(data, e.second, res);
            data.popb();
        }
    }
    void erase(vector<T> data)
    {
        erase(data, root, 0);
    }
    vector<vector<T>> findByPrefix(vector<T> data)
    {
        vector<vector<T>> res;
        dfs(data, retrieve(data), res);
        return res;
    }
};
