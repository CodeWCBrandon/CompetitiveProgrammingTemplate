struct Dinic{
    struct edge{
        ll u, v;
        ll flow, capacity;

        edge(ll u, ll v, ll cap)
        {
            this->u = u;
            this->v = v;
            this->flow = 0;
            this-> capacity = cap;
        }
    };
    vector<edge> edgeList;
    vector<vector<ll>> adjList;
    vector<ll> level;
    vector<ll> nextID;
    ll n, s, t;
    ll currID = 0;

    Dinic(ll n, ll s, ll t)
    {
        this->n = n;
        this->s = s;
        this->t = t;

        adjList.resize(n);
        level.resize(n);
        nextID.resize(n);
    }

    void addEdge(ll u, ll v, ll cap)
    {
        edgeList.push_back(edge(u, v, cap));
        edgeList.push_back(edge(v, u, 0));

        adjList[u].push_back(currID);
        adjList[v].push_back(currID + 1);
        currID += 2;
    }

    bool bfs()
    {
        level.assign(n, -1);
        queue<ll> q;
        q.push(s);
        level[s] = 0;

        while(!q.empty())
        {
            ll curr = q.front(); q.pop();

            for(auto next : adjList[curr])
            {
                auto& [u, v, flow, capacity] = edgeList[next];
                ll available = capacity - flow;
                if(available == 0 || level[v] != -1) continue;
                level[v] = level[u] + 1;
                q.push(v); 
            }
        }

        return level[t] != -1;
    }

    ll dfs(ll curr, ll bottleneck)
    {
        if(curr == t) return bottleneck;
        for(ll& i = nextID[curr]; i < adjList[curr].size(); ++i)
        {
            ll id = adjList[curr][i];
            auto& [u, v, flow, capacity] = edgeList[id];
            ll available = capacity - flow;
            if(available == 0 || level[v] <= level[u]) continue;
            ll nextFlow = dfs(v, min(bottleneck, available));

            if(nextFlow == 0) continue;
            edgeList[id].flow += nextFlow;
            edgeList[id ^ 1].flow -= nextFlow;

            return nextFlow;
        }

        return 0;
    }

    ll maxFlow()
    {
        ll mxFlow = 0;
        while(true)
        {
            if(!bfs()) break;
            nextID.assign(n, 0);
            while(true)
            {
                ll flow = dfs(s, 1e18);
                if(flow == 0) break;
                mxFlow += flow;
            }
        }

        return mxFlow;
    }

    vector<pair<ll, ll>> cutEdges()
    {
        queue<ll> q;
        q.push(s);

        vector<bool> sourceCC(n, false);
        sourceCC[s] = true;

        while(!q.empty())
        {
            ll curr = q.front(); q.pop();

            for(auto next : adjList[curr])
            {
                auto& [u, v, flow, capacity] = edgeList[next];
                ll available = capacity - flow;
                if(available == 0 || sourceCC[v] == true) continue;
                sourceCC[v] = true;
                q.push(v);
            }
        }

        vector<pair<ll, ll>> ret;
        vector<ll> taken(n, -1);
        for(int i = 0; i < n; ++i)
        {
            if(!sourceCC[i]) continue;
            for(auto next : adjList[i])
            {
                auto& [u, v, flow, capacity] = edgeList[next];
                if(!sourceCC[v] && taken[v] != i)
                {
                    ret.push_back({u, v});
                    taken[v] = i;
                }
            }
        }

        return ret;
    }
};
