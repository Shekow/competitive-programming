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

struct BiTrie
{
    vvll nodes;
    vll cnt;
    ll MSB;
    BiTrie(ll MSB): MSB(MSB){ addNode(), modify(0, 1); }
    void addNode(){ nodes.pb(vll(2, -1)), cnt.pb(0); }
    void modify(ll val, ll diff)
    {
        ll idx = 0;
        cnt[0] += diff;
        for (ll i{MSB}; i >= 0; i--)
        {
            bool bit = (val >> i) & 1;
            if (nodes[idx][bit] == -1)
                addNode(), nodes[idx][bit] = cnt.size() - 1;
            idx = nodes[idx][bit];
            cnt[idx] += diff;
        }
    }
    bool exists(ll idx, bool bit)
    { 
        return ~nodes[idx][bit] && cnt[nodes[idx][bit]];
    }
    ll getXor(ll val, bool maxi = 1)
    {
        ll res = 0, idx = 0;
        for (ll i{MSB}; i >= 0; i--)
        {
            bool bit = (val >> i) & 1;
            if (!exists(idx, bit) || (maxi && exists(idx, !bit)))
                bit ^= 1, res ^= (1ll << i);
            idx = nodes[idx][bit];
        }
        return res;
    }
};