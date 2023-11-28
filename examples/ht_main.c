#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/bf.h"
#include "../include/hash_file.h"
#include "../include/record.h"


// #define MAX_RECORDS 1700 // you can change it if you want
#define BUCKETS_NUM 13  // you can change it if you want
#define FILE_NAME "data.db"

#define CALL_OR_DIE(call)     \
  {                           \
    HT_ErrorCode code = call; \
    if (code != HT_OK)        \
    {                         \
      printf("Error\n");      \
      exit(code);             \
    }                         \
  }
const char* names[] = {
  "Yannis",
  "Christofos",
  "Sofia",
  "Marianna",
  "Vagelis",
  "Maria",
  "Iosif",
  "Dionisis",
  "Konstantina",
  "Theofilos",
  "Giorgos",
  "Dimitris"
};

const char* surnames[] = {
  "Ioannidis",
  "Svingos",
  "Karvounari",
  "Rezkalla",
  "Nikolopoulos",
  "Berreta",
  "Koronis",
  "Gaitanis",
  "Oikonomou",
  "Mailis",
  "Michas",
  "Halatsis"
};

const char* cities[] = {
  "Athens",
  "San Francisco",
  "Los Angeles",
  "Amsterdam",
  "London",
  "New York",
  "Tokyo",
  "Hong Kong",
  "Munich",
  "Miami"
};

int main()
{
  printf("I work here 69\n");
  CALL_OR_DIE(HT_Init());
  printf("I work here 71\n");
  int indexDesc;
  CALL_OR_DIE(HT_CreateIndex(FILE_NAME, BUCKETS_NUM));
  printf("I work here 74\n");
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc));
  printf("I work here 76\n");

  Record record;
  srand(12569874);
  int r;
  printf("Insert Entries\n");
  printf("I work here 82\n");

  for (int id = 0; id < MAX_RECORDS; ++id)
  {
  printf("I work here 86\n");
    record.id = id;
    r = rand() % 12;
    memcpy(record.name,names[r], strlen(names[r]) + 1);
    r = rand() % 12;
    memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
    r = rand() % 10;
    memcpy(record.city, cities[r], strlen(cities[r]) + 1);

    CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
    printf("I work here 96");
  }

  printf("RUN PrintAllEntries\n");
  int id = rand() % MAX_RECORDS;
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));

  printf("Print Entry with id = %d\n", id);
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id)); // must print something like : Entry doesn't exist or nothing at all

  id = 0;
  printf("Print Entry with id = %d\n", id);
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  id = 1689;
  printf("Print Entry with id = %d\n", id);
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  record.id = 1689;
  CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  printf("Print Entry with id = %d\n", id);
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  id = 30545;
  printf("Print Entry with id = %d\n", id);
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  CALL_OR_DIE(HT_CloseFile(indexDesc));
  BF_Close();
}