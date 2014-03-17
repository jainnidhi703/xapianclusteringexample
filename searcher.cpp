#include "searcher.h"

Searcher::Searcher(const string &dbPath)
    :db(dbPath)
{

}

void Searcher::search(const string &querystring, Xapian::doccount offset, Xapian::doccount pagesize)
{
    // offset - defines starting point within result set.
    // pagesize - defines number of records to retrieve.

    // Open the database we're going to search.
    //    Xapian::Database db(dbpath);

    // Set up a QueryParser with a stemmer and suitable prefixes.
    Xapian::QueryParser queryParser;
    queryParser.set_stemmer(Xapian::Stem("en"));
    queryParser.set_stemming_strategy(queryParser.STEM_SOME);
    queryParser.add_prefix("title", "S");
    queryParser.add_prefix("description", "XD");

    // And parse the query.
    Xapian::Query query = queryParser.parse_query(querystring);

    // Use an Enquire object on the database to run the query.
    Xapian::Enquire enquire(db);
    enquire.set_query(query);

    // And print out something about each match.
    Xapian::MSet mset = enquire.get_mset(offset, pagesize);

    clog << "'" << querystring << "'[" << offset << ":" << offset + pagesize
         << "] =" << endl <<" ";
    for (Xapian::MSetIterator m = mset.begin(); m != mset.end(); ++m) {
        Xapian::docid did = *m;
        cout << m.get_rank() + 1 << ": #" << setfill('0') << setw(3) << did
             << ' ';

        const string & data = m.get_document().get_data();
        cout << get_field(data, 1) << endl;
        // Log the document id.
        clog << ' ' << did;
    }
    clog << endl;
}

string Searcher::get_field(const string &data, size_t field)
{
    size_t start = 0;
    while (true) {
        size_t end = data.find('\n', start);
        if (field == 0)
            return string(data, start, end - start);
        start = end;
        if (start != string::npos) ++start;
        --field;
    }
}
