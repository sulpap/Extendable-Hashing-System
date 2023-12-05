#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/bf.h"
#include "../include/hash_file.h"
#include "../include/record.h"

// #define MAX_RECORDS 1700 // you can change it if you want
#define BUCKETS_NUM 13 // you can change it if you want
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
const char *names[] = {
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
    "Dimitris"};

const char *surnames[] = {
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
    "Halatsis"};

const char *cities[] = {
    "Athens",
    "San Francisco",
    "Los Angeles",
    "Amsterdam",
    "London",
    "New York",
    "Tokyo",
    "Hong Kong",
    "Munich",
    "Miami"};
/*
int main()
{
  CALL_OR_DIE(HT_Init());

  int indexDesc, indexDesc2;
  // open file1
  CALL_OR_DIE(HT_CreateIndex(FILE_NAME, BUCKETS_NUM));
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc));

  Record record;
  srand(12569874);
  int r;

  // first file
  printf("Insert Entries in data.db\n");
  for (int id = 0; id < 5; id++)
  {
    record.id = id;
    r = rand() % 5;
    memcpy(record.name, names[r], strlen(names[r]) + 1);
    r = rand() % 6;
    memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
    r = rand() % 7;
    memcpy(record.city, cities[r], strlen(cities[r]) + 1);

    CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  }
  printf("--------------------------------------\n");


  printf("RUN PrintAllEntries\n");
  int id = rand() % MAX_RECORDS;
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));
  // CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));

  id = 1;
  CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  printf("Print Entry with id = %d\n", id);
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  id = 2;
  CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  printf("Print Entry with id = %d\n", id);
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  id = 3;
  printf("Print Entry with id = %d\n", id);
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  id = 4;
  CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  printf("Print Entry with id = %d\n", id);
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, &id));

  CALL_OR_DIE(HT_CloseFile(indexDesc));
  BF_Close();
}
*/
int main()
{
  CALL_OR_DIE(HT_Init());

  int indexDesc;
  // Open file1
  CALL_OR_DIE(HT_CreateIndex(FILE_NAME, BUCKETS_NUM));
  CALL_OR_DIE(HT_OpenIndex(FILE_NAME, &indexDesc));

  Record record;
  srand(12569874);
  int r;

  // Insert enough records to trigger expansion
  printf("Inserting records to trigger expansion...\n");
  for (int id = 0; id < 2 * BUCKETS_NUM; id++)
  {
    record.id = id;
    r = rand() % 5;
    memcpy(record.name, names[r], strlen(names[r]) + 1);
    r = rand() % 6;
    memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
    r = rand() % 7;
    memcpy(record.city, cities[r], strlen(cities[r]) + 1);

    CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  }

  // Print all entries to see the expanded hash table
  printf("Print all entries after expansion:\n");
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));

  // Insert enough records to trigger bucket splitting
  printf("\nInserting records to trigger bucket splitting...\n");
  for (int id = 0; id < BUCKETS_NUM; id++)
  {
    record.id = id;
    r = rand() % 5;
    memcpy(record.name, names[r], strlen(names[r]) + 1);
    r = rand() % 6;
    memcpy(record.surname, surnames[r], strlen(surnames[r]) + 1);
    r = rand() % 7;
    memcpy(record.city, cities[r], strlen(cities[r]) + 1);

    CALL_OR_DIE(HT_InsertEntry(indexDesc, record));
  }
  printf("--------------------------------------\n");
  printf("--------------------------------------\n");
  // Print all entries to see the bucket splitting
  printf("Print all entries after bucket splitting:\n");
  printf("--------------------------------------\n");
  printf("--------------------------------------\n");
  CALL_OR_DIE(HT_PrintAllEntries(indexDesc, NULL));

  CALL_OR_DIE(HT_CloseFile(indexDesc));
  BF_Close();

  return 0;
}