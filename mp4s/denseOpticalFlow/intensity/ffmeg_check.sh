#!/bin/sh
ffmpeg -r 10 -i %d.png -pix_fmt yuv420p denseOpticalFlow_intensity.mp4
