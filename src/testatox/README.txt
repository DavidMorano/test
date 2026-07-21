TESTSTRTOX

This program tests the |strtox(3u)| subroutines.

Results:
Currently, all of the tests pass on all of my subroutines (of the
flavored |strtox{x}|).  But the current tests are not completely
comprehensive to test my |longlong| subroutines, so there could
still be hidden failures there (although my guess is there is not).

Cavæats:
Although my versions try to replicate the same signatures and
semantics of the stndard versions, I actually provide a slightly
enhanced feature set (for fun).  So it is theoretically possible
that someday someone can write a test case that breaks on my
subrotines.  But any new test cases would first have to be incorporated
into the code here.  So that is not going to happen automatically.

