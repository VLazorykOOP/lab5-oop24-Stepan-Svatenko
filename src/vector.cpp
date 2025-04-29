#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;


class Vector {
protected:
    std::vector<int> data;

public:
    Vector() = default;

    Vector(int size) : data(size) {}

    Vector(const Vector& other) : data(other.data) {}

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    virtual ~Vector() = default;

    virtual int& operator[](int index) {
        return data[index];
    }

    virtual const int& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return data.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (int i = 0; i < v.size(); ++i) {
            os << v[i] << " ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& v) {
        for (int i = 0; i < v.size(); ++i) {
            is >> v[i];
        }
        return is;
    }
};

class SafeVector : public Vector {
private:
    int low;
    int high;

public:
    SafeVector(int l, int h) : Vector(h - l + 1), low(l), high(h) {
        if (h < l) {
            throw std::invalid_argument("Upper bound must be >= lower bound");
        }
    }

    SafeVector(const SafeVector& other)
        : Vector(other), low(other.low), high(other.high) {}

    SafeVector& operator=(const SafeVector& other) {
        if (this != &other) {
            Vector::operator=(other);
            low = other.low;
            high = other.high;
        }
        return *this;
    }

    int& operator[](int index) override {
        if (index < low || index > high) {
            throw std::out_of_range("Index out of range");
        }
        return data[index - low];
    }

    const int& operator[](int index) const override {
        if (index < low || index > high) {
            throw std::out_of_range("Index out of range");
        }
        return data[index - low];
    }

    friend std::ostream& operator<<(std::ostream& os, const SafeVector& sv) {
        for (int i = sv.low; i <= sv.high; ++i) {
            os << sv[i] << " ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, SafeVector& sv) {
        for (int i = sv.low; i <= sv.high; ++i) {
            is >> sv[i];
        }
        return is;
    }
};

void unit_vector3(){
  cout << "=== Test Vector ===" << endl;
    Vector v1(5);
    cout << "Enter 5 elements for Vector v1:\n";
    cin >> v1;

    cout << "v1: " << v1 << endl;

    Vector v2 = v1; // копіювання
    cout << "v2 (copied from v1): " << v2 << endl;

    Vector v3;
    v3 = v1; // присвоєння
    cout << "v3 (assigned from v1): " << v3 << endl;

    cout << "v1[2] = " << v1[2] << endl;
    v1[2] = 100;
    cout << "After v1[2] = 100: " << v1 << endl;

    cout << "Size of v1: " << v1.size() << endl;

    cout << "\n=== Test SafeVector ===" << endl;
    try {
        SafeVector sv1(3, 7);
        cout << "Enter 5 elements for SafeVector sv1 (indices 3 to 7):\n";
        cin >> sv1;

        cout << "sv1: " << sv1 << endl;

        SafeVector sv2 = sv1; // копіювання
        cout << "sv2 (copied from sv1): " << sv2 << endl;

        SafeVector sv3(0, 0);
        sv3 = sv1; // присвоєння
        cout << "sv3 (assigned from sv1): " << sv3 << endl;

        cout << "sv1[5] = " << sv1[5] << endl;
        sv1[5] = 555;
        cout << "After sv1[5] = 555: " << sv1 << endl;

        cout << "Trying to access sv1[10] (out of bounds):" << endl;
        cout << sv1[10] << endl; // має кинути виняток

    } catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}
