#ifndef NEW_BLOCK_GLSPP_LIB_H
#define NEW_BLOCK_GLSPP_LIB_H

#include <gsl/gsl_block.h>
#include <memory>

namespace GSL{

class Block {
private:
    std::unique_ptr<gsl_block, decltype(&gsl_block_free)> gsl_block_m;
public:
    Block() = default;
    Block(const Block&) = default;
    Block(Block&&) = default;
    ~Block() = default;

    Block& operator=(const Block&) = default;
    Block& operator=(Block&&) = default;

    Block(size_t);

    double* data();
    const double* data() const;
    size_t size() const;

    gsl_block* gsl_data();
    const gsl_block* gsl_data() const;
};

}

#endif // NEW_BLOCK_GLSPP_LIB_H
