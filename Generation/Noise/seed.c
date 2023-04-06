#include <stdio.h>
#include <stdlib.h>


char *read_seed(char *pathname)
{
    FILE *seed = fopen(pathname,"r");
    char *s = malloc(256*sizeof(char));
    int er = fread(s,256,1,seed);
    if(er<0)
        return 0;
    fclose(seed);
    return s;
}

void save_seed(char* seed, char *path)
{
    FILE *save = fopen(path,"w");
    fprintf(save,"%s",seed);
    fclose(save);
}
