ll fastExpo(ll a, ll b, ll m)
{
    if(b == 0) return 1;
    if(b == 1) return a;
    if(b % 2 == 0) return fastExpo((a * a) % m, b / 2, m);
    else return (a * fastExpo((a * a) % m, b / 2, m)) % m;
}

struct hashedString
{
    ll p, m;
    vector<ll> hashValue;
    vector<ll> power, invPower;

    hashedString(ll p, ll m, string s)
    {
        this->p = p;
        this->m = m;
        hashValue.assign(s.size(), 0);
        power.assign(s.size() + 5, 0);
        invPower.assign(s.size() + 5, 0);

        ll currentPower = 1;
        for(int i = 0; i <= s.size(); ++i)
        {
            power[i] = currentPower;
            currentPower = (currentPower * p) % m;
        }

        invPower[s.size()] = fastExpo(power[s.size()], m - 2, m);
        for(int i = s.size() - 1; i >= 0; --i)
        {
            invPower[i] = (invPower[i + 1] * p) % m;
        }
     
        ll currentVal = 0;
        ll currMul = 1;
        for(int i = 0; i < s.size(); ++i)
        {
            currentVal += (((s[i] - 'a') + 1) * currMul) % m; currentVal %= m;
            currMul = (currMul * p) % m;
            hashValue[i] = currentVal;
        }
    }

    ll getHashValue(ll l, ll r)
    {
        ll res = hashValue[r];
        if(l > 0) res = ((hashValue[r] - hashValue[l - 1]) + m) % m;

        res = (res * invPower[l]) % m;
        return res;
    }
};

struct hashCheck
{
    vector<vector<hashedString>> saved;

    ll p = 31;
    void addString(string& s, vector<ll>& mods)
    {
        saved.push_back(vector<hashedString>());
        for(auto m : mods)
        {
            hashedString temp(p, m, s);
            saved[saved.size() - 1].push_back(temp);
        }
    }

    bool check(ll firstIdx, ll secondIdx, ll lf, ll rf, ll ls, ll rs)
    {
        if(rf - lf != rs - ls) return false;
        for(int i = 0; i < saved[firstIdx].size(); ++i)
        {
            ll firstHashValue = saved[firstIdx][i].getHashValue(lf, rf);
            ll secondHashValue = saved[secondIdx][i].getHashValue(ls, rs);

            if(firstHashValue != secondHashValue) return false;
        }
        return true;
    }
};
