#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;
#define EPS 1e-11
const int M = 825;
const int N = 125;

struct edge {
    int u, v;
    double a, b, val;
    
    bool operator<(edge other) const{
        return val < other.val;
    }
};

edge arr[M];
int pset[N];
int n, m, tc;
double t1, t2;

void _reset() {
    for (int i = 0; i < n; i++)
        pset[i] = i;
}

int finds(int x) {
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

double work(double t) {
    _reset();
    for (int i = 0; i < m; i++)
        arr[i].val = t * arr[i].a + arr[i].b;
    sort(arr, arr + m);
    double res = 0;
    for (int i = 0; i < m; i++) {
        int uu = arr[i].u;
        int vv = arr[i].v;
        if (finds(uu) != finds(vv)) {
            pset[finds(uu)] = vv;
            res += arr[i].val;
        }
    }
    return res;
}

int main() {
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d %d", &n, &m);
        scanf("%lf %lf", &t1, &t2);
        for (int i = 0; i < m; i++)
            scanf("%d %d %lf %lf", &arr[i].u, &arr[i].v, &arr[i].a, &arr[i].b);
        
        double m, m1, m2, r, pr, pp, pm, br;
        pr = work (m);
        
        m1 = work (t1);
        m2 = work (t2);
        br = pr = max (m1, m2);
        pm = m1 > m2 ? t1 : t2;
        pp = m1 > m2 ? t2 : t1;
        
        while (t2 - t1 > EPS) {

//            printf ("%f %f\n", t1, t2);
            m1 = work (t1);
            m2 = work (t2);
            
            m = (t1 + t2) / 2.0;
            if (m1 + EPS > m2) t2 = (m + t2) / 2.0;
            else t1 = (m + t1) / 2.0;
            
        }
//        printf ("%f %f\n", work (t1), work (t2));

//            double m = (t1 + t2) / 2;
//            double r = work (m);
//            double m1 = t1 + (t2 - t1) / 3.0;
//            double m2 = t1 + (t2 - t1) * 2.0 / 3.0;
//            double r1 = work(m1);
//            double r2 = work(m2);
//            printf ("--------------------\n");
//            printf ("%f %f\n", t1, t2);
//            printf ("%f %f\n", m1, m2);
//            printf ("%f %f\n", r1, r2);
//            if (r1 + EPS > r2) t2 = m2;
//            else t1 = m1;
//        }
//            printf ("--------------------\n");
        printf("%.3f %.3f\n", (t1 + t2) / 2.0, work((t1 + t2) / 2.0));
    }
}
