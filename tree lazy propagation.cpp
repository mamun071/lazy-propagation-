#include<bits/stdc++.h>
using namespace std;

#define mx 1000009
long long int ar[mx];
long long int tree[3*mx],lazy[3*mx];

void make_tree(long long int node,long long int s,long long int e)
{
    if(s==e)
    {
        tree[node]=ar[s];
        return;
    }
    int mid=(s+e)/2;
    int left=node*2;
    int right=node*2+1;
    make_tree(left,s,mid);
    make_tree(right,mid+1,e);
    tree[node]=tree[left]+tree[right];
}

void updateRange(long long int node,long long int start,long long int end,long long int l,long long int r,long long int val)
{
    if(lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > end or start > r or end < l)
        return;
    if(start >= l and end <= r)
    {
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int queryRange(long long int node,long long int start,long long int end,long long int l,long long int r)
{
    if(start > end or start > r or end < l)
        return 0;
    if(lazy[node] != 0)
    {

        tree[node] += (end - start + 1) * lazy[node];
        if(start != end)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start >= l and end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);
    int p2 = queryRange(node*2 + 1, mid + 1, end, l, r);
    return (p1 + p2);
}

main()
{
    long long int n,c,p,v,q;
    int t;
    scanf("%d",&t);
    //t--;
    while(t--)
    {

        memset(ar,0,sizeof ar);
        memset(lazy,0,sizeof lazy);
        memset(tree,0,sizeof tree);
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)
            ar[i]=0,lazy[i]=0;
        make_tree(1,1,n);
        scanf("%lld",&c);
        while(c--)
        {
            int flag;
            cin>>flag;
            if(flag==0)
            {
                //int p,q,v;
                scanf("%lld%lld%lld",&p,&q,&v);
                updateRange(1,1,n,p,q,v);
            }
            else
            {
                scanf("%lld%lld",&p,&q);
                cout<<queryRange(1,1,n,p,q)<<endl;
            }
        }
    }
}
/*void update_range(int node,int s,int e,int l,int r,int val)
{
    if(lazy[node]!=0)
    {
        tree[node]+=(e-s+1)*lazy[node];
        if(s!=e)
        {
            tree[node*2]+=lazy[node];
            tree[node*2+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    if(s>e or r<s or e>l)
        return;
    if(l>=s and r<=e)
    {
        tree[node]+=(e-s+1)*lazy[node];
        if(s!=e)
        {
            tree[node*2]+=lazy[node];
            tree[node*2+1]+=lazy[node];
        }
        return;
    }
    int mid=(s+e)/2;
    int left=node*2;
    int right=node*2+1;
    update_range(left,s,mid,l,r,val);
    make_tree(right,mid+1,e,l,r,val);
    tree[node]=tree[left]+tree[right];
}

int query(int node,int s,int e,int l,int r)
{
     if(s>e or r<s or e>l)
        return;
    if(lazy[node]!=0)
    {
        tree[node]+=(e-s+1)*lazy[node];
        if(s!=e)
        {
            tree[node*2]+=lazy[node];
            tree[node*2+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    if(l>=s and r<=e)
    {
        return tree[node];
    }
    int mid=(s+e)/2;
    int left=node*2;
    int right=node*2+1;
    int p1=query(left,s,mid,l,r);
    int p2=query(right,mid+1,e,l,r);
    //tree[node]=tree[left]+tree[right];
    return p1+p2;
}*/



