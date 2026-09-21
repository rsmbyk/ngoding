#define ppq std::priority_queue<std::pair<int, int> >

int main () {
    int tc, n, c;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d", &n, &c);
        ppq villages, reserves;
        
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf ("%d %d", &a, &b);
            if (a < c) villages.push (std::make_pair (b, a));
            else reserves.push ();
        }
        
        while (!villages.empty () || !reserves.empty ()) {
            if (villages.empty ()) {
                if (reserves.)
            }
        }
    }
}