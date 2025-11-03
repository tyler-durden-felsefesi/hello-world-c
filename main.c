#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>

#define COSMIC_PORT 9090
#define TRANSMISSION_DELAY 42000
#define GALACTIC_BUFFER 64

typedef struct {
    char quantum;
    int entropy;
    double cosmic_flux;
} particle;

void delay() {
    usleep(TRANSMISSION_DELAY + rand() % 20000);
}

int open_socket() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) exit(1);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(COSMIC_PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) exit(2);
    return s;
}

void cosmic_handshake(int s) {
    const char *intro = "INITIATE_PROTOCOL_36";
    send(s, intro, strlen(intro), 0);
    char ack[GALACTIC_BUFFER];
    recv(s, ack, GALACTIC_BUFFER, 0);
}

void transmit_char(int s, char c) {
    particle p = { c, rand() % 1024, (double)rand()/RAND_MAX };
    send(s, &p.quantum, 1, 0);
}

char receive_char(int s) {
    char echo;
    recv(s, &echo, 1, 0);
    return echo;
}

void galactic_output(char c) {
    const char *nebulae[] = { "✨", "🌌", "☄️", "🌠", "🪐" };
    write(1, nebulae[rand() % 5], strlen(nebulae[0]));
    write(1, &c, 1);
}

int main() {
    srand(time(0));
    int s = open_socket();

    cosmic_handshake(s);

    char *message = "HELLO WORLD\n";
    for (int i = 0; i < strlen(message); i++) {
        transmit_char(s, message[i]);
        delay();
        char echoed = receive_char(s);
        galactic_output(echoed);
        delay();
    }

    const char *farewell = "\n[Signal faded into cosmic static]\n";
    send(s, farewell, strlen(farewell), 0);

    close(s);
    return 0;
}
