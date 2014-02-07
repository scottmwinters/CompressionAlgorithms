#!/bin/sh

make clean
make

cp golfcore.ppm copy_of_golfcore.ppm

time ./rleEncode copy_of_golfcore.ppm
time ./rleDecode copy_of_golfcore.ppm.rle

./isCopy copy_of_golfcore.ppm golfcore.ppm

rm copy_of_golfcore.ppm

cp golfcore.ppm copy_of_golfcore.ppm

time ./lzwEncode copy_of_golfcore.ppm
time ./lzwDecode copy_of_golfcore.ppm.lzw

./isCopy copy_of_golfcore.ppm golfcore.ppm