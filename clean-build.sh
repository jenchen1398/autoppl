# directory where current shell script resides
PROJECTDIR=$(dirname "$BASH_SOURCE")

cd "$PROJECTDIR"

mode=$1 # debug/release mode
shift   # shift command-line arguments
        # the rest are cmake command-line arguments

mkdir -p build && cd build

# if debug directory does not exist, create it
mkdir -p debug
# if release directory does not exist, create it
mkdir -p release

# if debug mode
if [ "$mode" = "debug" ]; then
    cd debug
# if release mode
elif [ "$mode" = "release" ]; then
    cd release
else
    echo "usage: $0 <debug/release> [cmake options]" 1>&2
    exit 1
fi

rm -rf *
cmake ../../ "$@"
cmake --build . -- -j12
