
#pragma once

#include "CommandProcessor.h"

enum class COMMAND_TYPE { ADD_PRIMITIVE };

class Command {
    private:
        COMMAND_TYPE type;
    public:
        Command(COMMAND_TYPE type): type(type) {}

        COMMAND_TYPE get_type() const;
        virtual void process_geometry(CommandProcessor&) = 0;
};

class AddPrimitiveCommand : public Command {
    public:
        AddPrimitiveCommand() : Command(COMMAND_TYPE::ADD_PRIMITIVE) {}
};