#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#define FILENAME 256

char buf[256][20] = {0};
int wordcount[256] = {0};
char textfile[FILENAME];
int main()
{
    
    memset(textfile , '\0' , FILENAME);
    int check;
    printf("input the filename\n");
    if ((check = read(STDIN_FILENO, textfile , sizeof(textfile))) == -1)
    {
        perror("read");
        exit(1);
    }

    textfile[strcspn(textfile, "\n")] = '\0';

    int fd = open(textfile, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    

    struct stat file_info;
    int filesize = file_info.st_size;
    
    
    int totalwords = 0;
    char character;
    char word[20];
    memset(word, '\0', sizeof(word));
   
    int allocatedword = 0;
    while (read(fd , &character , 1) > 0)
    {
        if (character == ' ' || character == '\t' || character == '\n' )
            continue;
        
        totalwords++;
        int index = 0;
        while (character != ' ' && character != '\t' && character != '\n')
        {   
                word[index++] = character;
                if (read(fd , &character , 1) == 0)
                break;
                
        }

        word[index] = '\0';
    
       
        int flag = 0;
        for (int  i = 0; i < allocatedword; i++)
        {
            if (flag = (strcmp(word, buf[i]) == 0))
            {
                wordcount[i]++;
                break;
            }
            
        }

        if (!flag) {
            strcpy(buf[allocatedword], word);
            wordcount[allocatedword++]++;
        }

    }

    close(fd);

    for (int i = 0; i < allocatedword; i++)
    {
        printf("%s : %d\n", buf[i], wordcount[i]);
    }

    printf("total number of words in text: %d\n", totalwords);
    printf("total number of characters in text: %d\n", filesize);

    return 0;
}
