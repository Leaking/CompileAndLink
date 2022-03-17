#include <stdio.h>
void DoThing();
void DoLayer() {
    printf("layer \n");
    DoThing();
}