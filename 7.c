#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>  
#include <grp.h>  
#include <unistd.h>
//stat -f /

void print_file_info(const char *filename, struct stat* stats) {
    printf("filename: %s\n", filename);
    printf("size: %lld byte\n",(long long)stats->st_size);
	printf("blocks: %ld\n", (long)stats->st_blocks);
	printf("rights: %o\n", stats->st_mode & 0777);

    
    if (S_ISREG(stats->st_mode)) {
        printf("regular file\n");
    } else if (S_ISDIR(stats->st_mode)) {
        printf("dir\n");
    } else if (S_ISCHR(stats->st_mode)) {
        printf("char cpecial\n");
    } else if (S_ISBLK(stats->st_mode)) {
        printf("block special\n");
    } else if (S_ISFIFO(stats->st_mode)) {
        printf("FIFO\n");
    } else if (S_ISSOCK(stats->st_mode)) {
        printf("socket\n");
    } else if (S_ISLNK(stats->st_mode)) {
        printf("symbolik link\n");
    } else {
        printf("unknown type\n");
    }

    
    printf("creation time: %s", ctime(&stats->st_ctime));

    

    
    
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat stats;
	

	if(stat(argv[1], &stats) == 0){
	print_file_info(argv[1], &stats);
	}else{
	return EXIT_FAILURE;
	}    
    

    
    

    return EXIT_SUCCESS;
}
