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
    int permission = strtol(permissionChar,NULL, 8);

    int fd = creat(filename, permission);
    if (fd < 0) {
        perror("Error creating file");
	return EXIT_FAILURE;
    }

    

close(fd);
	fd = open(filename, O_WRONLY);


    const char *line = "lambda\nomega\nrandomly written letters\n";
	int  bytes_written = write(fd, line, strlen(line));
    if (bytes_written == -1) {
        perror("Error writing to file");
	return EXIT_FAILURE;
    }
	close(fd);


    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
	return EXIT_FAILURE;
   
    }


	int buffer_size = 64;
    char buffer[buffer_size];
    int read_bytes;


	printf("File content:\n");
    while ((read_bytes = read(fd, buffer, buffer_size)) > 0) {
        write(STDOUT_FILENO, buffer, read_bytes);
    }

	
    if (read_bytes == -1) {
        perror("Error reading file");
	return EXIT_FAILURE;
    }
	
	


    close(fd);
       


    return 0;
}
