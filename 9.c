#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void read_from_file_paste_to_file(int fd_from, int fd_to){
        int buffer_size = 256;
        char buffer[buffer_size];
        ssize_t bytes_read, bytes_written;

        while((bytes_read = read(STDIN_FILENO, buffer, buffer_size)) > 0){
        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if(bytes_written == -1){
        perror("Ошибка записи в файл");
        exit(EXIT_FAILURE);
        }
        if(bytes_read == -1){
        perror("Ошибка чтения из файла");
        exit(EXIT_FAILURE);
        }

        }

}

int main(int argc, char *argv[]){
        int from_fd, to_fd;
        if(argc == 3){
        from_fd = open(argv[1], O_RDONLY);
        if(from_fd == -1){
        perror("Не удалось открыть файл для чтения");
        return EXIT_FAILURE;
        }

        to_fd = open(argv[2], O_WRONLY | O_TRUNC, 644);
        if(to_fd == -1){
        perror("Не удалось открыть файл для записи");
        return EXIT_FAILURE;
        }

	if(dup2(from_fd, STDIN_FILENO) == -1){
	perror("Ошибка переназначения стандартного ввода");
	close(from_fd);
	return EXIT_FAILURE;
	}
	if(dup2(to_fd, STDOUT_FILENO) == -1){
	perror("Ошибка переназначения стандартного вывода");
	close(to_fd);
	return EXIT_FAILURE;
	}

        read_from_file_paste_to_file(from_fd, to_fd);
        close(from_fd);
        close(to_fd);
        }else{
        fprintf(stderr, "Использование: %s <исходный файл> <целевой файл>\n", argv[0]);
        return EXIT_FAILURE;
        }


        return EXIT_SUCCESS;



}
