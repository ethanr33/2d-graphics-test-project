#pragma once

#include <vector>

#include "command_processing/Command.h"

class CommandStream {
    private:
        std::vector<Command> stream;

        void clear();
    public:
        void add_primitive(const Primitive& p) {
            stream.push_back(AddPrimitiveCommand(p));
        }

        void reset() {
            stream.clear();
        }

        std::vector<Command>& get_command_stream() {
            return stream;
        }

        const std::vector<Command>& get_command_stream() const {
            return stream;
        }

};