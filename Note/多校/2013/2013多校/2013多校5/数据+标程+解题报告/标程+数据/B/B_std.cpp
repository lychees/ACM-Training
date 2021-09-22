#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int N = 26;
const int M = 1000010;
int pre[M];
char buffer[M];
void buildkmp(const string& mch)
{
    int i = 1 , j = -1;
    pre[0] = -1;
    while(i < mch.size())
    {
        while( j>=0 && mch[j + 1] != mch[i] )
            j = pre[j];
        if(mch[j+1] == mch[i])
            j++;
        pre[i] = j;
        i ++;
    }
}
bool kmp(const string& str,const string& mch)
{
    int i = 0, j = -1;
    while(i < str.size())
    {
        while( j>=0 && mch[j + 1] != str[i] )
            j = pre[j];
        if(mch[j+1] == str[i])
            j ++;
        if(j == mch.size() - 1)
        {
            j = pre[j];
            return true;
        }
        i++;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    string bwt;
    while(scanf("%s",buffer) == 1)
    {
        bwt = buffer;
        vector<int> vf[N];
        vector<int> vbwt[N];
        vector<int> mbwt(bwt.size() , 0);

        string sorted = bwt;
        sort(sorted.begin(),sorted.end());
        for(int i = 0 ;i < bwt.size() ; i ++)
        {
            if(bwt[i] != '$')
            {
                mbwt[ i ] = vbwt[ bwt[i] - 'a' ].size();
                vbwt[ bwt[i] - 'a' ].push_back(i);
            }
        }
        for(int i = 0 ;i < sorted.size() ; i ++)
        {
            if(sorted[i] != '$')
            {
                vf[ sorted[i] - 'a' ].push_back(i);
            }
        }
        string T;
        char ch = bwt[0];
        int od = 0;
        for(int i = 1 ;i < bwt.size() ; i ++)
        {
            T += ch;
            int lft = vf[ch - 'a'][od];
            ch = bwt[lft];
            od = mbwt[lft];
        }
        reverse(T.begin(),T.end());
        //cout << T << endl;
        int q;
        //cin >> q;
        scanf("%d",&q);
        while(q--)
        {
            string test;
            //cin >> test;
            scanf("%s",buffer);
            test = buffer;
            buildkmp(test);
            if(kmp(T,test))
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }
    return 0;
}

