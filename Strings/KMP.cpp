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

vll prefixFn(string s)
{
    ll n = s.size();
    vll pi(n);
    for (ll i{1}; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        j += (s[i] == s[j]);
        pi[i] = j;
    }
    return pi;
}

vvll buildAuto(string s)
{
    vvll bigPi(s.size() + 1, vll(26));
    string t = s + "#" + s;
    ll n = t.size();
    vll pi = prefixFn(t);
 
    for (ll i = s.size() + 1, len = 0; i <= n; i++, len++)
    {
        for (ll c = 0; c < 26; c++)
        {
            char ch = c + 'a';
            ll j = pi[i - 1];
            while (j > 0 && ch != s[j])
                j = pi[j - 1];
            j += (ch == s[j]);
            bigPi[len][c] = j;
        }
    }
    return bigPi;
}