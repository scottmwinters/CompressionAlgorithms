#!/bin/sh

make clean
make

cp $1 test_file

echo "\n\nRLE Compression\n"
time ./rleEncode test_file

echo "\n\nRLE Decompression\n"
time ./rleDecode test_file.rle

echo "\n\nTesting...\n"
./istest_file $1 test_file

rm test_file*

cp $1 test_file

echo "\n\nLZW Compression\n"
time ./lzwEncode test_file

echo "\n\nLZW Decompression\n"
time ./lzwDecode test_file.lzw

echo "\n\nTesting...\n"
./isCopy $1 test_file

rm test_file*
