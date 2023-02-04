#include "set.h"
#include <stdio.h>

void set_print(Set s) {
    int i;
    for(i = 31; i >= 0; i--) {
        if (s & (1 << i)) {
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");
}

int main(void) {
    Set s = set_empty();
    printf("set_empty() = ");
    set_print(s);
    Set s1 = set_universal();
    printf("set_universal() = ");
    set_print(s1);
    s = set_insert(s, 4);
    printf("set_inster(4) = ");
    s = set_insert(s, 10);
    printf("set_inster(10) = ");
    set_print(s);
    printf("old set s1");
    set_print(s1);
    s1 = set_remove(s1, 4);
    printf("set_remove(4) = ");
    set_print(s1);
    printf("set_member of s1 of 4 should be false\n");
    printf("the result is %d\n", set_member(s1, 4));
    printf("set_member of s of 4 should be true\n");
    printf("the result is %d\n", set_member(s, 4));\
    s1 = set_remove(s1, 15);
    printf("s1 = ");
    set_print(s1);
    printf("s = ");
    set_print(s);
    printf("set_union = ");
    set_print(set_union(s, s1));
    Set s2 = set_universal();
    printf("s2 = ");
    set_print(s2);
    printf("s = ");
    set_print(s);
    printf("set_intersect(s2, s) = ");
    set_print(set_intersect(s2, s));
    s2 = set_remove(s2, 4);
    s2 = set_remove(s2, 8);
    s2 = set_remove(s2, 9);
    printf("s2 = ");
    set_print(s2);
    printf("s1 = ");
    set_print(s1);
    printf("set_difference(s2, s1) = ");
    set_print(set_difference(s1, s2));

    return 0;
}
