struct CartesianTree{
    struct Node{
        ll val;
        ll left, right;
    };

    vector<Node> tree;
    ll root = -1;
    CartesianTree(vector<ll>& a)
    {
        ll n = a.size();
        tree.resize(n);
        vector<ll> st;

        for(int i = 0; i < n; ++i)
        {
            tree[i] = {a[i], -1, -1};
            ll last = -1;

            while(!st.empty() && a[st.back()] <= a[i])
            {
                last = st.back();
                st.pop_back();
            }

            if(!st.empty())
            {
                tree[st.back()].right = i;
            }
            tree[i].left = last;
            st.push_back(i);
        }
        root = st.front();
    }

};
