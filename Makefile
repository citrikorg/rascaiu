DebugFlag = -g

rascaiu:
	g++ src/rascaiu.cpp -o bin/rascaiu.bin
	bin/rascaiu.bin

clean:
	rm -rf bin/*.bin
