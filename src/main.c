#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

extern char **environ;

typedef struct
{
   char *search_pattern;
   bool is_verbose_mode;
} qenv_t;

void
process_env (qenv_t q)
{
   /* TODO */
}

int
main (void)
{
   for (char **env = environ; *env != NULL; env++)
      {
         char *entry = *env;

         printf ("%s\n", entry);
      }

   return 0;
}
