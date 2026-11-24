build:
    cmake --build build

run:
    ./build/placements

debug-build:
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build

clean:
    cmake --build build --clean-first