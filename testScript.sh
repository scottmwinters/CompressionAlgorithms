#!/bin/sh

make clean
make

cp $1 copy 

echo "\n\nRLE Compression\n"
time ./rleEncode copy

echo "\n\nRLE Decompression\n"
time ./rleDecode copy.rle

echo "\n\nTesting...\n"
./isCopy $1 copy

rm copy*

cp $1 copy

echo "\n\nLZW Compression\n"
time ./lzwEncode copy

echo "\n\nLZW Decompression\n"
time ./lzwDecode copy.lzw

echo "\n\nTesting...\n"
./isCopy $1 copy

# rm copy*