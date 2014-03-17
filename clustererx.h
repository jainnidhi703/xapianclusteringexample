#ifndef CLUSTERERX_H
#define CLUSTERERX_H

#include <iostream>
#include <string>


#include <xapian.h>

using namespace std;

class ClustererX
{
public:
    ClustererX(const string & dbPath);
    void cluster(const string & querystring, Xapian::doccount offset = 0, Xapian::doccount pagesize = 10);
private:
    void printClusters(map<int, vector<int> > &clusters);
    Xapian::Database db;
};

#endif // CLUSTERERX_H
