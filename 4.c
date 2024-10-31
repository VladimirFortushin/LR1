#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
// blocks?? 
//./4 4_file.txt 644

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Использование: %s <имя файла> <права доступа (в восьмеричном виде)>\n", argv[0]);
        
    }

    const char* filename = argv[1];
	const char* permissionChar = argv[2];
    int permission = atoi(permissionChar);

    int fd = creat(filename, permission);
    if (fd < 0) {
        perror("Ошибка при создании файла");
	return EXIT_FAILURE;
    }

    long offset = lseek(fd, 1024L, SEEK_SET);
    if (offset < 0) {
        perror("lseek");
	return EXIT_FAILURE;
    }

   
    const char *data = "X\n";
    if (write(fd, data, strlen(data)) < 0) {
        perror("write");
	return EXIT_FAILURE;
    }

close(fd);
	fd = open(filename, O_WRONLY);


    offset = lseek(fd, 0, SEEK_SET);
    if (offset < 0) {
        perror("lseek");
	return EXIT_FAILURE;
    }

    const char *line = "bla\nbla bla\nbla bla bla\n";
	int  bytes_written = write(fd, line, strlen(line));
    if (bytes_written == -1) {
        perror("Ошибка при записи в файл");
	return EXIT_FAILURE;
    }
	close(fd);


    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Ошибка при открытии файла на чтение");
	return EXIT_FAILURE;
   
    }


	int buffer_size = 64;
    char buffer[buffer_size];
    int read_bytes;


	printf("Содержимое файла:\n");
    while ((read_bytes = read(fd, buffer, buffer_size)) > 0) {
        write(STDOUT_FILENO, buffer, read_bytes);
    }

	
    if (read_bytes == -1) {
        perror("Ошибка при чтении файла");
	return EXIT_FAILURE;
    }
	
	


    close(fd);
       


    return 0;
}
