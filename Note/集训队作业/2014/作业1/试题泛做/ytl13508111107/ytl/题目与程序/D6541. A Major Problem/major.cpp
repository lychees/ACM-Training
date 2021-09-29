#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

string diao[15][8]={
{"C","D","E","F","G","A","B","C"},
{"G","A","B","C","D","E","F#","G"},
{"D","E","F#","G","A","B","C#","D"},
{"A","B","C#","D","E","F#","G#","A"},
{"E","F#","G#","A","B","C#","D#","E"},
{"B","C#","D#","E","F#","G#","A#","B"},
{"F#","G#","A#","B","C#","D#","E#","F#"},
{"C#","D#","E#","F#","G#","A#","B#","C#"},
{"F","G","A","Bb","C","D","E","F"},
{"Bb","C","D","Eb","F","G","A","Bb"},
{"Eb","F","G","Ab","Bb","C","D","Eb"},
{"Ab","Bb","C","Db","Eb","F","G","Ab"},
{"Db","Eb","F","Gb","Ab","Bb","C","Db"},
{"Gb","Ab","Bb","Cb","Db","Eb","F","Gb"},
{"Cb","Db","Eb","Fb","Gb","Ab","Bb","Cb"}
};

int find(string &a){
    for (int i=0;i<15;i++) if (diao[i][0]==a) return i;
    return -1;
}
int look(int t,string &a){
    for (int i=0;i<8;i++) if (diao[t][i]==a) return i;
    return -1;
}

string a,b,c[1000];
int main(){
	freopen("major.in","r",stdin);
	freopen("major.out","w",stdout);
    while (cin>>a&&a!="*"){
        cin>>b;
        int tot=0;
        cin>>c[++tot];
        while (c[tot]!="*") cin>>c[++tot];
        tot--;
        int t1=find(a);
        if (t1==-1){
            cout<<"Key of "<<a<<" is not a valid major key"<<endl<<endl;
            continue;
        }
        int t2=find(b);
        if (t2==-1){
            cout<<"Key of "<<b<<" is not a valid major key"<<endl<<endl;
            continue;
        }
        cout<<"Transposing from "<<a<<" to "<<b<<":"<<endl;
        for (int i=1;i<=tot;i++){
            int t=look(t1,c[i]);
            if (t==-1) cout<<"  "<<c[i]<<" is not a valid note in the "<<a<<" major scale"<<endl;
            else cout<<"  "<<c[i]<<" transposes to "<<diao[t2][t]<<endl;
        }
        cout<<endl;     
    }
    return 0;
}

