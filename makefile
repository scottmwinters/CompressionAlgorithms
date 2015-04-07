all: rle lzw copy

rle: rle_encode.c rle_decode.c
	gcc -Wall --pedantic -O2 -c rle_encode.c -o rleEncode
	gcc -Wall --pedantic -O2 -c rle_decode.c -o rleDecode

lzw: lzw_encode.c lzw_decode.c
	gcc -Wall --pedantic -O2 -c lzw_encode.c -o lzwEncode
	gcc -Wall --pedantic -O2 -c lzw_decode.c -o lzwDecode

copy: test_if_copy.c
	gcc -Wall --pedantic -O2 -c test_if_copy.c -o isCopy

clean:
	rm rleEncode rleDecode lzwEncode lzwDecode isCopy
