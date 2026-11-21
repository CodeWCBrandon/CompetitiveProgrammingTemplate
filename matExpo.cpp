vector<vector<ll>> matmul(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    vector<vector<ll>> res (a.size(), vector<ll>(b[0].size(), 0));
    for (ll i = 0; i < a.size(); i++)
    {
        for (ll j = 0; j < b[0].size(); j++)
        {
            for (ll k = 0; k < a[0].size(); k++)
            {
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]));
            }
        }
    }
    return res;
}

vector<vector<ll>> matpow(vector<vector<ll>> a, ll b)
{
    vector<vector<ll>> res(a.size(), vector<ll>(a.size(), 0));
    for (ll i = 0; i < a.size(); i++)
    {
        res[i][i] = 1;
    }

    while (b > 0)
    {
        if (b & 1)
        {
            res = matmul(res, a);
        }
        a = matmul(a, a);
        b >>= 1;
    }
    return res;
}
