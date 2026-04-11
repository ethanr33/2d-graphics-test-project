
#pragma once

#include "Command.h"

class AddPrimitiveCommand;

class CommandProcessor {
    public:
        virtual void process(AddPrimitiveCommand&) = 0;
};

class PrimitiveCreator : CommandProcessor {
    public:
        void process(AddPrimitiveCommand&) override;
};