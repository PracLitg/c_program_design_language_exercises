#include <stdio.h>

#define upper 100
#define lower -20
#define step 10

int main() {
    float fahr;
    
    int up  = lower;

    while (up <= upper) {
        fahr = 9.0 / 5.0 * up + 32;
	printf("%4d\t%6.1f\n", up, fahr);
        up += step;
    }

    return 0;
}  
