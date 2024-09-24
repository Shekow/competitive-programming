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

ll sum(ll n){ return n * (n + 1) / 2; }
ll sumo(ll n){ return  n * n;}
ll sume(ll n){ return n * (n + 1); }
ll sum2(ll n){ return n * (n + 1) * (2 * n + 1) / 6; }
ll sum2o(ll n){ return n * (2 * n + 1) * (2 * n - 1) / 3; }
ll sum2e(ll n){ return 2 * n * (n + 1) * (2 * n + 1) / 3; }

ll xorSum(ll n)
{
    switch (n % 4)
    {
        case 0: 
            return n;
        case 1:
            return 1;
        case 2:
            return n + 1;
        default:
            return 0;
    }
}

ll xorSum(ll l, ll r){ return xorSum(r) ^ xorSum(l - 1); }

ll nim(vll v)
{
    sll st(all(v));
    v.assign(all(st));
    for (ll last{}, i{}; i < v.size(); last = v[i++])
        if (v[i] - last > 1)
            return i;
    return v.size() - 1;
}

ll getMEX(vll v)
{
    v.pb(-1), v.pb(1e18);
    sort(all(v));
    for (ll i{1};; i++)
        if (v[i] - v[i - 1] > 1)
            return v[i - 1] + 1;
}

void euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
        x = 1, y = 0;
    else
        euclid(b, a % b, x, y), tie(x, y) = make_tuple(y, x - y * (a / b));
}

struct Matrix
{
    static const ll SZ = 2;
    vvll mat;
    Matrix(): mat(SZ, vll(SZ))
    {
        for (ll i{}; i < SZ; i++)
            mat[i][i] = 1;
    }
    Matrix(vvll mat): mat(mat){}
    Matrix operator=(Matrix oth){ this->mat = oth.mat; return *this; }
    Matrix operator*(Matrix oth)
    {
        vvll res(SZ, vll(SZ));
        for (ll i{}; i < SZ; i++)
            for (ll j{}; j < SZ; j++)
                for (ll k{}; k < SZ; k++)
                    res[i][j] += mat[i][k] * oth.mat[k][j];
        return res;
    };
    Matrix operator%(ll mod)
    {
        for (ll i{}; i < SZ; i++)
            for (ll j{}; j < SZ; j++)
                mat[i][j] %= mod;
        return *this;
    }
};

Matrix fastPow(Matrix mat, ll p, ll m = 1e9 + 7)
{
    if (p == 0)
        return Matrix();
    Matrix res = fastPow(mat, p / 2, m);
    res = (res * res) % m;
    if (p & 1)
        res = (res * mat) % m;
    return res;
}

ll maxHistogramArea(vll v)
{
    vll st;
    v.pb(0);
    ll res = 0, n = v.size();
    for (ll i{}; i < n; i++)
    {
        while (!st.empty() && v[st.back()] > v[i])
        {
            ll cu = st.back();
            st.popb();
            res = max(res, v[cu] * (st.empty() ? i : i - st.back() - 1));
        }
        st.pb(i);
    }
    return res;
}

string infixToPostfix(string s)
{
    map<char, ll> prec{
        {'*', 0}, {'/', 0}, {'+', 1}, {'-', 1} , {'(', 1e18} 
    };
    string sol, st;
    for (auto &c: s)
    {
        if (isdigit(c))
            sol.pb(c);
        else if (c == '(')
            st.pb(c);
        else if (c == ')')
        {
            while (st.back() != '(')
                sol.pb(st.back()), st.popb();
            st.popb();
        }
        else
        {
            while (!st.empty() && prec[st.back()] <= prec[c])
                sol.pb(st.back()), st.popb();
            st.pb(c);
        }
    }
    while (!st.empty())
        sol.pb(st.back()), st.popb();
    return sol;
}


ld dis(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

ld mag(pll v)
{
    return sqrt(v.first * v.first + v.second * v.second);
}

ll dot(pll x, pll y)
{
    return x.first * y.first + x.second * y.second;
}

ld cross(pll x, pll y)
{
    return mag(x) * mag(y);
}

ld angleBetVectors(pll x, pll y)
{
    return (acos(dot(x, y) / cross(x, y))) / (2 * acos(0)) * 180;
}