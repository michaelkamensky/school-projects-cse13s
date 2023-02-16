#include <stdio.h>
#include <gmp.h>
#include "randstate.h"

int main(void) {
    printf("randstate_ut function is now active\n");
    randstate_init(547863098576039847);
    gmp_printf("the state is %Zd\n", state);
    randstate_clear();  
    return 0;
}
