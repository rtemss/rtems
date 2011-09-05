#!/bin/sh
#
#  $Id: search-id.sh,v 1.3 2011/05/17 20:39:39 joel Exp $
#

find $1 -type f -a ! -name "*.scn" -a ! -name "bsp_specs" -a \
	-print  > /tmp/$$.0
find $1 -type f -a ! -name "*.scn" -a ! -name "bsp_specs" -a \
	-exec grep -l '$Id' {} \;  > /tmp/$$.1

diff /tmp/$$.0 /tmp/$$.1 > /tmp/$$.2

grep "<" /tmp/$$.2 | sed 's/< //' >&1

rm -f /tmp/$$*
