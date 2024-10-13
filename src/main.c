#include <stdio.h>
#include <stdlib.h>
#include "../include/bluetoothSetup.h"

int main() {

    if( initialize() < 0 ) { printf("Failed to initialize Bluetooth. \n"); }
    if( setup_mouse() < 0 ) { printf("Failed to set up mouse. \n"); }

    printf("Mouse is ready. \n");
}