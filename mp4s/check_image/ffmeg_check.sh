#!/bin/sh
for i in 1 2 3 4 5
do
	ffmpeg -r 10 -i $1/$i/check_image/%d.png -pix_fmt yuv420p check_image_$i.mp4
done
