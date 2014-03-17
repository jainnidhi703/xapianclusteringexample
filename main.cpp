#include <iostream>
#include <string>

#include "indexer.h"
#include "searcher.h"
#include "clustererx.h"

using namespace std;

int main()
{
    const string dataPath = "/home/nidhijain/xapian/xapian-docsprint/data/100-objects-v1.csv";
    const string dbPath = "db/";

    Indexer indx(dataPath, dbPath);

    Searcher srch(dbPath);
    srch.search("watch");


    ClustererX ctx(dbPath);
    ctx.cluster("watch");

    return 0;
}

