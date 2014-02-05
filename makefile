all: rle lzw 

rle: rle_encode.c rle_decode.c
	gcc -Wall --pedantic -O2 -c rle_encode.c
	gcc -Wall --pedantic -O2 -c rle_decode.c
	gcc -Wall --pedantic -O2 rle_encode.o -o rleEncode 
	gcc -Wall --pedantic -O2 rle_decode.o -o rleDecode

lzw: lzw_encode.c lzw_decode.c
	gcc -Wall --pedantic -O2 -c lzw_encode.c
	gcc -Wall --pedantic -O2 -c lzw_decode.c
	gcc -Wall --pedantic -O2 lzw_encode.o -o lzwEncode
	gcc -Wall --pedantic -O2 lzw_decode.o -o lzwDecode 

clean:
	rm *.o rleEncode rleDecode lzwEncode lzwDecode
