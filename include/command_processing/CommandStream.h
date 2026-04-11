
#include <queue>

#include "command_processing/Command.h"

class CommandStream {
    private:
        std::queue<Command> stream;
    public:

        void add_primitive(Vertex);
};