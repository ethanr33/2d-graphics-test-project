
#include "Engine.h"

int main() {

    int width = 1000;
    int height = 500;

    Engine e{width, height};

    while (e.is_active()) {
        e.tick();
    }

    return 0;

}