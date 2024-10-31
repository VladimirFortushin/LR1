#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
        int fd;
        if(argc == 2){
        fd = open(argv[1], O_RDONLY, 644);
        if(fd == -1){
        perror("Не удалось открыть файл");
        return EXIT_FAILURE;
        }
	off_t file_size = lseek(fd, 0, SEEK_END);
	if(file_size == -1){
	perror("Ошибка чтения размера файла");
	close(fd);
	return EXIT_FAILURE;
	}
	char symbol;
	for(off_t i  = file_size - 1; i >=0; i--){
	if (lseek(fd, i, SEEK_SET) == -1) {
                perror("Ошибка при установке позиции в файле");
                close(fd);
                return EXIT_FAILURE;
            }	
	if(read(fd, &symbol, 1) != 1){
	perror("Ошибка чтения из файла");
	close(fd);
	return EXIT_FAILURE;
	}
	write(STDOUT_FILENO, &symbol, 1);
	}

        close(fd);
}
return EXIT_SUCCESS;
}
