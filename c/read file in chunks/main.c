#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CHUNK_SIZE 256


int chunkable(int size){
    return (size - CHUNK_SIZE) > 0;
}

char * read_file(FILE * f, size_t fsize){
    size_t readed_bytes = 0;
    char * fc = (char *) malloc(sizeof(char) * fsize);
    char * track = fc;

    printf("reading %zu bytes\n", fsize);
    if(chunkable(fsize)){
        do{
            readed_bytes = fread(track, 1, CHUNK_SIZE, f);
            if(!readed_bytes){
                break;
            }

            track += readed_bytes;
            fsize -=  readed_bytes;
            printf("reading left: %zu\n", fsize);
        }while(fsize);
        *track = 0;
    } else {
        fread(track, CHUNK_SIZE, 1, f);
    }
    return fc;
}

int get_file_size(FILE *f){
    int size = 0;
    fseek(f, 0, SEEK_END);

    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

int main(int argc, char *argv[]){
    int file_size;
    char * fc;
    FILE * fp;

    if(argc == 1){
        fputs("Missing argument filename, exiting...\n", stderr);
        return -1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("fopen");
        return -1;
    }

    file_size = get_file_size(fp);
    fc = read_file(fp, file_size);

    printf("filedata:\n\tsize: %d\n\tcontent:\n\n%s", file_size, fc);

    free(fc);
    fclose(fp);
}

