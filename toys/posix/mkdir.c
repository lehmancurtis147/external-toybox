/* mkdir.c - Make directories
 *
 * Copyright 2012 Georgi Chorbadzhiyski <georgi@unixsol.org>
 *
 * See http://opengroup.org/onlinepubs/9699919799/utilities/mkdir.html

USE_MKDIR(NEWTOY(mkdir, "<1vpm:", TOYFLAG_BIN|TOYFLAG_UMASK))

config MKDIR
  bool "mkdir"
  default y
  help
    usage: mkdir [-vp] [-m mode] [dirname...]

    Create one or more directories.

    -m	set permissions of directory to mode.
    -p	make parent directories as needed.
    -v	verbose
*/

#define FOR_mkdir
#include "toys.h"

GLOBALS(
  char *arg_mode;
)

void mkdir_main(void)
{
  char **s;
  mode_t mode = (0777&~toys.old_umask);


  if (TT.arg_mode) mode = string_to_mode(TT.arg_mode, 0777);

  // Note, -p and -v flags line up with mkpathat() flags

  for (s=toys.optargs; *s; s++)
    if (mkpathat(AT_FDCWD, *s, mode, toys.optflags|1))
      perror_msg("'%s'", *s);
}
