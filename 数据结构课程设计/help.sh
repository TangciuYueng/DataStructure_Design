#!/bin/bash

cd /home/ytc/Documents/数据结构程序设计
touch makefile
echo 'TARGET = out
SRC = *.cpp
RM = rm -f
GXX = g++
$(TARGET):$(SRC)
	$(GXX) $(SRC) -O $(TARGET)
.PHONY: clean
clean:
	$(RM) $(TARGET)
' > makefile
for i in {1..10}
do
	cp M* $i'_'*
	cd $i'_'*
	make
	chmod 777 out
	echo 'file'$i' changed done!'
	cd ../
done
