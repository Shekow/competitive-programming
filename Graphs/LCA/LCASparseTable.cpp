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
typedef vector<vvs> vvvs;
typedef set<ll> sll;
typedef set<sll> ssll;
typedef set<pll> spll;
typedef set<spll> sspll;
typedef set<string> ss;
typedef set<ss> sss;
typedef map<ll, ll> mll;

template<class T, class F>
struct SparseTable
{
    vector<vector<T>> pre;
    vector<ll> lg;
    ll n;
    F merge;
    SparseTable() = default;
    SparseTable(vector<T> data): n(data.size())
    {
        lg = vector<ll>(n + 1);
        for (ll i{2}; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        pre = vector<vector<T>>(n, vector<T>(lg[n] + 1));

        for (ll i{}; i < n; i++)
            pre[i][0] = data[i];
        for (ll p{1}; p <= lg[n]; p++)
            for (ll i{}; i + (1 << p) - 1 < n; i++)
                pre[i][p] = merge(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
    }
    T range(ll a, ll b)
    {
        T res;
        bool start{true};
        for (ll rem{b - a + 1}, i{a}, p{lg[rem]}; rem > 0; i += (1 << p), rem -= (1 << p), p = lg[rem])
            res = (start ? pre[i][p] : merge(res, pre[i][p])), start = false;
        return res;
    }
    T rangeOL(ll a, ll b)
    {
        ll p = lg[b - a + 1];
        return merge(pre[a][p], pre[b - (1 << p) + 1][p]);
    }
};

struct LCA
{
    struct Min
    {
        pll operator()(pll a, pll b)
        {
            return (a.second < b.second ? a : b);
        }
    };
 
    SparseTable<pll, Min> table;
    vector<ll> pos, depth;
    vector<pll> euler;
    ll n;
 
    LCA(vector<vector<ll>> &adj, ll root = 1): n(adj.size())
    {
        pos = depth = vector<ll>(n);
        dfs(adj, root);
        table = SparseTable<pll, Min>(euler);
    }
    void dfs(vector<vector<ll>> &adj, ll node = 1, ll par = -1, ll dep = 0)
    {
        pos[node] = euler.size();
        depth[node] = dep;
        euler.pb({node, dep});
        for (each e: adj[node])
            if (e != par)
                dfs(adj, e, node, dep + 1), euler.pb({node, dep});
    }
    ll query(ll u, ll v)
    {
        u = pos[u];
        v = pos[v];
        if (u > v)
            swap(u, v);
        return table.rangeOL(u, v).first;
    }
    ll distance(ll u, ll v)
    {
        ll d = depth[query(u, v)];
        return depth[u] + depth[v] - d * 2;
    }
};