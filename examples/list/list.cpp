#include <cstdio>

#include <list.hpp>

using namespace osl;

int main(int, char**) {
    list<int> buffer;

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    for (auto it = buffer.start(); it != ++buffer.end(); ++it)
        printf("%i\n", *it);

    list<int> buffer1 = buffer;

    for (auto it = buffer1.start(); it != ++buffer1.end(); ++it)
        printf("%i\n", *it);

    return 0;
}
