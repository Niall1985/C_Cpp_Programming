#include <iostream>
#include <vector>
using namespace std;

vector<int> computeLPS(const string &pat) {
    int m = pat.length(), len = 0;
    vector<int> lps(m, 0);
    
    for (int i = 1; i < m; ) {
        if (pat[i] == pat[len]) 
            lps[i++] = ++len;
        else 
            len ? len = lps[len - 1] : i++;
    }
    return lps;
}

vector<int> KMPsearch(const string &txt, const string &pat) {
    vector<int> lps = computeLPS(pat), res;
    int i = 0, j = 0, n = txt.length(), m = pat.length();

    while (i < n) {
        if (txt[i] == pat[j]) { i++; j++; }
        if (j == m) res.push_back(i - j), j = lps[j - 1];
        else if (i < n && txt[i] != pat[j]) j ? j = lps[j - 1] : i++;
    }
    return res;
}

int main() {
    string txt = "aabaacaadaabaaba", pat = "aaba";
    for (int i : KMPsearch(txt, pat)) cout << i << " ";
}
