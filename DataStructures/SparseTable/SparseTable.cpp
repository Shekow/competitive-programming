#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vector<ll>> vvll;
typedef vector<vector<pll>> vvpll;
typedef map<ll, ll> mll;
typedef set<ll> sll;

template<class T, class F>
struct SparseTable
{
    vector<vector<T>> pre;
    vll lg;
    ll n;
    F merge;

    SparseTable() = default;
    SparseTable(vector<T> data): n(data.size())
    {
        lg.resize(n + 1);
        for (ll i{2}; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        pre.assign(n, vector<T>(lg[n] + 1));

        for (ll i{}; i < n; i++)
            pre[i][0] = data[i];
        for (ll p{1}; p <= lg[n]; p++)
            for (ll i{}; i + (1 << p) - 1 < n; i++)
                pre[i][p] = merge(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
    }
    T query(ll a, ll b)
    {
        T res;
        bool start{true};
        for (ll rem{b - a + 1}, i{a}, p{lg[rem]}; rem > 0; i += (1 << p), rem -= (1 << p), p = lg[rem])
            res = (start ? pre[i][p] : merge(res, pre[i][p])), start = false;
        return res;
    }
    T queryOL(ll a, ll b)
    {
        ll p = lg[b - a + 1];
        return merge(pre[a][p], pre[b - (1 << p) + 1][p]);
    }
};

struct Seg
{
    ll val;
};

struct Merge
{
    Seg operator()(Seg a, Seg b)
    {
        return Seg{
            min(a.val, b.val)
        };
    }
};