#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

extern char **environ;

typedef struct
{
   char *search_pattern;
   bool is_verbose_mode;
} qenv_t;

void
process_env (const qenv_t *q)
{
   size_t total_bytes = 0;
   
   for (char **env = environ; *env != NULL; env++)
      {
         char *entry = *env;
         size_t len  = strlen (entry);

         if (q->search_pattern == NULL
             || strstr (entry, q->search_pattern) != NULL)
            {
               printf ("%s\n", entry);
            }

         if (q->is_verbose_mode)
            {
	       total_bytes += len + 1;
            }
      }

   if (q->is_verbose_mode)
      {
         printf("===  TOTAL ENVIRONMENT BLOCK SIZE -- %zu BYTES ===\n", total_bytes);
      }
}

int
main (void)
{

   return 0;
}
