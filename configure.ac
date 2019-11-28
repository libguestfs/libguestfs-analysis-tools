# libguestfs
# Copyright (C) 2009-2019 Red Hat Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

AC_INIT([libguestfs-analysis-tools], [1.41.8])

AC_CONFIG_AUX_DIR([build-aux])

AC_USE_SYSTEM_EXTENSIONS

dnl Initialize automake.
AM_INIT_AUTOMAKE(foreign subdir-objects tar-pax) dnl NB: Do not [quote] this parameter.

AC_CONFIG_MACRO_DIR([m4])

dnl Initialize libtool.
LT_INIT

dnl The C compiler environment.
dnl Define the host CPU architecture (defines 'host_cpu')
AC_CANONICAL_HOST
AC_DEFINE_UNQUOTED([host_cpu],["$host_cpu"],[Host architecture.])

dnl Check for basic C environment.
AC_PROG_CC_STDC
AC_PROG_INSTALL
AC_PROG_CPP

AC_C_PROTOTYPES
test "x$U" != "x" && AC_MSG_ERROR([Compiler not ANSI compliant])

AM_PROG_CC_C_O

AC_SUBST([WARN_CFLAGS], [-Wall])
dnl XXX Implement WERROR_CFLAGS

dnl Check support for 64 bit file offsets.
AC_SYS_LARGEFILE

dnl Check for gettext.
AM_GNU_GETTEXT([external])

dnl Check for libguestfs.
PKG_CHECK_MODULES([LIBGUESTFS], [libguestfs >= 1.40])

dnl Check for PCRE.
PKG_CHECK_MODULES([PCRE], [libpcre], [], [
    AC_CHECK_PROGS([PCRE_CONFIG], [pcre-config pcre2-config], [no])
    AS_IF([test "x$PCRE_CONFIG" = "xno"], [
        AC_MSG_ERROR([Please install the pcre devel package])
    ])
    PCRE_CFLAGS=`$PCRE_CONFIG --cflags`
    PCRE_LIBS=`$PCRE_CONFIG --libs`
])

dnl Check for perl (required).
AC_CHECK_PROG([PERL],[perl],[perl],[no])
test "x$PERL" = "xno" &&
    AC_MSG_ERROR([perl must be installed])

dnl Check for Pod::Man, Pod::Simple (for man pages).
AC_MSG_CHECKING([for Pod::Man])
if ! $PERL -MPod::Man -e1 >&AS_MESSAGE_LOG_FD 2>&1; then
    AC_MSG_ERROR([perl Pod::Man must be installed])
else
    AC_MSG_RESULT([yes])
fi
AC_MSG_CHECKING([for Pod::Simple])
if ! $PERL -MPod::Simple -e1 >&AS_MESSAGE_LOG_FD 2>&1; then
    AC_MSG_ERROR([perl Pod::Simple must be installed])
else
    AC_MSG_RESULT([yes])
fi

dnl Define a macro referring to podwrapper.pl.
PODWRAPPER="$PERL $(pwd)/podwrapper.pl"
AC_SUBST([PODWRAPPER])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile
                 boot-analysis/Makefile
                 boot-benchmark/Makefile
                 max-disks/Makefile
                 podwrapper.pl
                 qemu-boot/Makefile
                 qemu-speed-test/Makefile
                 utils/Makefile])
AC_OUTPUT
