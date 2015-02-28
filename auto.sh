#!/bin/sh
# (c) Copyright 2015 TJ <hacker@iam.tj>
# https://github.com/iam-TJ/map_area_coords_mirror
#
# Licensed on the terms of the GMU General Public License version 2
# contained in the file COPYRIGHT
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

gawk '/<img/ {$0=gensub(/(src=".*\/)(.*)(\.jpg")/, "\\1\\2-fixed\\3", 1)} /coords=/{match($0, /coords="([0-9,]+)"/, A); B=""; "./map_area_coords_mirror t831,490 414,227 "A[1] |& getline C; B="coords=\"" C "\""; $0=gensub(/coords="[0-9,]+"/, B, "g", $0)} {print}' station.html > station-fixed.html

gawk '/coords=.*title=/ {match($0, /title="([[:alnum:] ]+)"/, T); print T[1]} /coords=.*href=/ {match($0, /href="([[:alnum:] \/\.-]+)"/, H);print H[1]}  /coords=/{match($0, /coords="([0-9,]+)"/, A); B=""; "./map_area_coords_mirror 831,490 414,227 "A[1] |& getline C; B="coords=\"" C "\""; $0=gensub(/coords="[0-9,]+"/, B, "g", $0); print B; print ""}' station.html

