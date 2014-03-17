#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>

using namespace std;

class Indexer
{
public:
    Indexer(const string & datapath, const string & dbpath);

private:
    bool csv_parse_line(ifstream & csv, vector<string> & fields);
};

#endif // INDEX_H
