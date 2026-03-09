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

         if (q->search_pattern == NULL || q->search_pattern[0] == '\0'
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
         size_t ptr_count = 0;
         for (char **env = environ; *env != NULL; env++)
            {
               ptr_count++;
            }
         
         total_bytes += (ptr_count + 1) * sizeof (char *);
         fprintf (stderr,
                  "[VERBOSE] TOTAL ENVIRONMENT BLOCK SIZE -- %zu BYTES\n",
                  total_bytes);
      }
}

int
main (void)
{

   return 0;
}
