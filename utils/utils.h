/* libguestfs
 * Copyright (C) 2013-2019 Red Hat Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef GUESTFS_UTILS_H_
#define GUESTFS_UTILS_H_

#include <stdbool.h>

#include "cleanups.h"

#define STREQ(a,b) (strcmp((a),(b)) == 0)
#define STRCASEEQ(a,b) (strcasecmp((a),(b)) == 0)
#define STRNEQ(a,b) (strcmp((a),(b)) != 0)
#define STRCASENEQ(a,b) (strcasecmp((a),(b)) != 0)
#define STREQLEN(a,b,n) (strncmp((a),(b),(n)) == 0)
#define STRCASEEQLEN(a,b,n) (strncasecmp((a),(b),(n)) == 0)
#define STRNEQLEN(a,b,n) (strncmp((a),(b),(n)) != 0)
#define STRCASENEQLEN(a,b,n) (strncasecmp((a),(b),(n)) != 0)
#define STRPREFIX(a,b) (strncmp((a),(b),strlen((b))) == 0)
#define STRCASEPREFIX(a,b) (strncasecmp((a),(b),strlen((b))) == 0)
#define STRSUFFIX(a,b) (strlen((a)) >= strlen((b)) && STREQ((a)+strlen((a))-strlen((b)),(b)))

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

/* Macro which compiles the regexp once when the program/library is
 * loaded, and frees it when the library is unloaded.
 */
#define COMPILE_REGEXP(name,pattern,options)                            \
  static void compile_regexp_##name (void) __attribute__((constructor)); \
  static void free_regexp_##name (void) __attribute__((destructor));    \
  static pcre *name;                                                    \
                                                                        \
  static void                                                           \
  compile_regexp_##name (void)                                          \
  {                                                                     \
    const char *err;                                                    \
    int offset;                                                         \
    name = pcre_compile ((pattern), (options), &err, &offset, NULL);    \
    if (name == NULL) {                                                 \
      write (2, err, strlen (err));                                     \
      abort ();                                                         \
    }                                                                   \
  }                                                                     \
                                                                        \
  static void                                                           \
  free_regexp_##name (void)                                             \
  {                                                                     \
    pcre_free (name);                                                   \
  }

#define _(str) dgettext(PACKAGE, (str))
#define N_(str) dgettext(PACKAGE, (str))

/* utils.c */
extern void guestfs_int_free_string_list (char **);
extern size_t guestfs_int_count_strings (char *const *);
extern char *guestfs_int_concat_strings (char *const *);
extern char **guestfs_int_copy_string_list (char *const *);
extern char *guestfs_int_join_strings (const char *sep, char *const *);
extern char **guestfs_int_split_string (char sep, const char *);
extern char *guestfs_int_replace_string (const char *str, const char *s1, const char *s2);
extern char *guestfs_int_exit_status_to_string (int status, const char *cmd_name, char *buffer, size_t buflen);
extern int guestfs_int_random_string (char *ret, size_t len);
extern char *guestfs_int_drive_name (size_t index, char *ret);
extern ssize_t guestfs_int_drive_index (const char *);
extern int guestfs_int_is_true (const char *str);
extern bool guestfs_int_string_is_valid (const char *str, size_t min_length, size_t max_length, int flags, const char *extra);
#define VALID_FLAG_ALPHA 1
#define VALID_FLAG_DIGIT 2
//extern void guestfs_int_fadvise_normal (int fd);
extern void guestfs_int_fadvise_sequential (int fd);
extern void guestfs_int_fadvise_random (int fd);
extern void guestfs_int_fadvise_noreuse (int fd);
//extern void guestfs_int_fadvise_dontneed (int fd);
//extern void guestfs_int_fadvise_willneed (int fd);
extern char *guestfs_int_shell_unquote (const char *str);
extern int guestfs_int_is_reg (int64_t mode);
extern int guestfs_int_is_dir (int64_t mode);
extern int guestfs_int_is_chr (int64_t mode);
extern int guestfs_int_is_blk (int64_t mode);
extern int guestfs_int_is_fifo (int64_t mode);
extern int guestfs_int_is_lnk (int64_t mode);
extern int guestfs_int_is_sock (int64_t mode);
extern char *guestfs_int_full_path (const char *dir, const char *name);
extern void guestfs_int_hexdump (const void *data, size_t len, FILE *fp);

/* Not all language bindings know how to deal with Pointer arguments.
 * Those that don't will use this macro which complains noisily and
 * returns NULL.
 */
#define POINTER_NOT_IMPLEMENTED(type)                                   \
  (                                                                     \
   fprintf (stderr, "*** WARNING: this language binding does not support conversion of Pointer(%s), so the current function will always fail.  Patches to fix this should be sent to the libguestfs upstream mailing list.\n", \
            type),                                                      \
   NULL                                                                 \
)

/* ANSI colours.  These are defined as macros so that we don't have to
 * define the force_colour global variable in the library.
 */
#define ansi_green(fp)                           \
  do {                                           \
    if (force_colour || isatty (fileno (fp)))    \
      fputs ("\033[0;32m", (fp));                \
  } while (0)
#define ansi_red(fp)                             \
  do {                                           \
    if (force_colour || isatty (fileno (fp)))    \
      fputs ("\033[1;31m", (fp));                \
  } while (0)
#define ansi_blue(fp)                            \
  do {                                           \
    if (force_colour || isatty (fileno (fp)))    \
      fputs ("\033[1;34m", (fp));                \
  } while (0)
#define ansi_magenta(fp)                         \
  do {                                           \
    if (force_colour || isatty (fileno (fp)))    \
      fputs ("\033[1;35m", (fp));                \
  } while (0)
#define ansi_restore(fp)                         \
  do {                                           \
    if (force_colour || isatty (fileno (fp)))    \
      fputs ("\033[0m", (fp));                   \
  } while (0)

#endif /* GUESTFS_UTILS_H_ */
