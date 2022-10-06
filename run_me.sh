#!/bin/sh
cmake -Bbuild -H. && cd build && make -j 8

echo "-----------------------------------------------"
echo "open dtmapp in 3 processes"
