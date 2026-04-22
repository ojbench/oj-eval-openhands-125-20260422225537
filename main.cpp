#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(size_t n = 0) { init(n); }
    void init(size_t n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while (p[x] != x) {
            p[x] = p[p[x]];
            x = p[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct FastIO {
    static const int S = 1 << 20;
    int wpos; char wbuf[S];
    FastIO() : wpos(0) { ios::sync_with_stdio(false); cin.tie(nullptr); }
    ~FastIO() { if (wpos) fwrite(wbuf, 1, wpos, stdout); }
    inline int nextInt() {
        int c = getchar_unlocked();
        while (c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
        int sgn = 1; if (c == '-') sgn = -1, c = getchar_unlocked();
        long long x = 0;
        while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
        return int(x * sgn);
    }
    inline void writeStr(const char* s) {
        while (*s) {
            if (wpos == S) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
            wbuf[wpos++] = *s++;
        }
    }
};

int main() {
    FastIO io;
    int t = io.nextInt();
    for (int caseId = 0; caseId < t; ++caseId) {
        int n = io.nextInt();
        vector<pair<int,int>> neq; neq.reserve(256);
        vector<pair<int,int>> eqs; eqs.reserve(n);
        vector<int> ids; ids.reserve(2*n);
        for (int i = 0; i < n; ++i) {
            int a = io.nextInt();
            int b = io.nextInt();
            int e = io.nextInt();
            ids.push_back(a); ids.push_back(b);
            if (e == 1) eqs.emplace_back(a, b);
            else neq.emplace_back(a, b);
        }
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());
        auto getId = [&](int x){ return int(lower_bound(ids.begin(), ids.end(), x) - ids.begin()); };
        DSU dsu(ids.size());
        for (auto &pr : eqs) dsu.unite(getId(pr.first), getId(pr.second));
        bool ok = true;
        for (auto &pr : neq) {
            if (dsu.find(getId(pr.first)) == dsu.find(getId(pr.second))) { ok = false; break; }
        }
        if (ok) io.writeStr("YES\n"); else io.writeStr("NO\n");
    }
    return 0;
}
