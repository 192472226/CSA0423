#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[1024];
    ssize_t bytes;

    src = open("input.txt", O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        return 1;
    }

    dest = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        return 1;
    }

    while ((bytes = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes);
    }

    close(src);
    close(dest);
    return 0;
}

