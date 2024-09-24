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

// when doing HLD on edges:
// value for each node is the value of the edge that leads to its parent
// subtract one from the range query when the two nodes are in the same chain
template<class T, class F>
struct HLD
{
    ll n;
    F merge;
    vvll adj;
    vector<T> val, data;
    vll dep, sz, par, right, head, pos;
    SegTree<T, F> tree;
    HLD(vvll &adj, vector<T> val, ll root = 1)
    : adj(adj), val(val), n(adj.size())
    {
        dep.resize(n);
        sz.resize(n);
        par.resize(n);
        right.resize(n);
        head.resize(n);
        pos.resize(n);
        data.reserve(n);
        dfs(root);
        decompose(root);
        tree = SegTree<T, F>(data);
    }
    ll dfs(ll u, ll p = -1, ll d = 0)
    {
        dep[u] = d, par[u] = p;
        ll cuSz = 1;
        for (auto &v: adj[u])
            if (v != p)
                cuSz += dfs(v, u, d + 1);
        return sz[u] = cuSz;
    }
    void decompose(ll u, ll cnt = 1)
    {
        ll maxSz = 0;
        for (auto &v: adj[u])
            if (v != par[u])
                maxSz = max(maxSz, sz[v]);

        if (maxSz)
        {
            bool done = 0;
            for (auto &v: adj[u])
                if (v == par[u])
                    continue;
                else if (sz[v] == maxSz && !done)
                    decompose(v, cnt + 1), done = 1;
                else
                    decompose(v, 1);
        }
        else
        {
            ll r = data.size() + cnt - 1, hd = u;
            for (ll i{1}; i < cnt; i++, hd = par[hd]);
            for (ll cu = u, i{}; i < cnt; cu = par[cu], i++)
            {
                data.pb(val[cu]);
                pos[cu] = data.size() - 1;
                right[cu] = r, head[cu] = hd;
            }
        }
    }
    T query(ll u, ll v)
    {
        T res = T();
        while (1)
        {
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            if (right[u] == right[v])
            {
                if (pos[u] > pos[v])
                    swap(u, v);
                res = merge(res, tree.get(pos[u], pos[v]));
                break;
            }
            res = merge(res, tree.get(pos[u], right[u]));
            u = par[head[u]];
        }
        return res;
    }
    void set(ll u, T val){ tree.set(pos[u], val); }
};


template<class T, class M, class Op, class A>
struct LazyHLD
{
    ll n;
    M merge;
    vvll adj;
    vector<T> val, data;
    vll dep, sz, par, right, head, pos;
    LazySegTree<T, M, Op, A> tree;
    LazyHLD(vvll &adj, vector<T> val, ll root = 1)
    : adj(adj), val(val), n(adj.size())
    {
        dep.resize(n);
        sz.resize(n);
        par.resize(n);
        right.resize(n);
        head.resize(n);
        pos.resize(n);
        data.reserve(n);
        dfs(root);
        decompose(root);
        tree = LazySegTree<T, M, Op, A>(data);
    }
    // same as before
    void modify(ll u, ll v, Op op)
    {
        while (1)
        {
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            if (right[u] == right[v])
            {
                if (pos[u] > pos[v])
                    swap(u, v);
                tree.modify(pos[u], pos[v], op);
                break;
            }
            tree.modify(pos[u], right[u], op);
            u = par[head[u]];
        }
    }
};