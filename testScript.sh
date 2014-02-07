#!/bin/sh

make clean
make

cp $1 copy 

time ./rleEncode copy
time ./rleDecode copy.rle

./isCopy $1 copy

rm copy*

cp $1 copy

time ./lzwEncode copy
time ./lzwDecode copy.lzw

./isCopy $1 copy

rm copy*