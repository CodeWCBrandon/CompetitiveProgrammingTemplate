struct Treap{
    struct Node{
        ll priority, key, sz;

        ll sum = 0;
        ll lazyAdd = 0;
        bool rev = false;
        Node *left, *right;
        Node(ll key)
        {
            this->priority = rng();
            this->key = key;
            this->sum = key;
            this->sz = 1;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    ll getSz(Node* curr)
    {
        return ((curr) ? curr->sz : 0);
    }

    ll getSum(Node* curr)
    {
        return ((curr) ? curr->sum : 0);
    }

    void insert(Node*& root, ll pos, ll val)
    {
        auto [left, right] = split(root, pos);
        root = merge(left, merge(new Node(val), right));
    }

    void update(Node* curr)
    {
        if(curr == nullptr) return;
        curr->sz = 1 + getSz(curr->left) + getSz(curr->right);
        curr->sum = curr->key + getSum(curr->left) + getSum(curr->right); 
    }

    void checkPropagate(Node* curr, ll add, bool rev)
    {
        if(!curr) return;
        curr->key += add;
        curr->sum += (add * getSz(curr));
        curr->lazyAdd += add;
        curr->rev ^= rev; 

        if(rev)
        {
            swap(curr->left, curr->right);
        }
    }

    void push(Node* curr)
    {
        checkPropagate(curr->left, curr->lazyAdd, curr->rev);
        checkPropagate(curr->right, curr->lazyAdd, curr->rev);
        curr->lazyAdd = 0;
        curr->rev = false;
    }

    pair<Node*, Node*> split(Node* curr, ll x)
    {
        if(curr == nullptr) return {nullptr, nullptr};
        push(curr);
        ll leftSz = getSz(curr->left);
        if(leftSz >= x)
        {
            auto [left, mid] = split(curr->left, x);
            curr->left = mid;
            update(curr);
            return {left, curr};
        }else
        {
            auto [mid, right] = split(curr->right, x - leftSz - 1);
            curr->right = mid;
            update(curr);
            return {curr, right};
        }
    }

    Node* merge(Node* left, Node* right)
    {
        if(!left) return right;
        if(!right) return left;

        push(left);
        push(right);
        if(left->priority < right->priority)
        {
            left->right = merge(left->right, right);
            update(left);
            return left;
        }else{
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }

    ll rangeSumQuery(Node*& root, ll l, ll r)
    {
        auto [leftEnd, rightSide] = split(root, l);
        auto [mid, rightEnd] = split(rightSide, (r - l + 1));

        ll res = getSum(mid);

        root = merge(leftEnd, merge(mid, rightEnd));

        return res;
    }

    void rangeSumUpdate(Node*& root, ll l, ll r, ll val)
    {
        auto [leftEnd, rightSide] = split(root, l);
        auto [mid, rightEnd] = split(rightSide, (r - l + 1));

        checkPropagate(mid, val, false);

        root = merge(leftEnd, merge(mid, rightEnd));
    }

    void rangeReverse(Node*& root, ll l, ll r)
    {
        auto [leftEnd, rightSide] = split(root, l);
        auto [mid, rightEnd] = split(rightSide, (r - l + 1));

        checkPropagate(mid, 0, true);
        root = merge(leftEnd, merge(mid, rightEnd));
    }

    void debug(Node* curr)
    {
        if(!curr) return;
        push(curr);

        debug(curr->left);
        cout << curr->key << " ";
        debug(curr->right);
    }
};
