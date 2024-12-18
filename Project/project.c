#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"
#include"modes.h"


int main()
{
    park_list* parks_All = NULL;
    char* s = NULL;
    
    s = malloc(sizeof(char) * (BUFFERSIZE + 1));
    if (s == NULL)
    {
        puts(MEMO_ERR_MSG);
        exit(-1);
    }

    parks_All = Init_park_list();

    s = fgets(s, (BUFFERSIZE + 1), stdin);
    
    while(s != NULL)
    {
        switch (s[0])
        {
            case 'p':
                Modo_P(s, parks_All);
                break;
            case 'e':
                Modo_E(s, parks_All);
                break;
            case 's':
                Modo_S(s, parks_All);
                break;
            case 'v':
                Modo_V(s, parks_All);
                break;
            case 'f':
                Modo_F(s, parks_All);
                break;
            case 'r':
                parks_All = Modo_R(s, parks_All);
                break;
            case'q':
                return 0;
                break;
            
            default:
                break;
        }
        s = fgets(s, (BUFFERSIZE + 1), stdin);
    }
    free(s);
    Free_all_parks(parks_All);
    return 0;
}