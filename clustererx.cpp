#include "clustererx.h"

#include <map>

ClustererX::ClustererX(const string &dbPath)
    :db(dbPath)
{

}

void ClustererX::cluster(const string &querystring, Xapian::doccount offset, Xapian::doccount pagesize)
{
    const int MAX_DOCS = 100;
    const int NO_OF_CLUSTERS = 3;

    Xapian::QueryParser queryParser;
    queryParser.set_stemmer(Xapian::Stem("en"));
    queryParser.set_stemming_strategy(queryParser.STEM_SOME);
    queryParser.add_prefix("title", "S");
    queryParser.add_prefix("description", "XD");

    Xapian::Query query = queryParser.parse_query(querystring);

    Xapian::Enquire enquire(db);
    enquire.set_query(query);

    Xapian::MSet mset = enquire.get_mset(offset, pagesize);

    Xapian::ClusterSingleLink clusterer;
    Xapian::ClusterAssignments xapclusters;
    Xapian::DocSimCosine docsim;
    Xapian::MSetDocumentSource source(mset, MAX_DOCS);

    clusterer.cluster(xapclusters, docsim, source, NO_OF_CLUSTERS);

    int newID = 0;
    map<int, int> idMap;
    map<int, vector<int> > clusters;
    for(Xapian::MSetIterator it = mset.begin(); it != mset.end(); ++it) {
        Xapian::docid did = *it;
        int clusterID = xapclusters.cluster(did);
        if(idMap.count(clusterID) == 0) {
            idMap[clusterID] = newID++;
        }
        clusterID = idMap[clusterID];

        clusters[clusterID].push_back(did);
    }

    printClusters(clusters);
}

void ClustererX::printClusters(map<int, vector<int> > &clusters)
{
    cout << "============ Clusters ============" << endl;
    for(auto &kv : clusters) {
        cout << kv.first << " : [ ";
        string delim = "";
        for(auto &did : kv.second) {
            cout << delim << did;
            delim = ", ";
        }
        cout << " ]" << endl;
    }
}
