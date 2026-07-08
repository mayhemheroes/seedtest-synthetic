# seedtest-synthetic

Throwaway synthetic target for validating Mayhem seed-corpus **load** (cold start) and
**accumulation** (across runs) through the real CI path. Not a real project — safe to delete.

The single fuzz harness (`src/fuzz_seedcheck.c`) has three distinct branches for the three
starter seeds `CAT` / `DOG` / `FOO`, plus a nested byte cascade the fuzzer extends so the
corpus grows within a run. Seeds are wired the one sanctioned way:
`file://mayhem/<target>/testsuite` + the server-accumulated `testsuite.tar`.

<!-- kick Actions workflow registration -->
