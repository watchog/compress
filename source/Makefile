main: main.o bit_operation.o build_tree.o rwfile.o decode.o encode.o compress.o extract.o compress_extract.o
	g++ -o main main.o bit_operation.o build_tree.o rwfile.o decode.o encode.o compress.o extract.o compress_extract.o -std=c++11

main.o: main.cc head.h rwfile.h bit_operation.h build_tree.h encode.h decode.h\
	compress.h extract.h compress_extract.h
	g++ -c main.cc -std=c++11

bit_operation.o: bit_operation.cc head.h bit_operation.h
	g++ -c bit_operation.cc -std=c++11

build_tree.o: build_tree.cc head.h build_tree.h
	g++ -c build_tree.cc -std=c++11

rwfile.o: rwfile.cc head.h rwfile.h
	g++ -c rwfile.cc -std=c++11
decode.o: decode.cc head.h rwfile.h decode.h
	g++ -c decode.cc -std=c++11

encode.o: encode.cc head.h encode.h rwfile.h
	g++ -c encode.cc -std=c++11

compress.o: compress.cc head.h compress.h rwfile.h encode.h bit_operation.h
	g++ -c compress.cc -std=c++11

extract.o: extract.cc head.h extract.h decode.h rwfile.h
	g++ -c extract.cc -std=c++11

compress_extract.o: compress_extract.cc head.h compress.h extract.h
	g++ -c compress_extract.cc -std=c++11

clean:
	rm  main.o bit_operation.o build_tree.o rwfile.o decode.o encode.o compress.o extract.o compress_extract.o
