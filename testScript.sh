#!/bin/sh

make clean
make

cp $1 test_file

echo "\nRunning RLE Compression"
time ./rleEncode test_file

echo "\nRunning RLE Decompression"
time ./rleDecode test_file.rle

echo "\nTesting..."
./isCopy test_file $1

echo "\nRLE Compression Statistics: \n"
echo "Original File: "
ls -l $1 | awk '{print $5}'

echo "Compressed File"
ls -l test_file.rle | awk '{print $5}'

echo "Uncompressed File"
ls -l test_file | awk '{print $5}'

rm test_file*

cp $1 test_file

echo "\nRunning LZW Compression"
time ./lzwEncode test_file

echo "\nRunning LZW Decompression"
time ./lzwDecode test_file.lzw

echo "\nTesting..."
./isCopy test_file $1

echo "\nLZE Compression Statistics: \n"
echo "Original File: "
ls -l $1 | awk '{print $5}'

echo "Compressed File"
ls -l test_file.lzw | awk '{print $5}'

echo "Uncompressed File"
ls -l test_file | awk '{print $5}'

rm test_file*

make clean
