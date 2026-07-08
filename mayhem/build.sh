#!/usr/bin/env bash
# Build the synthetic libFuzzer harness. Runs inside the commit image as `mayhem` in /mayhem.
set -euo pipefail
[ -n "${SOURCE_DATE_EPOCH:-}" ] || unset SOURCE_DATE_EPOCH
: "${SANITIZER_FLAGS=-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer}"
: "${DEBUG_FLAGS:=-g -gdwarf-3}"
: "${CC:=clang}" ; : "${LIB_FUZZING_ENGINE:=-fsanitize=fuzzer}"
: "${SRC:=/mayhem}"
cd "$SRC"
# one libFuzzer binary; instrument the code under test with the sanitizers + DWARF<4 symbols
$CC $SANITIZER_FLAGS $DEBUG_FLAGS $LIB_FUZZING_ENGINE \
    "$SRC/src/fuzz_seedcheck.c" -o /mayhem/fuzz_seedcheck
echo "built /mayhem/fuzz_seedcheck"
