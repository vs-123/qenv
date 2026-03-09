#include <stdio.h>
#include <string.h>
#include <stddef.h>

extern char **environ;

int
main (void)
{
   printf ("Hello, World!\n");

   for (char **env = environ; *env != NULL; env++)
      {
         char *entry = *env;

         printf ("%s\n", entry);
      }

   return 0;
}
