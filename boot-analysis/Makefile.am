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

EXTRA_DIST = boot-analysis.pod

noinst_PROGRAMS = boot-analysis

boot_analysis_SOURCES = \
	boot-analysis.c \
	boot-analysis.h \
	boot-analysis-timeline.c \
	boot-analysis-utils.c \
	boot-analysis-utils.h
boot_analysis_CPPFLAGS = \
	-I$(top_srcdir)/utils -I$(top_builddir)/utils \
	-I$(top_srcdir)/lib -I$(top_builddir)/lib
boot_analysis_CFLAGS = \
	-pthread \
	$(WARN_CFLAGS) $(WERROR_CFLAGS) \
	$(PCRE_CFLAGS) \
	$(LIBGUESTFS_CFLAGS)
boot_analysis_LDADD = \
	$(top_builddir)/utils/libutils.la \
	$(LIBGUESTFS_LIBS) \
	$(PCRE_LIBS) \
	$(LTLIBINTL) \
	-lm

# Manual page.
# It should be noinst_MANS but that doesn't work.
noinst_DATA = boot-analysis.1

boot-analysis.1: boot-analysis.pod
	$(PODWRAPPER) \
	  --man $@ \
	  --license GPLv2+ \
	  --warning safe \
	  $<
