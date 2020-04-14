#!/bin/bash

gbenchpath="lib/benchmark"
gtestpath="$gbenchpath/googletest"

# setup google benchmark
echo -n "Setting up google benchmark... "
git submodule update --init
echo "done"

# setup googletest
echo -n "Setting up googletest... "
if [ ! -d "$gtestpath" ]; then
    git clone https://github.com/google/googletest.git $gtestpath
    cd $gtestpath
    git checkout release-1.10.0
    cd -
fi
echo "done"
