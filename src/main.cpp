#include <iostream>
#include "vector.h"
#include "complex_vector.h"
#include "complex.h"
#include "special_functions.h"

#include <gsl/gsl_sf_result.h>

using namespace GSL;

int main()
{
	std::cout << Complex(0,2) << std::endl;
	gsl_sf_result res{1., 0.2};
	std::cout << res.val << " +- " << res.err << std::endl;
	return 0;
}
