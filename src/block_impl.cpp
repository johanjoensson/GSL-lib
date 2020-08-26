#include "GSLpp/block.h"

template<>
Block_t<double, gsl_block, std::allocator<double>>::Block_t(size_t n)
 : block(std::make_shared<gsl_block>(gsl_block_alloc(n)), gsl_block_free)
{}
