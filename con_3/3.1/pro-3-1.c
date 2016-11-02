#include <stdio.h>
#include <time.h>

int main(){
    time_t t_start, t_end;
    t_start = time(NULL) ;
    sleep(3000);
    t_end = time(NULL) ;
    printf("time: %.0f s\n", difftime(t_end,t_start)) ;
    return 0;
}
