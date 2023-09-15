#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits.h>

using namespace std;

class aRow {
public:
    vector<string> myRow;

    aRow();

    void display();

    string getColValue(int col);

    ~aRow();
};

class Table {
public:
    vector<string> colTypes;
    vector<string> colNames;
    vector<aRow> myTable;

    Table();

    ~Table();

    Table* selectColumns(int* colNums);

    Table* subsetTable(int bRow, int eRow, int bCol, int eCol);

    string columnAverage(int colNum);

    string columnMax(int colNum);

    string columnMin(int colNum);

    int missingValues(int colNum);

    void displayTableSummary();

    void display();
};

aRow::aRow() {
    // Initialize aRow constructor
}

void aRow::display() {
    for (const string& value : myRow) {
        cout << value << "\t";
    }
    cout << endl;
}

string aRow::getColValue(int col) {
    if (col < myRow.size()) {
        return myRow[col];
    }
    return "";
}

aRow::~aRow() {
    // Implement destructor for aRow if needed
}

Table::Table() {
    // Initialize Table constructor
}

Table::~Table() {
    // Implement destructor for Table if needed
}

Table* Table::selectColumns(int* colNums) {
    Table* newTable = new Table();
    for (int rowNum = 0; rowNum < myTable.size(); rowNum++) {
        aRow newRow;
        for (int i = 0; colNums[i] != -1; i++) {
            int col = colNums[i];
            if (col < myTable[rowNum].myRow.size()) {
                newRow.myRow.push_back(myTable[rowNum].myRow[col]);
            }
        }
        newTable->myTable.push_back(newRow);
    }
    return newTable;
}

Table* Table::subsetTable(int bRow, int eRow, int bCol, int eCol) {
    Table* newTable = new Table();
    for (int rowNum = bRow; rowNum <= eRow; rowNum++) {
        aRow newRow;
        for (int colNum = bCol; colNum <= eCol; colNum++) {
            if (rowNum < myTable.size() && colNum < myTable[rowNum].myRow.size()) {
                newRow.myRow.push_back(myTable[rowNum].myRow[colNum]);
            }
        }
        newTable->myTable.push_back(newRow);
    }
    return newTable;
}

string Table::columnAverage(int colNum) {
    double sum = 0;
    int count = 0;
    for (const aRow& row : myTable) {
        if (colNum < row.myRow.size()) {
            stringstream ss(row.myRow[colNum]);
            int value;
            if (ss >> value) {
                sum += value;
                count++;
            }
        }
    }
    if (count == 0) {
        return "N/A";
    }
    double average = sum / count;
    stringstream ss;
    ss << fixed << setprecision(2) << average;
    return ss.str();
}

string Table::columnMax(int colNum) {
    int maxVal = INT_MIN;
    for (const aRow& row : myTable) {
        if (colNum < row.myRow.size()) {
            stringstream ss(row.myRow[colNum]);
            int value;
            if (ss >> value) {
                maxVal = max(maxVal, value);
            }
        }
    }
    if (maxVal == INT_MIN) {
        return "N/A";
    }
    return to_string(maxVal);
}

string Table::columnMin(int colNum) {
    int minVal = INT_MAX;
    for (const aRow& row : myTable) {
        if (colNum < row.myRow.size()) {
            stringstream ss(row.myRow[colNum]);
            int value;
            if (ss >> value) {
                minVal = min(minVal, value);
            }
        }
    }
    if (minVal == INT_MAX) {
        return "N/A";
    }
    return to_string(minVal);
}

int Table::missingValues(int colNum) {
    int count = 0;
    for (const aRow& row : myTable) {
        if (colNum >= row.myRow.size() || row.myRow[colNum].empty()) {
            count++;
        }
    }
    return count;
}

void Table::displayTableSummary() {
    cout << "Number of rows: " << myTable.size() << endl;
    cout << "Number of columns: " << colTypes.size() << endl;
    cout << "Total number of missing values: " << missingValues(0) << endl;
    cout << "Table Headers: ";
    for (int i = 0; i < colNames.size(); i++) {
        cout << (colNames[i].empty() ? to_string(i + 1) : colNames[i]) << "\t";
    }
    cout << endl;

    for (auto it = myTable.begin(); it != myTable.end(); it++) {
        it->display();
    }
}

void Table::display() {
    for (const string& name : colNames) {
        cout << name << "\t";
    }
    cout << endl;
    for (auto it = myTable.begin(); it != myTable.end(); it++) {
        it->display();
    }
}

vector<string> split(const string& s)
{
    stringstream ss(s);
    vector<string> words;
    for (string w; ss >> w; ) words.push_back(w);
    return words;
}



int main() {
    Table* aTable;
    int headerOrNot;
    string csvFileName;
    ifstream csvFile;
    int numColumns;
    int numRows;
    fstream infile;
    infile.open("input1.txt", ios::in);
    string mychar[10];

    if (infile.is_open()) {
        int i = 0;
        string s;
        while (getline(infile, s)){
            mychar[i] = s;
            i++;

        }
        cout << "1" << endl;
    }
    
    infile.close();
        auto words = split(mychar[0]);
    string temp[2];
    int i = 0;
    for (auto& w : words) {
        temp[i++] = w;
    }
    headerOrNot = stoi(temp[0]);
    
    csvFileName = temp[1];
    numColumns = stoi(mychar[1]);

    // Create a Table instance
    aTable = new Table();
    i = 0;
    int j = 2;
    // Read the data types and store them in *aTable object
    for (i ,j; i < numColumns; i++,j++) {
        string colType;
        colType = mychar[j];
        aTable->colTypes.push_back(colType);
    }

    numRows == stoi(mychar[j]);
    cout << "2" << endl;
    // Open and read the CSV file
    csvFile.open(csvFileName);
    if (!csvFile.is_open()) {
        cerr << "Error: Unable to open CSV file." << endl;
        return 1;
    }

    // Read and store the CSV data in aTable
    string line;
    while (getline(csvFile, line)) {
        stringstream ss(line);
        aRow row;
        string cell;
        while (getline(ss, cell, ',')) {
            row.myRow.push_back(cell);
        }
        aTable->myTable.push_back(row);
    }
    cout << "3" << endl;
    cout << "Table Summary:" << endl;
    aTable->displayTableSummary();

    int cols[] = { 0, 1, 4, 7 };
    Table* bTable = aTable->selectColumns(cols);

    cout << "Selected Columns Summary:" << endl;
    bTable->displayTableSummary();

    Table* cTable = bTable->subsetTable(0, 99, 2, 3);

    cout << "Subset Table Summary:" << endl;
    cTable->displayTableSummary();

    cout << "Column 3 Average: " << aTable->columnAverage(3) << endl;
    cout << "Column 2 Max: " << bTable->columnMax(2) << endl;
    cout << "Column 1 Min: " << cTable->columnMin(1) << endl;
    cout << "Missing Values in Column 4: " << aTable->missingValues(4) << endl;

    // Clean up memory
    delete aTable;
    delete bTable;
    delete cTable;

    return 0;
}
