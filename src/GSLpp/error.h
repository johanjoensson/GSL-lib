#ifndef ERROR_H
#define ERROR_H

#include <gsl/gsl_errno.h>
#include <memory>

namespace GSL{
    class Error_handler{
    public:
        Error_handler();

        void off();
    };
}

#endif // ERROR_H
