#!/bin/bash

gbenchpath="lib/benchmark"
gtestpath="$gbenchpath/googletest"

# setup google benchmark
echo "Setting up google benchmark... "
git submodule update --init
echo "done"

# setup googletest
echo "Setting up googletest... "
if [ ! -d "$gtestpath" ]; then
    git clone https://github.com/google/googletest.git $gtestpath
    cd $gtestpath
    git checkout -q release-1.10.0
    cd -
fi
echo "done"
