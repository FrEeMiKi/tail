#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include<ctype.h> 

#define LINE_LENGTH 1024
int LAST_LINES = 10;
int START_LINE = 0;
int LAST_BYTES = 0;
int FIRST_BYTES = 0;

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

int tail(FILE *file)
{
    int count_lines = 0;
    char lines[LAST_LINES][LINE_LENGTH];

    while (fgets(lines[count_lines % LAST_LINES], LINE_LENGTH, file) != NULL)
    {
        count_lines++;
    }

    int start = count_lines > LAST_LINES ? count_lines % LAST_LINES : 0;
    int count = count_lines > LAST_LINES ? LAST_LINES : count_lines;
    if (START_LINE > start)
    {
        start = START_LINE;
        count = count_lines - START_LINE;
    }
    if (LAST_BYTES == 0 && FIRST_BYTES == 0)
    {
        for (int i = 0; i < count; i++)
        {
            int count_bytes = 
            printf("%s", lines[(start + i) % LAST_LINES]);
        }
    }
    if (FIRST_BYTES != 0)
    {
        fseek(file, FIRST_BYTES, SEEK_SET);
        char buffer[LAST_BYTES + 1]; 
        size_t bytes_read = fread(buffer, 1, LAST_BYTES, file);
        buffer[bytes_read] = '\0'; 
        printf("%s", buffer);
        printf("\n");
    }
    if (LAST_BYTES != 0)
    {
        fseek(file, -LAST_BYTES, SEEK_END); 
        char buffer[LAST_BYTES + 1]; 
        size_t bytes_read = fread(buffer, 1, LAST_BYTES, file);
        buffer[bytes_read] = '\0'; 
        printf("%s", buffer);
        printf("\n");
    }
    return 0;
}


int main(int argc, char *argv[])
{

    FILE *file;
    if (argc == 1)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    else
    {
        file = fopen(argv[argc - 1], "r");
    }
    
    if (argc > 2)
    {
        for (int i = 1; i < argc - 1; i++)
        {
            if (strcmp(argv[i], "-n") == 0)
            {
                LAST_LINES = atoi(argv[i + 1]);
            }
            else if (strncmp(argv[i], "+", 1) == 0) 
            {
                START_LINE = atoi(ltrim(argv[i] + 1));
            }
            else if (strcmp(argv[i], "-c") == 0)
            {
                if (strncmp(argv[i+1], "+", 1) == 0)
                {
                    FIRST_BYTES = atoi(argv[i + 1] + 1);
                } 
                else if (strncmp(argv[i+1], "-", 1) == 0)
                {
                    LAST_BYTES = atoi(argv[i + 1] + 1);
                }
                else
                {
                    LAST_BYTES = atoi(argv[i + 1]);
                }
            }
        }
    }
    
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    tail(file);

    int count_lines = 0;
    return 0;
}
