#pragma once
#include "./system.h"

/// 2022/07/13
/// yoshitome
/// Action.h

class Action {
    private:

    public:
        Action();
        virtual ~Action();

        virtual int8_t run(int32_t speed) = 0;

};