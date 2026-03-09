#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
   size_t ptr_count   = 0;

   for (char **env = environ; *env != NULL; env++)
      {
         char *entry = *env;
         size_t len  = strlen (entry);

         if (q->search_pattern == NULL || q->search_pattern[0] == '\0'
             || strstr (entry, q->search_pattern) != NULL)
            {
               write (STDOUT_FILENO, entry, len);
               write (STDOUT_FILENO, "\n", 1);
            }

         if (q->is_verbose_mode)
            {
               total_bytes += len + 1;
               ptr_count++;
            }
      }

   if (q->is_verbose_mode)
      {
         total_bytes += (ptr_count + 1) * sizeof (char *);
         fprintf (stderr,
                  "[VERBOSE] TOTAL ENVIRONMENT BLOCK SIZE -- %zu BYTES\n",
                  total_bytes);
      }
}

int
strcmpci (char const *str1, char const *str2)
{
   for (;;)
      {
         int cmp = tolower (*str1) - tolower (*str2);
         if (!*str1 || !*str2 || cmp != 0)
            {
               return cmp;
            }
         str1++, str2++;
      }

   return 0;
}

typedef enum
{
   FLAG_NONE,
   FLAG_HELP,
   FLAG_INFO,
   FLAG_VERBOSE,
   FLAG_UNKNOWN
} flag_type_t;

typedef struct
{
   const char *short_flag;
   const char *long_flag;
   flag_type_t type;
} flag_map_t;

const flag_map_t flag_table[] = { { "-h", "--help", FLAG_HELP },
                                  { "-i", "--info", FLAG_INFO },
                                  { "-v", "--verbose", FLAG_VERBOSE } };

void
print_usage (const char *program_name)
{
#define popt(opt, desc) printf ("   %-45s %s\n", opt, desc)
   printf ("[USAGE] %s [FLAGS] [<SEARCH-PATTERN>]\n", program_name);
   printf ("[DESC.] TODO\n");

   printf ("[FLAGS]\n");
   popt ("--HELP, -H, -?", "PRINT THIS HELP MESSAGE AND EXIT");
   popt ("--INFO, -I", "PRINT INFORMATION ABOUT THIS PROGRAM AND EXIT");
   popt ("--VERBOSE, -V", "USE VERBOSE MODE");
   printf ("[NOTE] FLAGS ARE NOT CASE-SENSITIVE\n");
#undef popt
}

void
print_info (void)
{
#define pinfo(aspect, detail) printf ("   * %-17s %s\n", aspect, detail)
   printf ("[INFO]\n");
   printf ("   QENV -- TODO\n");
   printf ("\n");
   pinfo ("[AUTHOR]", "vs-123 @ https://github.com/vs-123");
   pinfo ("[REPOSITORY]", "https://github.com/vs-123/qenv");
   pinfo ("[LICENSE]",
          "GNU AFFERO GENERAL PUBLIC LICENSE VERSION 3.0 OR LATER");
#undef pinfo
}

flag_type_t
get_flag (const char *arg)
{
   for (size_t i = 0; i < sizeof (flag_table) / sizeof (flag_map_t); i++)
      {
         if (strcmpci (arg, flag_table[i].short_flag) == 0
             || strcmpci (arg, flag_table[i].long_flag) == 0)
            {
               return flag_table[i].type;
            }
      }
   return FLAG_UNKNOWN;
}

int
parse_arguments (int argc, char **argv, qenv_t *q)
{
   int data_idx = 1;

   if (argc > 1 && argv[1][0] == '-')
      {
         flag_type_t type = get_flag (argv[1]);

         switch (type)
            {
            case FLAG_HELP:
               print_usage (argv[0]);
               return 0;
            case FLAG_INFO:
               print_info ();
               return 0;
            case FLAG_VERBOSE:
               q->is_verbose_mode = true;
               data_idx           = 2;
               break;
            default:
               fprintf (stderr, "[ERROR] UNRECOGNISED FLAG, USE --HELP\n");
               return -1;
            }
      }

   if (argc < (data_idx))
      {
         fprintf (stderr, "[ERROR] BAD ARGUMENTS, USE --HELP\n");
         return -1;
      }

   /* will be NULL when no args provided,
      this NULL is handled in =process_env= */
   q->search_pattern = argv[data_idx];

   return 1;
}

int
main (int argc, char **argv)
{
   qenv_t q   = { 0 };
   int result = parse_arguments (argc, argv, &q);

   if (result <= 0)
      {
         return (result == 0) ? 0 : 1;
      }

   process_env (&q);

   return 0;
}
