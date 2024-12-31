#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void scan_ports(const char *host, int start_port, int end_port) {
    printf("Scanning ports from %d to %d on %s...\n", start_port, end_port, host);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);

    for (int port = start_port; port <= end_port; port++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        addr.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0) {
            printf("Port %d is open\n", port);
        }

        close(sock);
    }
}

int main() {
    const char *target_host = "127.0.0.1"; // Localhost; replace with the target IP address if needed
    int start_port = 0;
    int end_port = 3000;

    scan_ports(target_host, start_port, end_port);
    return 0;
}
