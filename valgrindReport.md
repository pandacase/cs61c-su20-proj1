
## Sample Test (less than 60 bytes one word)

```sh
➜ make && cat sampleInput | valgrind ./philspel sampleDictionary
gcc -g -Wall -std=c99 -c philspel.c
gcc -g -Wall -o philspel philspel.o hashtable.o
==775693== Memcheck, a memory error detector
==775693== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==775693== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==775693== Command: ./philspel sampleDictionary
==775693== 
Creating hashtable
Loading dictionary sampleDictionary
Dictionary loaded
Processing stdin
this is a sample of normal words,
this is a misspelled [sic] word.
nick [sic] Nick NiCK wEAVER [sic] weaver [sic] Weaver.
weird [sic] Weird [sic] WEIRD [sic] weIrD CapS!
this!is3normal
this!is$wrng [sic]$words
this is a bad sentences [sic]
230948 0923490290 234 234  )#@$)(()*@#)(@#)(%)(@#$)(*)(&@#$*&!@) @#(*$&
this has [sic] no [sic] last [sic] linefeed [sic]==775693== 
==775693== HEAP SUMMARY:
==775693==     in use at exit: 19,776 bytes in 31 blocks
==775693==   total heap usage: 36 allocs, 5 frees, 29,120 bytes allocated
==775693== 
==775693== LEAK SUMMARY:
==775693==    definitely lost: 0 bytes in 0 blocks
==775693==    indirectly lost: 0 bytes in 0 blocks
==775693==      possibly lost: 0 bytes in 0 blocks
==775693==    still reachable: 19,776 bytes in 31 blocks
==775693==         suppressed: 0 bytes in 0 blocks
==775693== Rerun with --leak-check=full to see details of leaked memory
==775693== 
==775693== For lists of detected and suppressed errors, rerun with: -s
==775693== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Custom Test (more than 60 bytes one word)

```sh
➜ make && cat customInput| valgrind ./philspel customDictionary
gcc -g -Wall -std=c99 -c philspel.c
gcc -g -Wall -o philspel philspel.o hashtable.o
==772378== Memcheck, a memory error detector
==772378== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==772378== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==772378== Command: ./philspel customDictionary
==772378== 
Creating hashtable
Loading dictionary customDictionary
Dictionary loaded
Processing stdin
this is [sic] a [sic] sample [sic] of [sic] normal [sic] words [sic],
abcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJ
hi [sic]!this!
abcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghijABCDEFGHIJabcdefghij [sic]==772378== 
==772378== HEAP SUMMARY:
==772378==     in use at exit: 18,912 bytes in 7 blocks
==772378==   total heap usage: 16 allocs, 9 frees, 28,832 bytes allocated
==772378== 
==772378== LEAK SUMMARY:
==772378==    definitely lost: 0 bytes in 0 blocks
==772378==    indirectly lost: 0 bytes in 0 blocks
==772378==      possibly lost: 0 bytes in 0 blocks
==772378==    still reachable: 18,912 bytes in 7 blocks
==772378==         suppressed: 0 bytes in 0 blocks
==772378== Rerun with --leak-check=full to see details of leaked memory
==772378== 
==772378== For lists of detected and suppressed errors, rerun with: -s
==772378== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```