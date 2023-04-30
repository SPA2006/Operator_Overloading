#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class CoffeeGrinder;
class Multicooker;
class Breakfast;

class CoffeeGrinder {
    friend Breakfast;

private:
    int temperature, power, volume;
    std::string color;
    char label;
    std::vector<std::string> types = { "Americano", "Cortado", "Mocha", "Macchiato",
        "Flat White", "Decaf", "Irish Coffee", "Iced Coffee", "Café au Lait", "Re-enter the name" };

public:
    CoffeeGrinder(int temp = 0, int poww = 0, int vol = 0, std::string col = "", char label = '+');
    CoffeeGrinder(const CoffeeGrinder& other);
    ~CoffeeGrinder();

    friend std::istream& operator >> (std::istream& in, CoffeeGrinder& cg);
    friend std::ostream& operator << (std::ostream& out, const CoffeeGrinder& cg);

    CoffeeGrinder operator + (const int t) const;
    CoffeeGrinder operator - (const int t) const;

    CoffeeGrinder operator + (const CoffeeGrinder& other) const;
    CoffeeGrinder operator - (const CoffeeGrinder& other) const;

    CoffeeGrinder& operator += (const int t);
    CoffeeGrinder& operator -= (const int t);

    CoffeeGrinder& operator += (const CoffeeGrinder& other);
    CoffeeGrinder& operator -= (const CoffeeGrinder& other);

    CoffeeGrinder& operator ++ ();
    CoffeeGrinder& operator ++ (int value);

    CoffeeGrinder& operator = (const CoffeeGrinder& other);
    std::string& operator [] (int index);

    bool CheckVoltage();
};

class Multicooker {
    friend Breakfast;

private:
    int temperature, power;
    std::string color;
public:
    Multicooker(int temp = 0, int poww = 0, std::string col = "");
    Multicooker(const Multicooker& other);
    ~Multicooker();

    friend std::istream& operator >> (std::istream& in, Multicooker& mc);
    friend std::ostream& operator << (std::ostream& out, const Multicooker& mc);

    Multicooker operator + (int t) const;
    Multicooker operator - (int t) const;

    Multicooker operator + (const Multicooker& other) const;
    Multicooker operator - (const Multicooker& other) const;

    Multicooker& operator += (const int t);
    Multicooker& operator -= (const int t);

    Multicooker& operator += (const Multicooker& mc);
    Multicooker& operator -= (const Multicooker& mc);
};

class Breakfast {
private:
    CoffeeGrinder MyGrinder;
    Multicooker MyCooker;

public:
    Breakfast(const CoffeeGrinder& MG, const Multicooker& MC);
    Breakfast() = default;
    Breakfast(const CoffeeGrinder& MG);
    Breakfast(const Multicooker& MC);

    Breakfast(const Breakfast& other);
    ~Breakfast();

    CoffeeGrinder get_grinder();
    Multicooker get_cooker();

    void Start();
};

CoffeeGrinder input_grinder();
Multicooker input_cooker();
Breakfast get_objects(std::string ans);



int main() {
    Breakfast MyBreakfast;
    std::string answer;

    std::cout << "What would you like for breakfast?\n";
    std::cout << "- Coffee\n";
    std::cout << "- Eat smt\n";
    std::cout << "- Both\n";
    std::cin >> answer;

    MyBreakfast = get_objects(answer);
    system("CLS");
    MyBreakfast.Start();
    std::cout << MyBreakfast.get_grinder();
    std::cout << "----------\n\n";
    std::cout << MyBreakfast.get_cooker();

    MyBreakfast.get_grinder()++;
    MyBreakfast.get_cooker() += 10;

    std::cout << MyBreakfast.get_grinder();
    std::cout << "----------\n\n";
    std::cout << MyBreakfast.get_cooker();

    return 0;
}



// Coffee Grinder methods ----------

CoffeeGrinder::CoffeeGrinder(int temp, int poww, int vol, std::string col, char label) :
    temperature(temp), power(poww), volume(vol), color(col), label(label) {}

CoffeeGrinder::CoffeeGrinder(const CoffeeGrinder& other) {
    this->temperature = other.temperature;
    this->power = other.power;
    this->volume = other.volume;
    this->color = other.color;
    this->label = other.label;
}

CoffeeGrinder::~CoffeeGrinder() {
    //std::cout << "Deeeeeelete.....\n";
}

std::istream& operator >> (std::istream& in, CoffeeGrinder& cg) {
    int t, p, v;
    std::string c;
    char l;
    in >> t >> p >> v;
    std::getline(in, c, '.');
    in >> l;

    cg = CoffeeGrinder(t, p, v, c, l);
    return in;
}

std::ostream& operator << (std::ostream& out, const CoffeeGrinder& cg) {
    out << "Status of Coffee Grinder:\n\n";
    out << "Temperature: " << cg.temperature << "C\n";
    out << "Power: " << cg.power << "V\n";
    out << "Volume: " << cg.volume << "ml\n";
    out << "Color: " << cg.color << "\n\n";
    return out;
}

CoffeeGrinder CoffeeGrinder::operator + (const int t) const {
    CoffeeGrinder result(*this);
    result.temperature += t;
    return result;
}
CoffeeGrinder CoffeeGrinder::operator - (const int t) const {
    CoffeeGrinder result(*this);
    result.temperature -= t;
    return result;
}

CoffeeGrinder CoffeeGrinder::operator + (const CoffeeGrinder& other) const {
    CoffeeGrinder cg;
    cg.temperature = this->temperature + other.temperature;
    cg.power = this->power + other.power;
    cg.volume = this->volume + other.volume;
    cg.color = this->color;
    cg.label = this->label;
    return cg;
}
CoffeeGrinder CoffeeGrinder::operator - (const CoffeeGrinder& other) const {
    CoffeeGrinder cg;
    cg.temperature = this->temperature - other.temperature;
    cg.power = this->power - other.power;
    cg.volume = this->volume - other.volume;
    cg.color = this->color;
    cg.label = this->label;
    return cg;
}

CoffeeGrinder& CoffeeGrinder::operator += (const int t) {
    this->temperature += t;
    return *this;
}
CoffeeGrinder& CoffeeGrinder::operator -= (const int t) {
    this->temperature -= t;
    return *this;
}

CoffeeGrinder& CoffeeGrinder::operator += (const CoffeeGrinder& other) {
    this->temperature += other.temperature;
    return *this;
}
CoffeeGrinder& CoffeeGrinder::operator -= (const CoffeeGrinder& other) {
    this->temperature -= other.temperature;
    return *this;
}

CoffeeGrinder& CoffeeGrinder::operator ++ () {
    this->power += 10;
    this->temperature++;

    return *this;
}

CoffeeGrinder& CoffeeGrinder::operator ++ (int value) {
    CoffeeGrinder cg(*this);
    this->power += 10;
    this->temperature++;
    return cg;
}

CoffeeGrinder& CoffeeGrinder::operator = (const CoffeeGrinder& other) {
    this->temperature = other.temperature;
    this->power = other.power;
    this->volume = other.volume;
    this->color = other.color;
    this->label = other.label;

    return *this;
}

std::string& CoffeeGrinder::operator [] (int index) {
    if (index < types.size() - 1 && index > -1)
        return types[index];
    else
        return types[types.size() - 1];
}

bool CoffeeGrinder::CheckVoltage() {
    return label == '+';
}

// Multicooker methods ----------

Multicooker::Multicooker(int temp, int poww, std::string col) :
    temperature(temp), power(poww), color(col) {}

Multicooker::Multicooker(const Multicooker& other) {
    this->temperature = other.temperature;
    this->power = other.power;
    this->color = other.color;
}

Multicooker::~Multicooker() {}

std::istream& operator >> (std::istream& in, Multicooker& mc) {
    int temp, poww;
    std::string col;
    in >> temp >> poww;
    std::getline(in, col);
    mc = Multicooker(temp, poww, col);
    return in;
}

std::ostream& operator << (std::ostream& out, const Multicooker& mc) {
    out << "Status of Multicooker:\n\n";
    out << "Temperature: " << mc.temperature << "C\n";
    out << "Power: " << mc.power << "V\n";
    out << "Color: " << mc.color << "\n\n";
    return out;
}

Multicooker Multicooker::operator + (int t) const {
    Multicooker result(*this);
    result.temperature += t;
    return *this;
}
Multicooker Multicooker::operator - (int t) const {
    Multicooker result(*this);
    result.temperature -= t;
    return *this;
}

Multicooker Multicooker::operator + (const Multicooker& other) const {
    Multicooker mc;
    mc.temperature = this->temperature + other.temperature;
    mc.power = this->power + other.power;
    mc.color = this->color;
    return mc;
}
Multicooker Multicooker::operator - (const Multicooker& other) const {
    Multicooker mc;
    mc.temperature = this->temperature - other.temperature;
    mc.power = this->power - other.power;
    mc.color = this->color;
    return mc;
}

Multicooker& Multicooker::operator += (const int t) {
    this->temperature += t;
    return *this;
}
Multicooker& Multicooker::operator -= (const int t) {
    this->temperature -= t;
    return *this;
}

Multicooker& Multicooker::operator += (const Multicooker& other) {
    this->temperature += other.temperature;
    return *this;
}
Multicooker& Multicooker::operator -= (const Multicooker& other) {
    this->temperature -= other.temperature;
    return *this;
}

// Breakfast methods ----------

Breakfast::Breakfast(const CoffeeGrinder& MG, const Multicooker& MC): MyGrinder(MG), MyCooker(MC) {}
Breakfast::Breakfast(const CoffeeGrinder& MG): MyGrinder(MG) {}
Breakfast::Breakfast(const Multicooker& MC): MyCooker(MC) {}

Breakfast::Breakfast(const Breakfast& other) {
    this->MyGrinder.temperature = other.MyGrinder.temperature;
    this->MyGrinder.power = other.MyGrinder.power;
    this->MyGrinder.volume = other.MyGrinder.volume;
    this->MyGrinder.color = other.MyGrinder.color;
    this->MyGrinder.label = other.MyGrinder.label;

    this->MyCooker.temperature = other.MyCooker.temperature;
    this->MyCooker.power = other.MyCooker.power;
    this->MyCooker.color = other.MyCooker.color;
}

Breakfast::~Breakfast() {}

CoffeeGrinder Breakfast::get_grinder() {
    return MyGrinder;
}
Multicooker Breakfast::get_cooker() {
    return MyCooker;
}

void Breakfast::Start() {
    if (this->MyGrinder.CheckVoltage())
        std::cout << "VjuHHH!!!\n\n";
    else
        std::cout << "Beep Beep\n\n";
}

// Methods ----------

CoffeeGrinder input_grinder() {
    CoffeeGrinder MyGrinder;
    std::cout << "\n\nInput coffee grinder's specs: Temperature, Power, Volume, Color (end with a dot), + or -   ->\n";
    for (short i = 0; i < 100; ++i)
        std::cout << "-";
    std::cout << "\n\n";
    std::cin >> MyGrinder;
    return MyGrinder;
}

Multicooker input_cooker() {
    Multicooker MyCooker;
    std::cout << "\n\nInput multicooker's specs: Temperature, Power, Color   ->\n";
    for (short i = 0; i < 100; ++i)
        std::cout << "-";
    std::cout << "\n\n";
    std::cin >> MyCooker;
    return MyCooker;
}

Breakfast get_objects(std::string ans) {
    if (ans == "Both") {
        return Breakfast(input_grinder(), input_cooker());
    }
    else if (ans == "Coffee") {
        return Breakfast(input_grinder());
    }
    else {
        return Breakfast(input_cooker());
    }
}