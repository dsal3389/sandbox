#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


#define TAB_CHUNK_SIZE 1

void print_dir(char *path, char *pname, int tabs);
int is_dir(const char *path);


int main(int argc, char **argv){
    if(argc == 1){
        fprintf(stderr, "no start directory specifiyed\n");
        exit(1);
    }

    if(!is_dir(argv[1])){
        fprintf(stderr, "given path is not a dir\n");
        exit(1);
    }
    print_dir(argv[1], argv[1], 2);
    return 0;
}

void print_dir(char *path, char *pname, int tabs){
    DIR *d;
    struct dirent *ep;
    d = opendir(path);

    printf("%*c %s\n", tabs, '-', pname);
    while(ep = readdir(d)){
        char *name = ep -> d_name;
        char npath[255*tabs];

        if(!strcmp(name, ".") || !strcmp(name, ".."))
            continue;

        snprintf(npath, sizeof(npath), "%s/%s", path, name);

        if(is_dir(npath)){
            print_dir(npath, name, tabs+1);
        }
        else{
            printf("%*c %s\n", tabs, '|', name);
        }
    }
    closedir(d);
}

int is_dir(const char *path){
    DIR *dir;
    dir = opendir(path);

    if(dir != NULL){
        closedir(dir);
        return 1;
    }

    if(errno == ENOTDIR)
        return 0;
    return -1;
}

