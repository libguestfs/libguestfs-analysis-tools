# libguestfs
# Copyright (C) 2011-2019 Red Hat Inc.
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

include $(top_srcdir)/subdir-rules.mk

noinst_PROGRAMS = qemu-boot

qemu_boot_SOURCES = \
	qemu-boot.c
qemu_boot_CPPFLAGS = \
	-I$(top_srcdir)/utils -I$(top_builddir)/utils
qemu_boot_CFLAGS = \
	-pthread \
	$(WARN_CFLAGS) $(WERROR_CFLAGS) \
	$(LIBGUESTFS_CFLAGS)
qemu_boot_LDADD = \
	$(top_builddir)/utils/libutils.la \
	$(LIBGUESTFS_LIBS) \
	$(LTLIBINTL)
