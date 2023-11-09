#!/bin/bash 

OUTPUT="$(ls -1)"
for NAME in $OUTPUT
do
if [ "$NAME" == "build" ];
then
rm -r build
fi
if [ "$NAME" == "bin" ];
then
rm -r bin
fi
if [ "$NAME" == "log.txt" ];
then
rm log.txt
fi
done
mkdir build
cd build
cmake ../
cmake --build .
cd ../
cd bin
./calculator