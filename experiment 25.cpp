 #include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd;
    char buffer[200];

    fd = open("sample.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("Cannot open file\n");
        return 1;
    }

    write(fd, "UNIX System Calls Test\n", 23);
    lseek(fd, 0, SEEK_SET);

    int n = read(fd, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("%s\n", buffer);

    struct stat st;
    stat("sample.txt", &st);
    printf("Size: %ld bytes\n", st.st_size);

    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    close(fd);
    return 0;
}
