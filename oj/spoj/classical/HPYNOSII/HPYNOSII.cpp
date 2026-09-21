#include <cstdio>

int main() {
    int pre[150]={};
    pre[4] = 1;
    pre[16] = 1;
    pre[20] = 1;
    pre[37] = 1;
    pre[42] = 1;
    pre[58] = 1;
    pre[89] = 1;
    pre[145] = 1;
    
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        int n, happy = 0, count = 0;
        scanf ("%d", &n);
        
        while (happy != 1) {
            happy = 0;
            
            while (n) {
                int temp = n % 10;
                happy += (temp * temp);
                n /= 10;
            }
            
            if (happy < 150 && pre[happy] == 1) {
                break;
            }
            else {
                n = happy;
                count++;
            }
        }
        
        if (happy == 1) printf ("%d\n", count);
        else printf ("-1\n");
    }
}