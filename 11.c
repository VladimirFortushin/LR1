#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
	struct stat file_stat;
	 int maxLength = 0;
    int length;
    char *longestFileName = NULL; 

    for (int i = 1; i < argc; i++) {
        struct stat fileStat;

        
        if (stat(argv[i], &file_stat) == -1) {
            perror("Ошибка получения информации о файле");
            return EXIT_FAILURE;
        }

        
        length = file_stat.st_size;

        
        if (length >=  maxLength) {
            maxLength = length;
            longestFileName = argv[i];
        }
    }

    
    if (longestFileName != NULL) {
        printf("Файл с максимальной длиной: %s (размер: %d байт)\n", longestFileName, maxLength);
    } else {
        printf("Нет доступных файлов для обработки.\n");
    }

    return EXIT_SUCCESS;	


}
