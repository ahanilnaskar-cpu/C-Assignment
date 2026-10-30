#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <algorithm>

using namespace std;

// ==========================================
// AGROVISION X
// SMART FARM MANAGEMENT SYSTEM
// ==========================================

// ---------- ABSTRACT CLASS ----------
class Advisory {
public:
    virtual void giveAdvice() const = 0;

    virtual ~Advisory() {
    }
};

// ---------- BASE CLASS ----------
class Crop : public Advisory {

protected:

    string name;
    double area;
    string season;
    double yieldPerAcre;

    static int cropCount;

public:

    // Default Constructor
    Crop() :
        name("Unknown"),
        area(0),
        season("Unknown"),
        yieldPerAcre(0) {

        cropCount++;
    }

    // Parameterized Constructor
    Crop(string n, double a, string s, double y) {

        if (n.empty() || a <= 0 || y < 0)
            throw invalid_argument("Invalid crop details!");

        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;

        cropCount++;
    }

    // Virtual Destructor
    virtual ~Crop() {
        cropCount--;
    }

    // Static Member
    static int getCropCount() {
        return cropCount;
    }

    // Runtime Polymorphism
    virtual double calculateTotalYield() const {

        return area * yieldPerAcre;
    }

    // Display Crop Information
    virtual void display() const {

        cout << left
             << setw(16) << name
             << setw(12) << area
             << setw(14) << season
             << setw(15) << yieldPerAcre
             << setw(15) << calculateTotalYield()
             << endl;
    }

    // Operator Overloading
    bool operator>(const Crop& other) const {

        return calculateTotalYield() >
               other.calculateTotalYield();
    }

    // File Handling
    virtual void saveData(ofstream& file) const = 0;

    virtual string getType() const = 0;

    string getName() const {
        return name;
    }

    double getArea() const {
        return area;
    }

    double getYield() const {
        return calculateTotalYield();
    }
};

int Crop::cropCount = 0;


// ==========================================
// DERIVED CLASS 1: CEREAL CROP
// ==========================================

class CerealCrop : public Crop {

private:

    string fertilizerType;
    int irrigationFrequency;

public:

    CerealCrop() :
        Crop(),
        fertilizerType("None"),
        irrigationFrequency(0) {
    }

    CerealCrop(string n, double a, string s,
               double y, string f, int i)
        : Crop(n, a, s, y) {

        if (i <= 0)
            throw invalid_argument(
                "Irrigation frequency must be positive!"
            );

        fertilizerType = f;
        irrigationFrequency = i;
    }

    double calculateTotalYield() const override {

        return area * yieldPerAcre;
    }

    string getType() const override {
        return "CEREAL";
    }

    void display() const override {

        cout << left
             << setw(16) << name
             << setw(12) << area
             << setw(14) << season
             << setw(15) << yieldPerAcre
             << setw(15) << calculateTotalYield()
             << endl;

        cout << "   Fertilizer: " << fertilizerType
             << " | Irrigation: Every "
             << irrigationFrequency << " days\n";
    }

    // AI-Style Advisory
    void giveAdvice() const override {

        cout << "\n  [SMART CEREAL ADVISOR]\n";

        cout << "  > Monitor nitrogen levels during "
             << "grain development.\n";

        cout << "  > Irrigate every "
             << irrigationFrequency
             << " days according to soil moisture.\n";

        cout << "  > Monitor pests and fungal infections.\n";
    }

    void saveData(ofstream& file) const override {

        file << "CEREAL "
             << quoted(name) << " "
             << area << " "
             << quoted(season) << " "
             << yieldPerAcre << " "
             << quoted(fertilizerType) << " "
             << irrigationFrequency << "\n";
    }
};


// ==========================================
// DERIVED CLASS 2: VEGETABLE CROP
// ==========================================

class VegetableCrop : public Crop {

private:

    string pestControlMethod;
    bool greenhouseGrown;

public:

    VegetableCrop() :
        Crop(),
        pestControlMethod("None"),
        greenhouseGrown(false) {
    }

    VegetableCrop(string n, double a, string s,
                  double y, string p, bool g)
        : Crop(n, a, s, y) {

        pestControlMethod = p;
        greenhouseGrown = g;
    }

    double calculateTotalYield() const override {

        // Greenhouse optimization
        double factor = greenhouseGrown ? 1.15 : 1.0;

        return area * yieldPerAcre * factor;
    }

    string getType() const override {
        return "VEGETABLE";
    }

    void display() const override {

        cout << left
             << setw(16) << name
             << setw(12) << area
             << setw(14) << season
             << setw(15) << yieldPerAcre
             << setw(15) << calculateTotalYield()
             << endl;

        cout << "   Pest Control: " << pestControlMethod
             << " | Greenhouse: "
             << (greenhouseGrown ? "YES" : "NO")
             << endl;
    }

    // AI-Style Advisory
    void giveAdvice() const override {

        cout << "\n  [SMART VEGETABLE ADVISOR]\n";

        cout << "  > Maintain consistent soil moisture.\n";

        cout << "  > Monitor fungal diseases and pests.\n";

        cout << "  > Use drip irrigation to reduce "
             << "water wastage.\n";

        if (!greenhouseGrown) {

            cout << "  > Greenhouse cultivation may improve "
                 << "estimated yield by 15%.\n";
        }
        else {

            cout << "  > Greenhouse optimization is active.\n";
        }
    }

    void saveData(ofstream& file) const override {

        file << "VEGETABLE "
             << quoted(name) << " "
             << area << " "
             << quoted(season) << " "
             << yieldPerAcre << " "
             << quoted(pestControlMethod) << " "
             << greenhouseGrown << "\n";
    }
};


// ==========================================
// SMART FARM MANAGEMENT SYSTEM
// ==========================================

class SmartFarm {

private:

    vector<unique_ptr<Crop>> crops;

public:

    // ---------- DASHBOARD ----------

    void dashboard() const {

        cout << "\n";
        cout << "====================================================\n";
        cout << "              AGROVISION X v2.0                    \n";
        cout << "         SMART AGRICULTURE CONTROL SYSTEM           \n";
        cout << "====================================================\n";

        cout << "\n                 SYSTEM DASHBOARD\n";

        cout << "----------------------------------------------------\n";

        cout << " SYSTEM STATUS       : ONLINE\n";

        cout << " FARM MONITORING     : ACTIVE\n";

        cout << " SMART ADVISORY      : ENABLED\n";

        cout << "----------------------------------------------------\n";

        cout << " REGISTERED CROPS    : "
             << Crop::getCropCount() << endl;

        cout << " TOTAL FARM AREA     : "
             << fixed << setprecision(2)
             << totalArea() << " acres\n";

        cout << " ESTIMATED HARVEST   : "
             << totalYield() << " tons\n";

        cout << "----------------------------------------------------\n";

        cout << "              SYSTEM COMMAND CENTER\n";

        cout << "----------------------------------------------------\n";

        cout << " 1.  Register New Cereal Crop\n";

        cout << " 2.  Register New Vegetable Crop\n";

        cout << " 3.  View Farm Inventory\n";

        cout << " 4.  Smart Farming Advisory\n";

        cout << " 5.  Compare Crop Performance\n";

        cout << " 6.  Farm Analytics & Productivity\n";

        cout << " 7.  Save Farm Database\n";

        cout << " 8.  Load Farm Database\n";

        cout << " 9.  View System Statistics\n";

        cout << " 10. Exit System\n";

        cout << "====================================================\n";
    }


    // ---------- TOTAL FARM AREA ----------

    double totalArea() const {

        double total = 0;

        for (const auto& c : crops) {

            total += c->getArea();
        }

        return total;
    }


    // ---------- TOTAL FARM YIELD ----------

    double totalYield() const {

        double total = 0;

        for (const auto& c : crops) {

            total += c->calculateTotalYield();
        }

        return total;
    }


    // ---------- ADD CEREAL CROP ----------

    void addCereal() {

        string n, s, f;

        double a, y;

        int irrigation;

        cout << "\n[ CEREAL CROP REGISTRATION ]\n";

        cout << "Crop Name: ";
        getline(cin, n);

        cout << "Cultivation Area (acres): ";
        if (!(cin >> a))
            throw invalid_argument("Invalid area input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Cultivation Season: ";
        getline(cin, s);

        cout << "Expected Yield Per Acre (tons): ";
        if (!(cin >> y))
            throw invalid_argument("Invalid yield input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Fertilizer Type: ";
        getline(cin, f);

        cout << "Irrigation Frequency (days): ";
        if (!(cin >> irrigation))
            throw invalid_argument("Invalid irrigation input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        crops.push_back(
            make_unique<CerealCrop>(
                n, a, s, y, f, irrigation
            )
        );

        cout << "\n[SUCCESS] Cereal crop registered!\n";

        cout << "[SYSTEM] Crop added to farm inventory.\n";
    }


    // ---------- ADD VEGETABLE CROP ----------

    void addVegetable() {

        string n, s, p;

        double a, y;

        char greenhouse;

        cout << "\n[ VEGETABLE CROP REGISTRATION ]\n";

        cout << "Crop Name: ";
        getline(cin, n);

        cout << "Cultivation Area (acres): ";

        if (!(cin >> a))
            throw invalid_argument("Invalid area input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Cultivation Season: ";
        getline(cin, s);

        cout << "Expected Yield Per Acre (tons): ";

        if (!(cin >> y))
            throw invalid_argument("Invalid yield input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Pest Control Method: ";
        getline(cin, p);

        cout << "Greenhouse Cultivation? (Y/N): ";

        if (!(cin >> greenhouse))
            throw invalid_argument("Invalid greenhouse input!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        greenhouse = toupper(greenhouse);

        if (greenhouse != 'Y' && greenhouse != 'N')
            throw invalid_argument("Enter Y or N!");

        crops.push_back(
            make_unique<VegetableCrop>(
                n, a, s, y, p, greenhouse == 'Y'
            )
        );

        cout << "\n[SUCCESS] Vegetable crop registered!\n";

        cout << "[SYSTEM] Crop added to farm inventory.\n";
    }


    // ---------- VIEW FARM INVENTORY ----------

    void displayCrops() const {

        if (crops.empty()) {

            cout << "\nNo crop records available.\n";

            return;
        }

        cout << "\n";
        cout << "====================================================\n";

        cout << "                FARM INVENTORY                     \n";

        cout << "====================================================\n";

        cout << left
             << setw(16) << "CROP"
             << setw(12) << "AREA"
             << setw(14) << "SEASON"
             << setw(15) << "YIELD/AC"
             << setw(15) << "TOTAL YIELD"
             << endl;

        cout << "----------------------------------------------------\n";

        for (size_t i = 0; i < crops.size(); i++) {

            cout << i + 1 << ". ";

            crops[i]->display();

            cout << "----------------------------------------------------\n";
        }
    }


    // ---------- SMART ADVISORY ----------

    void advisory() const {

        if (crops.empty()) {

            cout << "\nNo crops available for analysis.\n";

            return;
        }

        cout << "\n";
        cout << "====================================================\n";

        cout << "             AGROVISION SMART ADVISOR              \n";

        cout << "====================================================\n";

        for (const auto& c : crops) {

            cout << "\nCROP: " << c->getName();

            c->giveAdvice();

            cout << "\n----------------------------------------------------\n";
        }
    }


    // ---------- CROP COMPARISON ----------

    void compareCrops() const {

        if (crops.size() < 2) {

            cout << "\nRegister at least two crops first.\n";

            return;
        }

        int i, j;

        cout << "\nEnter first crop number: ";

        if (!(cin >> i))
            throw invalid_argument("Invalid crop index!");

        cout << "Enter second crop number: ";

        if (!(cin >> j))
            throw invalid_argument("Invalid crop index!");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (i < 1 || j < 1 ||
            i > static_cast<int>(crops.size()) ||
            j > static_cast<int>(crops.size()) ||
            i == j) {

            cout << "\nInvalid crop selection!\n";

            return;
        }

        Crop& c1 = *crops[i - 1];

        Crop& c2 = *crops[j - 1];

        cout << "\n========== PERFORMANCE ANALYSIS ==========\n";

        cout << c1.getName() << " : "
             << c1.getYield() << " tons\n";

        cout << c2.getName() << " : "
             << c2.getYield() << " tons\n";

        if (c1 > c2) {

            cout << "\nRESULT: " << c1.getName()
                 << " has higher estimated production.\n";
        }

        else {

            cout << "\nRESULT: " << c2.getName()
                 << " has higher estimated production.\n";
        }
    }


    // ---------- FARM ANALYTICS ----------

    void analytics() const {

        if (crops.empty()) {

            cout << "\nNo data available for analytics.\n";

            return;
        }

        double highest = 0;

        double lowest = crops[0]->getYield();

        string bestCrop = crops[0]->getName();

        for (const auto& c : crops) {

            double y = c->getYield();

            if (y > highest) {

                highest = y;

                bestCrop = c->getName();
            }

            if (y < lowest) {

                lowest = y;
            }
        }

        double productivity =
            totalArea() > 0
            ? totalYield() / totalArea()
            : 0;

        cout << "\n";
        cout << "====================================================\n";

        cout << "              FARM ANALYTICS CENTER                \n";

        cout << "====================================================\n";

        cout << fixed << setprecision(2);

        cout << "\nTotal Registered Crops : "
             << crops.size();

        cout << "\nTotal Cultivation Area : "
             << totalArea() << " acres";

        cout << "\nTotal Expected Harvest : "
             << totalYield() << " tons";

        cout << "\nAverage Productivity   : "
             << productivity << " tons/acre";

        cout << "\nHighest Producing Crop : "
             << bestCrop;

        cout << "\nHighest Crop Yield     : "
             << highest << " tons";

        cout << "\nLowest Crop Yield      : "
             << lowest << " tons";

        cout << "\n\nPRODUCTIVITY INDICATOR\n";

        int score = min(
            100,
            static_cast<int>(productivity * 10)
        );

        cout << "[";

        for (int i = 0; i < 20; i++) {

            if (i < score / 5)
                cout << "#";

            else
                cout << "-";
        }

        cout << "] " << score << "/100";

        cout << "\n\nNote: This is an illustrative "
             << "productivity indicator, not a scientific "
             << "farm-efficiency rating.\n";

        cout << "====================================================\n";
    }


    // ---------- SAVE DATABASE ----------

    void saveDatabase() const {

        ofstream file("AgroVision_Database.txt");

        if (!file) {

            throw runtime_error(
                "Unable to create database file!"
            );
        }

        for (const auto& c : crops) {

            c->saveData(file);
        }

        file.close();

        cout << "\n[SYSTEM] Farm database saved successfully!\n";

        cout << "File: AgroVision_Database.txt\n";
    }


    // ---------- LOAD DATABASE ----------

    void loadDatabase() {

        ifstream file("AgroVision_Database.txt");

        if (!file) {

            cout << "\nNo previous database found.\n";

            return;
        }

        string type, n, s, extra;

        double a, y;

        vector<unique_ptr<Crop>> loadedCrops;

        try {

            while (file >> type) {

                file >> quoted(n)
                     >> a
                     >> quoted(s)
                     >> y
                     >> quoted(extra);

                if (!file)
                    throw runtime_error("Corrupted database!");

                if (type == "CEREAL") {

                    int irrigation;

                    file >> irrigation;

                    loadedCrops.push_back(
                        make_unique<CerealCrop>(
                            n, a, s, y, extra, irrigation
                        )
                    );
                }

                else if (type == "VEGETABLE") {

                    bool greenhouse;

                    file >> greenhouse;

                    loadedCrops.push_back(
                        make_unique<VegetableCrop>(
                            n, a, s, y, extra, greenhouse
                        )
                    );
                }

                else {

                    throw runtime_error(
                        "Unknown crop type in database!"
                    );
                }
            }

            if (!file.eof() && file.fail())
                throw runtime_error("Database reading failed!");

        }

        catch (...) {

            throw;
        }

        crops = move(loadedCrops);

        cout << "\n[SUCCESS] Database loaded successfully!\n";

        cout << "Restored crop records: "
             << crops.size() << endl;
    }


    // ---------- SYSTEM STATISTICS ----------

    void statistics() const {

        int cereals = 0;

        int vegetables = 0;

        for (const auto& c : crops) {

            if (c->getType() == "CEREAL")
                cereals++;

            else
                vegetables++;
        }

        cout << "\n";
        cout << "============================================\n";

        cout << "             SYSTEM STATISTICS              \n";

        cout << "============================================\n";

        cout << "\nTotal Crop Objects : "
             << Crop::getCropCount();

        cout << "\nCereal Crops       : " << cereals;

        cout << "\nVegetable Crops    : " << vegetables;

        cout << "\nDatabase Status    : ACTIVE";

        cout << "\nMonitoring Status  : ONLINE";

        cout << "\n============================================\n";
    }
};


// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {

    SmartFarm farm;

    int choice;

    cout << "\n\n";

    cout << "      INITIALIZING AGROVISION X SYSTEM...\n";

    cout << "      Loading Agricultural Modules...\n";

    cout << "      Connecting Farm Database...\n";

    cout << "      System Successfully Initialized!\n";

    do {

        farm.dashboard();

        cout << "\nEnter Command: ";

        if (!(cin >> choice)) {

            cout << "\n[ERROR] Invalid command!\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        try {

            switch (choice) {

                case 1:

                    farm.addCereal();

                    break;

                case 2:

                    farm.addVegetable();

                    break;

                case 3:

                    farm.displayCrops();

                    break;

                case 4:

                    farm.advisory();

                    break;

                case 5:

                    farm.compareCrops();

                    break;

                case 6:

                    farm.analytics();

                    break;

                case 7:

                    farm.saveDatabase();

                    break;

                case 8:

                    farm.loadDatabase();

                    break;

                case 9:

                    farm.statistics();

                    break;

                case 10:

                    cout << "\n============================================\n";

                    cout << "       AGROVISION X SHUTTING DOWN           \n";

                    cout << "       Thank You For Using Our System!      \n";

                    cout << "============================================\n";

                    break;

                default:

                    cout << "\nInvalid selection! Try again.\n";
            }

        }

        catch (const exception& e) {

            cout << "\n[SYSTEM ERROR] "
                 << e.what() << endl;
        }

    } while (choice != 10);

    return 0;
}