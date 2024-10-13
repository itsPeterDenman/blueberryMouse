#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include "../include/bluetoothSetup.h"

int initialize() {
    printf("Initializing bluetooth connection... \n");

    system("sudo hciconfig hci0 up"); // turn bluetooth on
    system("sudo btmon &"); // monitor events

    return 0;
}

int setup_mouse() {
    printf("Setting up Bluetooth Mouse HID... \n");

    struct sockaddr_rc address = { 0 };
    int sock, status;
    char dest[18];

    strncpy(dest, "30:57:14:15:59:E8", sizeof(dest) - 1);
    dest[17] = '\0'; // null terminator

    /*
    AF_BLUETOOTH : int domain, found in man socket
    SOCK_STREAM : int type, found in man socket
    BTPROTO_RFCOMM : int protocol, not sure where to find this but /usr/include/bluetooth/bluetooth.h defines it as 3
    */
    sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if(sock < 0) { printf("Failed to create socket. \n"); return -1; }
    printf("Socket created. \n");

    address.rc_family = AF_BLUETOOTH; // address family (bluetooth)
    address.rc_channel = (uint8_t)1; // channel number
    str2ba(dest, &address.rc_bdaddr); // device address

    status = connect(sock, (struct sockaddr*)&address, sizeof(address));
    if(status < 0) { printf("Failed to connect. \n"); return -1; }

    printf("Connection Successful! \n");

    close(sock);

    return 0;
}