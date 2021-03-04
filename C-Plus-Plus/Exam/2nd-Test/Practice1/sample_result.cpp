#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Record {
private:
    string name;
    int hour, minute, second;
    double latitude, longitude;
public:
    Record(string name = "noName", int hour = 0, int minute = 0, int second = 0, double latitude = 0.0,
           double longitude = 0.0): name(name), hour(hour), minute(minute), second(second), latitude(latitude),
                                    longitude(longitude) { }

    Record(const Record& other): name(other.name), hour(other.hour), minute(other.minute), second(other.second),
                                 latitude(other.latitude), longitude(other.longitude) { }

    string getName() const { return name; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }

    friend Record& operator++(Record& self);
    friend Record operator+(const Record& self, double other);
    friend ostream& operator<<(ostream& out, const Record& self);
};


int inputData(const string& path, vector<Record>& vec_record);
void outPut(const vector<Record>& vec_record, unsigned n);
void processTime(vector<Record>& vec_record);
void processLocation(vector<Record>& vec_record);

auto func() -> int {
    return 0;
}

int main() {
    Record record1("Randy", 11, 12, 13, 34.15, 117.21);
    Record record2(record1);
    cout << record2 << endl;

    vector<Record> vec_record;
    string path = "D:\\location.txt";
    inputData(path, vec_record);

    processTime(vec_record);
    cout << "After time processing: " << endl;
    outPut(vec_record, 10);

    processLocation(vec_record);
    cout << "After location processing: " << endl;
    outPut(vec_record, 10);
    return 0;
}


Record& operator++(Record& self) {
    self.second++;
    if (self.second >= 60) {
        self.second %= 60;
        self.minute++;
    }
    if (self.minute >= 60) {
        self.minute %= 60;
        self.hour++;
    }
    if (self.hour >= 24) {
        self.hour %= 24;
    }
    return self;
}

Record operator+(const Record& self, double other) {
    return Record(self.name, self.hour, self.minute,
                  self.second, self.latitude + other, self.longitude + other);
}

ostream& operator<<(ostream& out, const Record& self) {
    out << setiosflags(ios::left) << setw(10) << self.name << setiosflags(ios::right);
    out << setw(2) << self.hour << ':' << setw(2) << self.minute << ':' << setw(2) << self.second;
    out << setiosflags(ios::right | ios::fixed) << setprecision(10);
    out << setw(20) << self.latitude << setw(20) << setw(20) << self.longitude;
    out << resetiosflags(ios::right | ios::fixed);
    return out;
}

int inputData(const string& path, vector<Record>& vec_record) {
    ifstream fin(path, ios::in);
    if (!fin.is_open()) {
        return -1;
    }
    while (!fin.eof()) {
        string name, s_hour, s_minute, s_second;
        double latitude, longitude;
        fin >> name;
        if (name.empty()) {
            break;
        }
        getline(fin, s_hour, ':');
        getline(fin, s_minute, ':');
        fin >> s_second >> latitude >> longitude;
        vec_record.push_back(Record(name, stoi(s_hour), stoi(s_minute), stoi(s_second), latitude, longitude));
    }
    return 0;
}

void outPut(const vector<Record>& vec_record, unsigned n) {
    unsigned end = min(vec_record.size(), n);
    for (unsigned i = 0; i < end; i++) {
        cout << vec_record[i] << endl;
    }
}


template <class Func>
int Filter(vector<Record>& vec_record, Func Pred) {
    int number = 0; // 删除数据的个数
    auto iter = vec_record.begin();
    while (iter != vec_record.end()) {
        // 使用迭代器删除不合法的数据
        if (!Pred(*iter)) {
            // 删除不合法的数据，迭代器指向下一个要判断的元素
            iter = vec_record.erase(iter);
            number++;
        } else { // 不符合条件递增迭代器
            ++iter;
        }
    }
    return number;
}

bool isVaildTime(const Record& self) {
    if (self.getHour() >= 6 && self.getHour() < 22) {
        return true;
    }
    if (self.getHour() == 22 && self.getMinute() == 0 && self.getSecond() == 0) {
        return true;
    }
    return false;
}

bool isValidPosition(Record& self) {
    self = self + 0.1;
    if ((self.getLatitude() >= 34.0 && self.getLatitude() <= 41.0) &&
        (self.getLongitude() >= 96.0 && self.getLongitude() <= 122.0)) {
        return true;
    }
    return false;
}


void processTime(vector<Record>& vec_record) {
    Filter(vec_record, isVaildTime);
}

void processLocation(vector<Record>& vec_record) {
    Filter(vec_record, isValidPosition);
}
