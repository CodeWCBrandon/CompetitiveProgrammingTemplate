struct Trie
{
    struct Node
    {
        int next[26];
        ll freq;

        Node()
        {
            for(int i = 0; i < 26; ++i) next[i] = -1;
            freq = 0;
        }
    };

    vector<Node> tr;

    Trie()
    {
        tr.push_back(Node());
    }

    ll newNode()
    {
        tr.push_back(Node());
        return tr.size() - 1;
    }

    void insert(string& a)
    {
        ll curr = 0;
        for(int i = 0; i < a.size(); ++i)
        {
            ll val = (a[i] - 'a');
            if(tr[curr].next[val] == -1)
            {
                tr[curr].next[val] = newNode();
            }
            curr = tr[curr].next[val];
            tr[curr].freq++;
        }
    }
};
