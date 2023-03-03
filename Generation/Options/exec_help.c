#include <stdio.h>


void exec_help(void)
{
   printf("usage: ./main [options] \n");
   printf("List of available options : \n");
   printf("-c -circle          : Generate a circle gradient\n");
   printf("-ds -diamond_square : Generate a diamond square Noise\n");
   printf("-h                  : Print list of options\n");
   printf("-i -island          : Generate a default island map 1000x1000\n");
   printf("-map                : Generate a default map 1920x1080\n");
   printf("-p -perlin          : Generate a perlin Noise\n");
   printf("-P -perso           : Launch personalisation menu\n");
   printf("-s -simplex         : Generate a simplex Noise\n");
}
