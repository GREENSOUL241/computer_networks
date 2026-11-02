
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5777
#define MAX 1024

int main() {
    int server_fd, client_fd;
    char buffer[MAX], rev[MAX];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 5);

    printf("TCP Server waiting for client...\n");

    client_fd = accept(server_fd, (struct sockaddr *)&client, &len);
    printf("Client connected!\n");

    while (1) {
        int n = read(client_fd, buffer, MAX - 1);
        if (n <= 0)
            break;

        buffer[n] = '\0';

        int j = 0;
        for (int i = n - 1; i >= 0; i--)
            rev[j++] = buffer[i];

        rev[j] = '\0';

        write(client_fd, rev, strlen(rev));
    }

    close(client_fd);
    close(server_fd);
    return 0;
}
