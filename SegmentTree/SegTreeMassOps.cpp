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

template<class T, class M, class Op, class A>
struct SegTree
{
    vector<T> seg;
    vector<Op> ops;
    ll n;
    M merge;
    A apply;
    void propegate(ll v, ll l, ll r)
    {
        if (r - l <= 0)
            return;
        ops[v * 2].apply(ops[v]);
        seg[v * 2] = apply(seg[v * 2], ops[v]);
        ops[v * 2 + 1].apply(ops[v]);
        seg[v * 2 + 1] = apply(seg[v * 2 + 1], ops[v]);
        ops[v] = Op();
    }
    void build(vector<T> &data, ll v, ll l, ll r)
    {
        if (l == r)
        {
            seg[v] = data[l];
            return;
        }
        ll m = (l + r) / 2;
        build(data, v * 2, l, m);
        build(data, v * 2 + 1, m + 1, r);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
    void modify(ll v, ll l, ll r, ll tl, ll tr, Op op)
    {
        propegate(v, l, r);
        if (tl > tr)
            return;
        if (l == tl && r == tr)
        {
            ops[v].apply(op);
            seg[v] = apply(seg[v], op);
            return;
        }
        ll m = (l + r) / 2;
        modify(v * 2, l, m, tl, min(tr, m), op);
        modify(v * 2 + 1, m + 1, r, max(tl, m + 1), tr, op);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
    T get(ll v, ll l, ll r, ll tl, ll tr)
    {
        propegate(v, l, r);
        if (tl > tr)
            return T();
        if (l == tl && r == tr)
            return seg[v];
        ll m = (l + r) / 2;
        return merge(
            get(v * 2, l, m, tl, min(tr, m)),
            get(v * 2 + 1, m + 1, r, max(tl, m + 1), tr)
        );
    }
    ll getKth(ll v, ll l, ll r, ll k)
    {
        propegate(v, l, r);
        if (l == r)
            return (k == 1 ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= k)
            return getKth(v * 2, l, m, k);
        return getKth(v * 2 + 1, m + 1, r, k - seg[v * 2]);  
    }
    ll getLB(ll v, ll l, ll r, ll tl, ll tr, ll val)
    {
        propegate(v, l, r);
        if (tl > tr)
            return -1;
        if (l == r)
            return (seg[v] >= val ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= val)
        {
            ll res = getLB(v * 2, l, m, tl, min(tr, m), val);
            if (~res)
                return res;
        }
        return getLB(v * 2 + 1, m + 1, r, max(tl, m + 1), tr, val);
    }
    SegTree(vector<T> data): n(data.size())
    {
        seg.assign(n * 4, T());
        ops.assign(n * 4, Op());
        build(data, 1, 0, n - 1);
    }
    void modify(ll l, ll r, Op op)
    {
        modify(1, 0, n - 1, l, r, op);
    }
    T get(ll l, ll r)
    {
        return get(1, 0, n - 1, l, r);
    }
    ll getKth(ll k)
    {
        return getKth(1, 0, n - 1, k + 1);
    }
    ll getLB(ll l, ll r, ll x)
    {
        return getLB(1, 0, n - 1, l, r, x);
    }
};

struct Seg
{
    ll val;
    Seg(): Seg(-1e18){}
    Seg(ll val): val(val){}
    operator ll()
    {
        return val;
    }
};

struct Merge
{
    Seg operator()(Seg a, Seg b)
    {
        return Seg(max(a.val, b.val));
    }
};

struct Op
{
    ll op;
    Op(): Op(0){}
    Op(ll op): op(op){}
    void apply(Op other)
    {
        op += other.op;
    }
};

struct Apply
{
    Seg operator()(Seg a, Op b)
    {
        return Seg(a.val + b.op);
    }
};