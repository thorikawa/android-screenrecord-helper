#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import re

bsize = 1024;

dir = "./data/"
list = os.listdir(dir)
s = 0
e = 0
count = -1
for file in list:
    match = re.match("^fb_(.*)\.raw$", file)
    if not match:
        print "skip " + file
        continue
    time = match.group(1)
    if s == 0:
        s = long(time)
    else:
        e = long(time)
    count = count + 1
    countstr = str(count).rjust(5,"0")
    tmpfile = os.path.join(dir, "fb_" + countstr + ".tmp")
    pngfile = os.path.join(dir, "fb_" + countstr + ".png")
    f = open(os.path.join(dir, file), "rb")
    fout = open(tmpfile, "wb")
    try:
        byte = f.read(12)
        while True:
            data = f.read(bsize)
            if data:
                fout.write(data)
            else:
                break
    finally:
        f.close()
        fout.close()
    ff = "ffmpeg -y -vframes 1 -vcodec rawvideo -f rawvideo -pix_fmt bgr32 -s 640*360 -i " + tmpfile + " -f image2 -vcodec png " + pngfile
    print ff
    os.system(ff)

duration = (e - s) / 1000.0
fps = count / duration
print "fps=" + str(fps)
fpsstr = str(fps)
ff = "ffmpeg -y -r " + fpsstr + " -i " + dir + "/fb_%05d.png -r " + fpsstr + " -pix_fmt yuv420p out.mp4"
os.system(ff)
