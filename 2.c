#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	if(argc < 3){
		printf("Wrong params count for %s: %d, should be: file_name permissions", argv[0], argc-1);
	}

	const char* filename = argv[1]; //const char* - mutable pointer to immutable char[]
	const char* permissionChar = argv[2];
	int permission = atoi(permissionChar);
	
	int fd = creat(filename, permission);
	
	if(fd < 0){
		printf("Error while creating file, fd=%d\n", fd);
		printf("Permission: %d", permission);
	}
	
	write(fd, "random text\nrand??\nno way\n", 26);
	
	close(fd);

	fd = open(filename, O_RDONLY);

	if(fd < 0){
		perror("Error opening file O_RDONLY");
	}

	int buf_size = 26;
	char buffer[buf_size];
	int read_bytes = 0;
	
	while((read_bytes = read(fd, buffer, buf_size)) > 0){
		write(STDOUT_FILENO, buffer, read_bytes);
	}

	if(read_bytes == -1){
		perror("Error reading file");
	}
	
	close(fd);
	
	fd = open(filename, O_RDWR);

	if(fd < 0){
		perror("Error opening file O_RDWR");
	}

	close(fd);

	return 0;
}
