#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
sqlite3 *db;
vector<int> results;

///
///
/// useless function
///
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

//
//
// use for query in splite
//
//
static int query_callback(void *para, int nCount, char **pValue, char **pName) {
  string s;
  for (int i = 0; i < nCount; i++) {
    if (i % 2) {
      // s+=pValue[i];
      // s+="\n";
      results.push_back(atoi(pValue[i]));
    }
  }
  cout << s << endl;
  return 0;
}

//
//
// use for open database in splite
//
//
void open_database(char *filename) {
  /* Open database */
  int rc;
  rc = sqlite3_open(filename, &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    exit(0);
  } else {
    fprintf(stdout, "Opened database successfully\n");
  }
}

//
//
// use for create database in splite
//
//

void create_database() {
  // if(db == NULL) fprintf(stderr, "No database: %s\n", zErrMsg);
  /* Create SQL statement */
  int rc;
  char *zErrMsg = 0;
  char sql[300];
  sprintf(sql,
          "CREATE TABLE PAIR("
          "Key INT PRIMARY KEY,"
          "Value           INT);");
  /* Execute SQL statement */
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table created successfully\n");
  }
}

//
//
// use for clearup database in splite
//
//
void Dropout() {
  char sql[300];
  char *zErrMsg = 0;
  sprintf(sql, "DROP TABLE 'PAIR';");
  // int rc = 0;
  int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL_Dropout error: %s\n", zErrMsg);
    //注意，执行失败，需要清理错误码的内存空间
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Records Dropout successfully\n");
  }
}

//
//
// use for insert database in splite
//
//
void insert(int key, int value) {
  char sql[300];
  char *zErrMsg = 0;
  sprintf(sql,
          "INSERT INTO PAIR VALUES(  \
           %d ,%d);",
          key, value);

  /* Execute SQL statement */
  int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    // fprintf(stdout, "insert successfully\n");
  }
}

//
//
// use for erase database in splite
//
//
bool erase(int key) {
  char sql[3000];
  char *zErrMsg = 0;
  sprintf(sql, "DELETE FROM PAIR WHERE Key=%d;", key);

  int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL erase error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
    return false;
  } else {
    // fprintf(stdout, "erase successfully\n");
    return true;
  }
}

//
//
// use for query database in splite
//
//
void query(int key) {
  char sql[300];
  char *zErrMsg = 0;
  sprintf(sql, "SELECT * from PAIR WHERE Key == %d;", key);
  const char *data = "Callback function called";
  int rc = sqlite3_exec(db, sql, query_callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL query error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    // fprintf(stdout, "query successfully\n");
  }
}

//
//
// std run test!
// only query will return the value and push into the vector
//
//
void tester(string filename) {
  ifstream File(filename.c_str());

  char cmd;
  int key, value;
  while (File >> cmd) {
    if (cmd == 'i') {
      File >> key >> value;
      insert(key, value);
    } else if (cmd == 'e') {
      File >> key;
      erase(key);
    } else if (cmd == 'q') {
      File >> key;
      query(key);
    } else {
      puts("bad_command");
    }
  }

  File.close();
}

//
//
// std run B+Tree!
// only query will return the value and push into the vector
//
//
vector<int> BTree_results;
void get_result(FILE *fp) {
  char buf[100];
  int result;
  if (!fp) {
    return;
  }
  while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != 0) {
    result = atoi(buf);
    BTree_results.push_back(result);
    // cout << result << endl;
  }
}

void BTree_tester(string filename) {
  FILE *fp;
  fp = NULL;
  string program_name = "hello_world";
  string cmd = "./" + program_name + " < " + filename;
  fp = popen(cmd.c_str(), "r");
  if (!fp) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  get_result(fp);
  pclose(fp);
}

int main(int argc, char *argv[]) {
  bool big = true;
  open_database("std_test.db");

  // clear database
  Dropout();

  // create database
  create_database();

  if (big) {
    // this test for big data

    // first initial dataset
    string dataset = "insert.data";
    tester(dataset);
    BTree_tester(dataset);

    // then for query
    string test_name = "query.data";
    BTree_tester(test_name);
    tester(test_name);

    for (int i = 0; i < results.size(); i++) {
      if (results[i] != BTree_results[i]) {
        cout << "wrong at big insert + query" << endl;
        return 0;
      }
    }
    // then for erase & query
    // test_name = "erase_query.data";
    // BTree_tester(test_name);
    // tester(test_name);

    // for (int i = 0; i < results.size(); i++) {
    //  if (results[i] != BTree_results[i]) {
    //    cout << "wrong at erase + query" << endl;
    //    return 0;
    //  }
    // }
    cout << "PASS" << endl;
  } else {
    // this test for open and close !

    // first initial dataset
    for (int i = 1; i <= 3; i++) {
      string dataset = "insert" + to_string(i) + ".data";
      tester(dataset);
      BTree_tester(dataset);

      // then for query
      string test_name = "query" + to_string(i) + ".data";
      BTree_tester(test_name);
      tester(test_name);

      for (int i = 0; i < results.size(); i++) {
        if (results[i] != BTree_results[i]) {
          cout << "wrong at open and close " << i << endl;
          return 0;
        }
      }
      cout << "PASS" << endl;
    }
  }

  sqlite3_close(db);

  return 0;
}

/*
   for (auto val : results)
{
    cout << val << endl;
}

for (auto val : BTree_results)
{
    cout << val << endl;
}
*/
