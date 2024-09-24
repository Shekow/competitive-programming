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

template<class T, class F>
struct PersistentSegTree
{
    struct Node
    {
        F merge;
        Node *l, *r;
        T val;
        Node(T val): val(val), l(NULL), r(NULL){}
        Node(Node *l, Node* r): val(), l(l), r(r)
        {
            if (l)
                val = merge(val, l->val);
            if (r)
                val = merge(val, r->val);
        }
    };
    ll n;
    F merge;
    vector<Node *> history;
    PersistentSegTree(vector<T> data): n(data.size())
    {
        history.pb(build(data, 0, n - 1));
    }
    Node *build(vector<T> &data, ll l, ll r)
    {
        if (l == r)
            return new Node(data[l]);
        ll m = (l + r) / 2;
        return new Node(build(data, l, m), build(data, m + 1, r));
    }
    Node *set(Node *v, ll l, ll r, ll pos, T val)
    {
        if (l == r)
            return new Node(val); 
        ll m = (l + r) / 2;
        if (pos <= m)
            return new Node(set(v->l, l, m, pos, val), v->r);
        return new Node(v->l, set(v->r, m + 1, r, pos, val));
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        if (l == tl && r == tr)
            return v->val;
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    // op: sum
    ll getKth(Node *vl, Node *vr, ll l, ll r, ll k)
    {
        if (l == r)
            return l;
        ll m = (l + r) / 2, left = vr->l->val - vl->l->val;
        if (left >= k)
            return getKth(vl->l, vr->l, l, m, k);
        return getKth(vl->r, vr->r, m + 1, r, k - left);
    }
    void set(ll pos, T val)
    {
        history.pb(set(history.back(), 0, n - 1, pos, val));
    }
    T get(ll l, ll r, ll h){ return get(history[h], 0, n - 1, l, r); }
    T get(ll l, ll r){ return get(history.back(), 0, n - 1, l, r); }
    ll getKth(ll l, ll r, ll k)
    { 
        return getKth(history[l], history[r + 1], 0, n - 1, k);
    }
};