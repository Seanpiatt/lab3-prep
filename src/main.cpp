#include "UniquePtr.h"
#include <cassert>
#include <iostream>

struct Base {
    virtual ~Base() = default;
    virtual int id() const { return 0; }
};

struct Derived : Base {
    int id() const override { return 1; }
};

struct Pair {
    int a;
    int b;
    Pair(int x, int y) : a(x), b(y) {}
};

int main() {
    UniquePtr<int> empty;

    UniquePtr<int> p(new int(42));

    UniquePtr<int> moved(std::move(p));

    UniquePtr<int> assigned(new int(7));
    assigned = std::move(moved);

    UniquePtr<Derived> d(new Derived());
    UniquePtr<Base> b(std::move(d));

    UniquePtr<int> x(new int(1));
    UniquePtr<int> y(new int(1));

    UniquePtr<int> toRelease(new int(99));
    int* raw = toRelease.release();
    delete raw;

    UniquePtr<int> toReset(new int(5));
    toReset.reset(new int(6));
    toReset.reset();

    UniquePtr<int> s1(new int(10));
    UniquePtr<int> s2(new int(20));
    s1.swap(s2);

    UniquePtr<Pair> pr(new Pair(3, 4));

    auto viaMakeUnique = makeUnique<Pair>(7, 8);

    std::cout << "all UniquePtr checks passed\n";
    return 0;
}
