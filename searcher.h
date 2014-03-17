#ifndef SEARCHER_H
#define SEARCHER_H

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#include <xapian.h>

using namespace std;

class Searcher
{
public:
    Searcher(const string & dbPath);
    void search(const string & querystring, Xapian::doccount offset = 0, Xapian::doccount pagesize = 10);

private:
    string get_field(const string & data, size_t field);

    Xapian::Database db;
};

#endif // SEARCHER_H
