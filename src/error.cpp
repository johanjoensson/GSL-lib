#include "GSLpp/error.h"

using namespace GSL;

Error_handler::Error_handler()
{}

void Error_handler::off()
{
    gsl_set_error_handler_off();
}
