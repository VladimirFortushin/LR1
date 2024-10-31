#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *filename = "/home/students/f/fortushin.vd/no_exist.txt";
    int fd = open(filename, O_RDWR);

    if (fd == -1) {
        printf("Ошибка при открытии файла: %s\n", strerror(errno));
	
        return 1;
    }

    printf("Файл успешно открыт. errno: %d\n", fd);

    if (close(fd) == -1) {
        perror("Ошибка при закрытии файла: ");
        return 1;
    }

    printf("Файл успешно закрыт. errno: %d\n", fd);

    return 0;
}

