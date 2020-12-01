#include <iostream> // cout
#include <string>
#include <vector>
#include <sstream> // istringstream
#include <fstream> // ifstream
using namespace std;

/**
 * Returns csv file into table, exported as a vector of vectors of
 * doubles.
 * @param inputFileName input file name (fullpath)
 * @return data as a vector of vector of doubles.
 */
vector<vector<string>> parse2DCsvFile(string inputFileName) {
    vector<vector<string>> data;
    ifstream inputFile(inputFileName);
    int l = 0;

    while (inputFile) {
        l++;
        string s;
        if (!getline(inputFile, s)) break;
        if (s[0] != '#') {
            istringstream ss(s);
            vector<string> record;

            while(ss) {
                string line;
                if (!getline(ss, line, ','))
                    break;
                try {
                    record.push_back(line);//stof(line));
                } catch (const std::invalid_argument e) {
                    cout << "NaN found in file " << inputFileName << " line " << l << '\n';
                    e.what();
                }
            }
            data.push_back(record);
        }
    }


    if (!inputFile.eof()) {
        cerr << "Could not read file " << inputFileName << '\n';
        __throw_invalid_argument("File not found");
    }

    return data;
}

//* fetch the close price and datestamp from the given BTC/USD csv
//* file, and print the tail values.
int main() {
    string filename = "../data/Kraken_BTCUSD_1h.csv";
    vector<vector<string>> data = parse2DCsvFile(filename);

    int N = data.size();
    cout << "loaded " << N << " rows, from " << filename << '\n';

    // save only the headers we want.
    string date[N-1] = {};
    double price[N-1] = {};
    int dateid[N-1] = {};

    int l = 0;
    for (vector<string> x: data) {
        if ( l>0 ) {
            date[l-1] = x[1];
            price[l-1] = stod(x[6]);
            dateid[l-1] = l-1;
        }
        l++;
    }

    cout << "final 5 rows in the table" << '\n';
    for (int i=N-6;i<N-1;i++)
        cout << "date: " << date[i] << ", dateid " << dateid[i] << ", price " << price[i] << '\n';



    return 0;
}
