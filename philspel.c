/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philspel.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  // readDictionary(argv[1]);
  readDictionaryPro(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  // processInput();
  processInputPro();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}

/*
 * This should hash a string to a bucket index.  Void *s can be safely cast
 * to a char * (null terminated string) and is already done for you here 
 * for convenience.
 */
unsigned int stringHash(void *s) {
  char *string = (char *)s;
  // -- TODO --
  // DJB2 algorithm
  unsigned int hash = 5381;
  int c;

  while ((c = *string++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

/*
 * This should return a nonzero value if the two strings are identical 
 * (case sensitive comparison) and 0 otherwise.
 */
int stringEquals(void *s1, void *s2) {
  // -- TODO --
  char *p = (char *)s1;
  char *q = (char *)s2;
  int res = 1;
  while (*p != 0) {
    if (*p != *q) {
      res = 0;
      break;
    }
    p++;
    q++;
  }

  if (*q != 0) {
    res = 0;
  }

  return res;
}

/*
 * This function should read in every word from the dictionary and
 * store it in the hash table.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, return.  You will need to allocate
 * (using malloc()) space for each word.  As described in the spec, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length.  You CANNOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(1)
 * to cleanly exit the program.
 *
 * Since the format is one word at a time, with new lines in between,
 * you can safely use fscanf() to read in the strings until you want to handle
 * arbitrarily long dictionary chacaters.
 */
void readDictionary(char *dictName) {
  // -- TODO --
  FILE *fp;
  char buf[64] = {0};

  fp = fopen(dictName, "r");
  if (fp == NULL) {
    fprintf(stderr, "File doesn't exist\n");
    exit(1);
  }

  while (fgets(buf, sizeof buf, fp)) {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = '\0';  // convert \n to \0
    char *string = (char *)malloc(sizeof(char) * (strlen(buf) + 1));
    memset(string, 0, sizeof(char) * (strlen(buf) + 1));
    memcpy(string, buf, strlen(buf));
    insertData(dictionary, string, string);
  }
}

/*
 * This should process standard input (stdin) and copy it to standard
 * output (stdout) as specified in the spec (e.g., if a standard 
 * dictionary was used and the string "this is a taest of  this-proGram" 
 * was given to stdin, the output to stdout should be 
 * "this is a teast [sic] of  this-proGram").  All words should be checked
 * against the dictionary as they are input, then with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not found by appending " [sic]" after the error.
 *
 * Since we care about preserving whitespace and pass through all non alphabet
 * characters untouched, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), meaning you will probably have
 * to get characters from stdin one at a time.
 *
 * Do note that even under the initial assumption that no word is longer than 60
 * characters, you may still encounter strings of non-alphabetic characters (e.g.,
 * numbers and punctuation) which are longer than 60 characters. Again, for the 
 * final 20% of your grade, you cannot assume words have a bounded length.
 */
void toLowCaseExcepOne(char *buf) {
  int size = strlen(buf);
  for (int i = 1; i < size; ++i) {
    if (buf[i] >= 'A' && buf[i] <= 'Z') {
      buf[i] = tolower(buf[i]);
    }
  }
}

void toLowCaseOne(char *buf) {
  int size = strlen(buf);
  if (size > 0) {
    buf[0] = tolower(buf[0]);
  }
}

void outputOneWord(char *buf) {
  char buf_dup[strlen(buf) + 1];
  memcpy(buf_dup, buf, strlen(buf) + 1);
  if (findData(dictionary, buf_dup) != NULL) {      // CASE 1
    printf("%s", buf);
  } else {
    toLowCaseExcepOne(buf_dup);
    if (findData(dictionary, buf_dup) != NULL) {    // CASE 3
      printf("%s", buf);
    } else {
      toLowCaseOne(buf_dup);
      if (findData(dictionary, buf_dup) != NULL) {  // CASE 2
        printf("%s", buf);
      } else {                                      // NOT MATCH
        printf("%s [sic]", buf);
      }
    }
  }
}


void processInput() {
  // -- TODO --
  int c;
  char buf[64] = {0};
  int i = 0;

  while ((c = getchar()) != EOF) {
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {
      if (strlen(buf) > 0) {
        outputOneWord(buf);
        memset(buf, 0, sizeof buf);
        i = 0;
      }
      putchar(c);
    } else {
      buf[i++] = c;
    }
  }
  if (strlen(buf) > 0) {
    outputOneWord(buf);
  }

  exit(0);
}


/////////////////////////////////////////
/////////////* VERSION PRO */////////////
/////////////////////////////////////////

void readDictionaryPro(char *dictName) {
  // -- TODO --
  FILE *fp;
  const unsigned int min_size = 64;

  fp = fopen(dictName, "r");
  if (fp == NULL) {
    fprintf(stderr, "File doesn't exist\n");
    exit(1);
  }

  while (1) {
    char *buffer = (char *)malloc(sizeof(char) * (min_size));
    memset(buffer, 0, sizeof(char) * (min_size));
    unsigned int size = min_size;
    
    if (fgets(buffer, min_size, fp) == NULL) {
      free(buffer);
      break;
    }

    // if more than min_size, resize the buffer
    while ( buffer[size - 1 - 1] != '\0' 
            && buffer[size - 1 - 1] != '\n' ) {
      // buffer is full now: strlen(buffer) == size
      size *= 2;
      char *tmpbuf = (char *)malloc(sizeof(char) * (size));
      memset(tmpbuf, 0, sizeof(char) * (size));
      
      memcpy(tmpbuf, buffer, strlen(buffer));
      // example: from 63 -> 127, increase 64 bytes.
      // buf[63] used to be \0.
      // new bytes occupy from buf[63] to buf[126] (64 bytes),
      // fgets's arg n including the final \0 (buf[127]),
      // so here the n is size / 2 + 1 = 64 + 1 = 65.
      fgets(tmpbuf + strlen(buffer), size / 2 + 1, fp);

      free(buffer);
      buffer = tmpbuf;
    }

    if (strlen(buffer) > 0) {
      if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0'; // convert \n to \0
    }
    insertData(dictionary, buffer, buffer);
  }
}


void processInputPro() {
  // -- TODO --
  int c;
  unsigned int size = 64;
  char *buf = (char *)malloc(sizeof(char) * (size));
  memset(buf, 0, sizeof(char) * (size));
  int i = 0;

  while((c = getchar()) != EOF) {
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')) {
      if (strlen(buf) > 0) {
        outputOneWord(buf);
        memset(buf, 0, sizeof(char) * (size));
        i = 0;
      }
      putchar(c);
    } else {
      buf[i] = c;

      if (i == size - 2) { // resize the buf size
        size *= 2;
        char *tmpbuf = (char *)malloc(sizeof(char) * (size));
        memset(tmpbuf, 0, sizeof(char) * (size));

        memcpy(tmpbuf, buf, strlen(buf));
        
        free(buf);
        buf = tmpbuf;
      }
      i++;
    }
  }
  if (strlen(buf) > 0)
    outputOneWord(buf);
  free(buf);

  exit(0);
}