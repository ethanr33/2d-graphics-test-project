#pragma once

#include <vector>

#include "command_processing/Command.h"

class CommandStream {
    private:
        std::vector<Command> stream;

        void clear();
    public:
        void add_primitive(const Primitive& p) {
            stream.push_back(AddPrimitiveCommand(PRIMITIVE_TYPE::POINT, p.get_vertices()));
        }

        void add_clear_command(Color color) {
            stream.push_back(ClearCommand(color));
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