AC_PREREQ([2.69])
AC_INIT([xlibs], [1.0], [jflopezfernandez@gmail.com])
AM_INIT_AUTOMAKE([-Wall foreign])
AM_PROG_AR
LT_PREREQ([2.4.6])
LT_INIT

AC_CONFIG_MACRO_DIRS([m4])

# Configuration options.
AC_ARG_ENABLE([crc32],
    [AS_HELP_STRING([--disable-strings],
        [disable strings library (enabled by default)])],
    [strings_library_enabled="$enableval"],
    [strings_library_enabled=yes])

if test "x$strings_library_enabled" = xyes
then
    AC_CONFIG_SUBDIRS([strings])
fi

# Define the configuration files to generate.
AC_CONFIG_FILES([Makefile])

# Finish up the configuration.
AC_OUTPUT
