#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<string, string> mroList;
string findSet (string n) { return mroList[n] == n ? n : mroList[n] = findSet (mroList[n]); }
void unionSet (string a, string b) { mroList[findSet (a)] = findSet (b); }

int main (int args, char const *argv[]) {
    int tc, p, z;
    cin >> tc;
    
    while (tc--) {
        mroList.clear ();
        cin >> p;
        
        map<string, string> recruits;
        string pesel, mro;
        for (int i = 0; i < p; i++) {
            cin >> pesel >> mro;
            recruits[pesel] = mro;
            mroList[mro] = mro;
        }
        
        cin >> z;
        string oldmro, newmro;
        for (int i = 0; i < z; i++) {
            cin >> oldmro >> newmro;
            unionSet (oldmro, newmro);
        }
        
        cin >> p;
        vector<pair<string, string> > results;
        for (int i = 0; i < p; i++) {
            cin >> pesel;
            mro = findSet (recruits[pesel]);
            results.push_back (make_pair (pesel, mro));
        }
        
        for (int i = 0; i < results.size (); i++) cout << results[i].first << " " << results[i].second << endl;
        cout << endl;
    }
    
    return 0;
}