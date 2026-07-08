#include <stdint.h>
#include <stddef.h>

// Synthetic seed-accumulation harness. Two purposes:
//  (1) three DISTINCT branches for the three starter seeds CAT / DOG / FOO, so each
//      cold seed lights up its own edge (proves the 3 local seeds actually loaded);
//  (2) a nested byte-compare cascade on "MAYHEMSEED" the fuzzer solves one byte at a
//      time, minting a NEW corpus entry per level, so run 1 grows the corpus and run 2
//      must start from a larger accumulated set. No crashes on purpose.
static volatile int sink;
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) return 0;
  if (size >= 3 && data[0]=='C' && data[1]=='A' && data[2]=='T') { sink = 101; }
  else if (size >= 3 && data[0]=='D' && data[1]=='O' && data[2]=='G') { sink = 102; }
  else if (size >= 3 && data[0]=='F' && data[1]=='O' && data[2]=='O') { sink = 103; }

  // nested cascade: each additional matching byte opens a fresh edge + corpus entry
  if (size > 0 && data[0] == 'M') {
    sink = 200;
    if (size > 1 && data[1] == 'A') {
      sink = 201;
      if (size > 2 && data[2] == 'Y') {
        sink = 202;
        if (size > 3 && data[3] == 'H') {
          sink = 203;
          if (size > 4 && data[4] == 'E') {
            sink = 204;
            if (size > 5 && data[5] == 'M') {
              sink = 205;
              if (size > 6 && data[6] == 'S') {
                sink = 206;
                if (size > 7 && data[7] == 'E') {
                  sink = 207;
                  if (size > 8 && data[8] == 'E') {
                    sink = 208;
                    if (size > 9 && data[9] == 'D') {
                      sink = 209;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
