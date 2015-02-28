# HTML map area coords mirror

A simple tool that mirrors coordinates about an adjustable center axis.
Developed to support quickly altering the coordinates when the associated
image was mirrored - avoiding lots of tedious manual adjustments, or re-drawing
the <map><area> coords.

E.g. for an image 831x490 with the mirror axis centered at 414,227:

    $ map_area_coords_mirror 831,490 414,227 255,274,510,274,510,350,255,350,255,274
    574,197,319,197,319,121,574,121,574,197

I've included a supporting shell script an HTML file it has been used with. The script "auto.sh" uses (g)awk to read an modify an HTML file by finding the lines containing <area coords="..."> and passing the coordinates out to this
tool for modification, and then replacing the coordinates in the final output.

