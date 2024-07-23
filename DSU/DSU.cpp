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

struct DSU
{
    vll par, rank;
    ll sz, comps;
    DSU(ll n) : sz(n)
    {
        par = rank = vll(sz + 1);
        for (ll i{1}; i <= sz; i++)
            par[i] = i;
        comps = n;
    }
    ll get(ll a)
    {
        return par[a] = (par[a] == a ? a : get(par[a]));
    }
    bool unite(ll a, ll b)
    {
        a = get(a), b = get(b);
        if (a == b)
            return false;
        if (rank[a] == rank[b]) 
            rank[a]++;
        if (rank[a] < rank[b]) 
            swap(a, b);
        par[b] = a;
        comps--;
        return true;
    }
};
