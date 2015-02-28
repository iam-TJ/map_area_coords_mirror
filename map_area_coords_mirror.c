/* HTML image map area mirror-coordinates tool 
 * (c) Copyright 2015 TJ <hacker@iam.tj>
 * https://github.com/iam-TJ/map_area_coords_mirror
 *
 * A simple tool that mirrors coordinates about an adjustable center line.
 * Developed to support quickly altering the coordinates when the associated
 * image was mirrored - avoiding lots of tedious manual adjustments, or re-drawing
 * the <map><area> coords.
 *
 * E.g. for an image 831x490 with the mirror axis centered at 414,227:
 *
 * $ map_area_coords_mirror 831,490 414,227 255,274,510,274,510,350,255,350,255,274
 * 574,197,319,197,319,121,574,121,574,197
 *
 * Licensed on the terms of the GMU General Public License version 2
 * contained in the file COPYRIGHT
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
  int x;
  int y;
};

struct Point* string_to_point(char *s, struct Point *point)
{
  if (s && point && strlen(s) > 3) {
    char *p = NULL;
    point->x = (int)strtol(s, &p, 10);
    if (p)
      point->y = (int)strtol(p+1, &p, 10);
    return point;
  }
  else {
    fprintf(stderr, "%s\n", "Invalid coordinate");
    return NULL;
  }
}

int
main(int argc, char **argv, char **env)
{
  if (argc < 4) {
    fprintf(stderr, "Usage: %s [%s]\n", argv[0], "<size-x,size-y> <mirror-x,mirror-y> <x,y,... HTML map area coordinates list>");
  }
  else {
    struct Point size, mirror, point, inv;
    if (!string_to_point(argv[1], &size)) {
      fprintf(stderr, "Error: %s\n", "Illegal size coordinate string");
    }
    if (!string_to_point(argv[2], &mirror)) {
      fprintf(stderr, "Error: %s\n", "Illegal mirror coordinate string");
    }
    else {
      size_t len = strlen(argv[3]);
      char *p = argv[3];
      char *q = p;
      char *z = p + len - 1; /* last character of string */
      for (unsigned int c = 0; *p; ++p) {
        if (*p == ',') {
          ++c;
        }
        if ((c && c%2 == 0) || p == z) {
          /* every even-numbered comma denotes the end of a coordinate pair */
          if (string_to_point(q, &point)) {
            inv.x = ((size.x - 1) / 2) + (mirror.x - point.x);
            inv.y = ((size.y - 1) / 2) + (mirror.y - point.y);
            printf("%d,%d", inv.x, inv.y);
            if (p != z) /* all but last pair end with a comma */
              printf("%s", ",");
          }
          q = p + 1;
          c = 0; /* reset comma count */
        }
      }
      printf("%s", "\n");
    }

  }
  return 0;
}

