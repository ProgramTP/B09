// Add necessary #include's.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "records.h"

// You may add helper functions. Actually there is a reason you should!

int get_yob(FILE *f, const char *name, short *pyob)
{
  fseek(f, 0, SEEK_SET);
  record *test = (record *)malloc(sizeof(record));
  while(1){
    fread(test, sizeof(record), 1, f);
    if(feof(f)){
      break;
    }
    char temp[test->name_len];
    strncat(temp, test->name, test->name_len);
    if (strcmp(temp, name) == 0){
      *pyob = test->yob;
      return 1;
    }
  }
  return 0;
}

void set_yob(FILE *f, const char *name, short yob)
{
  fseek(f, 0, SEEK_SET);
  int iterator = 0;
  record *test = (record *)malloc(sizeof(record));
  while(1){
    fread(test, sizeof(record), 1, f);
    iterator++;
    if(feof(f)){
      break;
    }
    
    char temp[test->name_len];
    strncat(temp, test->name, test->name_len);
    if (strcmp(temp, name) == 0){
      if(fseek(f, (sizeof(record)*iterator)-2, SEEK_SET) == 0){
        fwrite(&yob, sizeof(yob), 1, f);
        return;
      }
    }
  }
  record *new = (record *)malloc(sizeof(record));
  strcpy(new->name, name);
  new->yob = yob;
  new->name_len = strlen(name);
  fwrite(new, sizeof(record), 1, f);
}
