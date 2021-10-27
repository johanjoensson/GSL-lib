#include "GSLpp/block.h"

using namespace GSL;

Block::Block(size_t n)
 : gsl_block_m(gsl_block_alloc(n), gsl_block_free)
{}

size_t Block::size() const
{
    return gsl_block_m->size;
}

double* Block::data()
{
    return this->gsl_block_m->data;
}

const double* Block::data() const
{
    return this->gsl_block_m->data;
}

gsl_block* Block::gsl_data()
{
    return this->gsl_block_m.get();
}

const gsl_block* Block::gsl_data() const
{
    return this->gsl_block_m.get();
}
