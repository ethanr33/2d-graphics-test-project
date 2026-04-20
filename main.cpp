
#include "Engine.h"

int main() {

    int width = 600;
    int height = 600;

    Engine e{width, height};

    while (e.is_active()) {
        e.tick();
    }

    return 0;

}