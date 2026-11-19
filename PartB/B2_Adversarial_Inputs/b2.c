
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void unsafe_input(void)
{
    char name[20];

    printf("Enter donor name (unsafe scanf): ");
    scanf("%s", name);

    printf("Name: %s\n", name);
}

void safe_input(void)
{
    char name[20];

    printf("Enter donor name (safe fgets): ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Input error\n");
        return;
    }

    name[strcspn(name, "\n")] = '\0';
    printf("Name: %s\n", name);
}

void check_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        perror("File opening failed");
        return;
    }

    printf("File opened successfully\n");
    fclose(fp);
}

int valid_group(const char *group)
{
    const char *groups[] = {
        "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
    };

    for (int i = 0; i < 8; i++) {
        if (strcmp(group, groups[i]) == 0)
            return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Error: Missing command\n");
        printf("Usage: b2 safe | unsafe | file filename | find bloodgroup\n");
        return 1;
    }

    if (strcmp(argv[1], "safe") == 0) {
        safe_input();
    }
    else if (strcmp(argv[1], "unsafe") == 0) {
        unsafe_input();
    }
    else if (strcmp(argv[1], "file") == 0) {
        if (argc != 3) {
            printf("Error: Give exactly one filename\n");
            return 1;
        }
        check_file(argv[2]);
    }
    else if (strcmp(argv[1], "find") == 0) {
        if (argc != 3) {
            printf("Error: Give one blood group\n");
            return 1;
        }

        if (valid_group(argv[2]))
            printf("Valid blood group: %s\n", argv[2]);
        else
            printf("Invalid blood group: %s\n", argv[2]);
    }
    else {
        printf("Error: Unknown command\n");
        return 1;
    }

    return 0;
}
