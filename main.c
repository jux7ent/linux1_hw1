#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fs.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    printf("Welcome to MiniFS!\n");
    char command[30];
    FILE* dev = fopen(argv[1], "r+b");

    if (dev == NULL) {
        perror("fopen(dev)");
        return 1;
    }

    if(open_fs(dev)) {
        create_fs(dev);
        open_fs(dev);
    }

    for(;;) {
        printf("> ");
        scanf("%s", command);
        if (strcmp(command, "help") == 0) {
            printf("List of commands\n");
            printf("1. create root/path_to_new_file new_file_name CONTENT\n");
            printf("2. cat root/path_to_file\n");
            printf("3. mkdir root/path_to_new_dir new_dir_name\n");
            printf("4. ls root/path\n");
            printf("5. rm root/path_to_removable_file\n");
            printf("6. rmdir root/path_to_removable_dir\n");
            printf("7. put path_on_local root/path_to_new_file\n");
            printf("8. get root/path_to_file path_on_local\n");
            printf("8. quit\n");
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "create") == 0) {
            char path[100];
            char name[12];
            char file[100];
            scanf("%s%s%s", path, name, file);
            create(path, name, file, 100);
        } else if (strcmp(command, "cat") == 0) {
            char path[100];
            scanf("%s", path);
            cat(path);
        } else if (strcmp(command, "mkdir") == 0) {
            char path[100];
            char name[12];
            scanf("%s%s", path, name);
            mkdir(path, name);
        } else if (strcmp(command, "ls") == 0) {
            char path[100];
            scanf("%s", path);
            char* list = ls(path, NULL);
            printf("%s", list);
            free(list);
        } else if (strcmp(command, "rm") == 0) {
            char path[100];
            scanf("%s", path);
            rm(path);
        } else if (strcmp(command, "rmdir") == 0) {
            char path[100];
            scanf("%s", path);
            mrmdir(path);
        } else if (strcmp(command, "put") == 0) {
            char file[100];
            char path[100];
            scanf("%s%s", file, path);
            put(file, path);
        } else if (strcmp(command, "get") == 0) {
            char file[100];
            char path[100];
            scanf("%s%s", path, file);
            get(file, path);
        } else {
            printf("Unknown command: %s", command);
        }
    }
    fclose(dev);
    return 0;
}
