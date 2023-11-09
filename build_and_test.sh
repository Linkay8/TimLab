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
cmake ../test
cmake --build .
cd ../
cd bin
echo "Running tests..."
timeout -s SIGKILL 2m valgrind --leak-check=yes --log-file=../log.txt ./tokenize_test
if [[ $? -ne 0 ]]
then
        echo "Ooops, there are failed tests :("
        exit 1
fi
cd ../
echo "Valgrind log:"
cat log.txt
python valgrind_parser.py
