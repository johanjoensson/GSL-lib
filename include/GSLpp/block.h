#ifndef BLOCK_GSLPP_LIB_H
#define BLOCK_GSLPP_LIB_H
#include<gsl/gsl_block.h>
#include <memory>

namespace GSL{

template<class D, class GSL_BLOCK, class A = std::allocator<D>>
class Block_t
{
private:
    std::shared_ptr<GSL_BLOCK> block;
public:
    Block_t() = default;
    Block_t(const Block&) = default;
    Block_t(Block_t&&) = default;

    Block_t(size_t n);

    Block_t& operator=(const Block_t&) = default;
    Block_t& operator=(Block&_t&) = default;
};

}

#endif //BLOCK_GSLPP_LIB_H
