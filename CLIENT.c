
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5777
#define MAX 1024

int main() {
    int sockfd;
    char sendline[MAX], revline[MAX];
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server, sizeof(server));

    while (1) {
        printf("Enter a sentence: ");
        if (fgets(sendline, MAX, stdin) == NULL)
            break;

        write(sockfd, sendline, strlen(sendline));

        int n = read(sockfd, revline, MAX - 1);
        if (n <= 0)
            break;

        revline[n] = '\0';
        printf("Reversed sentence: %s\n", revline);
    }

    close(sockfd);
    return 0;
}
