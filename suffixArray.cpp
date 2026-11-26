struct SuffixArray{
    vector<ll> arr, lcp;
    ll sz;

    void radixSort(vector<pair<pair<ll, ll>, ll>>& a)
    {
        auto sortPass = [&](bool byFirst) 
        {
            vector<ll> cnt(sz, 0);
            for (auto& item : a)
            {
                ll key = byFirst ? item.first.first : item.first.second;
                cnt[key]++;
            }

            vector<ll> pos(sz, 0);
            ll currIdx = 0;
            for (ll i = 0; i < sz; ++i)
            {
                pos[i] = currIdx;
                currIdx += cnt[i];
            }

            vector<pair<pair<ll, ll>, ll>> sortedA(sz);
            for (auto& item : a)
            {
                ll key = byFirst ? item.first.first : item.first.second;
                sortedA[pos[key]++] = item;
            }

            a = std::move(sortedA);
        };

        sortPass(false); 
        sortPass(true); 
    }

    SuffixArray(string s)
    {
        s += '\$';
        this->sz = s.size();
        vector<ll> c(sz);
        arr.resize(sz);

        vector<pair<ll, ll>> initial(sz);
        for(int i = 0; i < sz; ++i)
        {
            initial[i] = {s[i], i};
        }
        sort(initial.begin(), initial.end());
        c[initial[0].second] = 0;
        for(int i = 1; i < sz; ++i)
        {
            if(initial[i].first == initial[i - 1].first) 
            {
                c[initial[i].second] = c[initial[i - 1].second];
            }else{
                c[initial[i].second] = c[initial[i - 1].second] + 1;
            }
        }

        ll k = 1;
        while(k < sz)
        {
            vector<pair<pair<ll, ll>, ll>> followUp(sz);
            for(int i = 0; i < sz; ++i)
            {
                followUp[i] = {{c[i], c[(i + k) % sz]}, i}; 
            }
            radixSort(followUp);
            c[followUp[0].second] = 0;
            for(int i = 1; i < sz; ++i)
            {
                if(followUp[i].first == followUp[i - 1].first)
                {
                    c[followUp[i].second] = c[followUp[i - 1].second];
                }else{
                    c[followUp[i].second] = c[followUp[i - 1].second] + 1;
                }
            }
            k <<= 1;
            if(c[followUp.back().second] == sz - 1 || k >= sz)
            {
                for(int i = 0; i < sz; ++i) arr[i] = followUp[i].second;
                break;
            }
        }
        buildLCP(s);
    }

    void buildLCP(string s) 
    {
        lcp.assign(sz, 0);
        vector<ll> rank(sz, 0);
        for (ll i = 0; i < sz; ++i) 
        {
            rank[arr[i]] = i;
        }

        ll k = 0;
        for (ll i = 0; i < sz; ++i) 
        {
            if (rank[i] == 0) 
            {
                k = 0;
                continue;
            }
            ll j = arr[rank[i] - 1];
            while (i + k < sz && j + k < sz && s[i + k] == s[j + k]) 
            {
                ++k;
            }
            lcp[rank[i] - 1] = k;
            if (k > 0) --k;
        }
    }
};
