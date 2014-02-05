lab2: rle_encode.o rle_decode.o lzw_encode.o lzw_decode.o
	gcc -Wall --pednatic -O2 rle_encode.o -o rleEncode 
	gcc -Wall --pedantic -O2 rle_decode.o -o rleDecode
	gcc -Wall --pedantic -O2 lzw_encode.o -o lzwEncode
	gcc -Wall --pedantic -O2 lzw_decode.o -o lzwDecode 

rle: rle_encode.c rle_decode.c
	gcc -Wall --pedantic -O2 -c rle_encode.c
	gcc -Wall --pedantic -O2 -c rle_decode.c

lzw: lzw_encode.c lzw_decode.c
	gcc -Wall --pedantic -O2 -c lzw_encode.c
	gcc -Wall --pedantic -O2 -c lzw_decode.c

clean:
	rm *.o rleEncode rleDecode lzwEncode lzwDecode
