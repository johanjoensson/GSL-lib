#ifndef NEW_MATRIX_VIEW_GLSPP_LIB_H
#define NEW_MATRIX_VIEW_GLSPP_LIB_H

#include "GSLpp/block.h"

namespace GSL{
class Matrix::View {
private:
    gsl_matrix_view gsl_mat_view_m;
public:
    View() = default;
    View(const View&) = default;
    View(View&&) = default;
    View& operator=(const View&) = default;
    View& operator=(View&&) = default;
    ~View() = default;

    View(const Matrix& m);
    View(const Matrix& m, size_t k1, size_t k2, size_t n1, size_t n2);

    View(GSL::Block& b, size_t n1, size_t n2);
    View(GSL::Block& b, size_t offset, size_t n1, size_t n2);
    View(GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda);

    View(double* data, size_t n1, size_t n2);
    View(double* data, size_t offset, size_t n1, size_t n2);
    View(double* data, size_t offset, size_t n1, size_t n2, size_t tda);

    View(Vector& v, size_t n1, size_t n2);
    View(Vector& v, size_t n1, size_t n2, size_t tda);

    View view();
    Const_View view() const;
    Const_View cview() const;
    View view(size_t k1, size_t k2, size_t n1, size_t n2);
    Const_View view(size_t k1, size_t k2, size_t n1, size_t n2) const;
    Const_View cview(size_t k1, size_t k2, size_t n1, size_t n2) const;

    operator Matrix();
    operator const Matrix() const;

    gsl_matrix* gsl_data();
    const gsl_matrix* gsl_data() const;

    Matrix clone() const;

    View& operator=(const Matrix& m);
    View& operator=(Matrix&& m);

    View& swap(View& mv);
    View& swap(View&& mv);
    View& swap(Matrix& mv);
    View& swap(Matrix&& mv);


    View& copy(const View& mv);
    View& copy(View&& mv);
    View& copy(const Matrix& mv);
    View& copy(Matrix&& mv);

    View& transpose_copy(const Matrix& other);
    View& swap_rows(size_t i, size_t j);
    View& swap_columns(size_t i, size_t j);
    View& swap_rowcol(size_t i, size_t j);

    View& transpose();
    View& T();

    size_t num_rows() const;
    size_t num_columns() const;
    std::pair<size_t, size_t> dim() const;
    size_t tda() const;

    View& set_all(double val);
    View& set_zero();
    View& set(size_t i, size_t j, double val);
    View& set_identity();
    double get(size_t i, size_t j) const;

    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    std::pair<size_t, size_t> max_index() const;
    std::pair<size_t, size_t> min_index() const;
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> minmax_index() const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    View& operator+=(const Matrix& other);
    View& operator-=(const Matrix& other);
    View& operator*=(const Matrix& other);
    View& operator/=(const Matrix& other);

    View& operator+=(double s);
    View& operator-=(double s);
    View& operator*=(double s);
    View& operator/=(double s);

    View& multiply(const Matrix& other);

    Vector::View row(size_t row);
    Vector::Const_View row(size_t row) const;
    Vector::Const_View crow(size_t row) const;

    Vector::View column(size_t column);
    Vector::Const_View column(size_t column) const;
    Vector::Const_View ccolumn(size_t column) const;

    Vector::View subrow(size_t i, size_t offset, size_t n);
    Vector::Const_View subrow(size_t i, size_t offset, size_t n) const;
    Vector::Const_View csubrow(size_t i, size_t offset, size_t n) const;
    Vector::View subcolumn(size_t i, size_t offset, size_t n);
    Vector::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
    Vector::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
    Vector::View diagonal();
    Vector::Const_View diagonal() const;
    Vector::Const_View cdiagonal() const;
    Vector::View subdiagonal(size_t k);
    Vector::Const_View subdiagonal(size_t k) const;
    Vector::Const_View csubdiagonal(size_t k) const;
    Vector::View superdiagonal(size_t k);
    Vector::Const_View superdiagonal(size_t k) const;
    Vector::Const_View csuperdiagonal(size_t k) const;

    Vector::View operator[](size_t row);
    Vector::Const_View operator[](size_t row) const;

    Vector::View at(size_t row);
    Vector::Const_View at(size_t row) const;

    double& operator()(size_t i, size_t j);
    const double& operator()(size_t i, size_t j) const;

    double& at(size_t i, size_t j);
    const double& at(size_t i, size_t j) const;

    class Iterator;
    class Row_Iterator;
    class Column_Iterator;
    class Diagonal_Iterator;

    class Const_Iterator;
    class Const_Row_Iterator;
    class Const_Column_Iterator;
    class Const_Diagonal_Iterator;


    using value_type = Vector::View;
    using const_value_type = Vector::Const_View;
    using difference_type = size_t;
    using reference = value_type;
    using const_reference = const_value_type;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = Row_Iterator;
    using const_iterator = Const_Row_Iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using column_iterator = Column_Iterator;
    using const_column_iterator = Const_Column_Iterator;
    using reverse_column_iterator = std::reverse_iterator<column_iterator>;
    using const_reverse_column_iterator = std::reverse_iterator<const_column_iterator>;

    using diagonal_iterator = Diagonal_Iterator;
    using const_diagonal_iterator = Const_Diagonal_Iterator;
    using reverse_diagonal_iterator = std::reverse_iterator<diagonal_iterator>;
    using const_reverse_diagonal_iterator = std::reverse_iterator<const_diagonal_iterator>;

    iterator begin() noexcept; // {return this->rows_begin();}
    const_iterator begin() const noexcept; // {return this->rows_begin();}
    const_iterator cbegin() const noexcept; // {return this->rows_cbegin();}

    iterator end() noexcept; // {return this->rows_end();}
    const_iterator end() const noexcept; // {return this->rows_end();}
    const_iterator cend() const noexcept; // {return this->rows_cend();}

    reverse_iterator rbegin() noexcept; // {return rows_rbegin();}
    const_reverse_iterator rbegin() const noexcept; // {return rows_rbegin();}
    const_reverse_iterator crbegin() const noexcept; //  {return rows_crbegin();}

    reverse_iterator rend() noexcept; // {return this->rows_rend();}
    const_reverse_iterator rend() const noexcept; // {return this->rows_rend();}
    const_reverse_iterator crend() const noexcept; // {return this->rows_crend();}

    value_type front() {return rows_front();}
    const_value_type front() const {return rows_front();}
    value_type back() {return rows_back();}
    const_value_type back() const {return rows_back();}

    Row_Iterator rows_begin() noexcept;
    Const_Row_Iterator rows_begin() const noexcept;
    Const_Row_Iterator rows_cbegin() const noexcept;

    Row_Iterator rows_end() noexcept;
    Const_Row_Iterator rows_end() const noexcept;
    Const_Row_Iterator rows_cend() const noexcept;

    reverse_iterator rows_rbegin() noexcept;
    const_reverse_iterator rows_rbegin() const noexcept;
    const_reverse_iterator rows_crbegin() const noexcept;

    reverse_iterator rows_rend() noexcept;
    const_reverse_iterator rows_rend() const noexcept;
    const_reverse_iterator rows_crend() const noexcept;

    value_type rows_front();
    const_value_type rows_front() const;
    value_type rows_back();
    const_value_type rows_back() const;

    Column_Iterator columns_begin() noexcept;
    Const_Column_Iterator columns_begin() const noexcept;
    Const_Column_Iterator columns_cbegin() const noexcept;

    Column_Iterator columns_end() noexcept;
    Const_Column_Iterator columns_end() const noexcept;
    Const_Column_Iterator columns_cend() const noexcept;

    reverse_column_iterator columns_rbegin() noexcept;
    const_reverse_column_iterator columns_rbegin() const noexcept;
    const_reverse_column_iterator columns_crbegin() const noexcept;

    reverse_column_iterator columns_rend() noexcept;
    const_reverse_column_iterator columns_rend() const noexcept;
    const_reverse_column_iterator columns_crend() const noexcept;

    value_type columns_front();
    const_value_type columns_front() const;
    value_type columns_back();
    const_value_type columns_back() const;

    Diagonal_Iterator diagonals_begin() noexcept;
    Const_Diagonal_Iterator diagonals_begin() const noexcept;
    Const_Diagonal_Iterator diagonals_cbegin() const noexcept;

    Diagonal_Iterator diagonals_end() noexcept;
    Const_Diagonal_Iterator diagonals_end() const noexcept;
    Const_Diagonal_Iterator diagonals_cend() const noexcept;

    reverse_diagonal_iterator diagonals_rbegin() noexcept;
    const_reverse_diagonal_iterator diagonals_rbegin() const noexcept;
    const_reverse_diagonal_iterator diagonals_crbegin() const noexcept;

    reverse_diagonal_iterator diagonals_rend() noexcept;
    const_reverse_diagonal_iterator diagonals_rend() const noexcept;
    const_reverse_diagonal_iterator diagonals_crend() const noexcept;

    value_type diagonals_front();
    const_value_type diagonals_front() const;
    value_type diagonals_back();
    const_value_type diagonals_back() const;

};


class Matrix::View::Iterator{
    protected:
        gsl_matrix_view m_m;
        Vector::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Iterator();
        Iterator(const Matrix::View* m, size_t i);

        Iterator(const Iterator& other) : m_m(other.m_m), vector_view_m(other.vector_view_m), index_m(other.index_m) {}
        Iterator(Iterator&& other) : m_m(std::move(other.m_m)), vector_view_m(std::move(other.vector_view_m)), index_m(std::move(other.index_m)) {}
        virtual ~Iterator(){}

        Iterator& operator=(const Iterator&) = delete;
        Iterator& operator=(Iterator&&) = delete;

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);
        bool operator<=(const Iterator& other);
        bool operator>=(const Iterator& other);
        bool operator<(const Iterator& other);
        bool operator>(const Iterator& other);

        virtual Iterator& add_n(const size_t n) {this->index_m += n; return *this;}
        virtual Iterator& sub_n(const size_t n) {this->index_m -= n; return *this;}
};

class Matrix::View::Row_Iterator : public Matrix::View::Iterator {
    public:
        using value_type = Vector::View;
        using reference = value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Row_Iterator();
        Row_Iterator(const Matrix::View* m, size_t i);

        Row_Iterator(const Iterator& it) : Iterator(it) {}
        Row_Iterator(Iterator&& it) : Iterator(std::move(it)) {}

        Row_Iterator(const Row_Iterator& other) : Iterator(other) {}
        Row_Iterator(Row_Iterator&& other) : Iterator(std::move(other)) {}
        ~Row_Iterator(){}

        reference operator*();
        pointer operator->();

        Row_Iterator operator++(int) 
        {
                Row_Iterator tmp = *this; 
                this->add_n(1); 
                return tmp;
        }

        Row_Iterator operator--(int) {Row_Iterator tmp = *this; this->sub_n(1); return tmp;}
        Row_Iterator& operator++(){this->add_n(1); return *this;}
        Row_Iterator& operator--(){this->sub_n(1); return *this;}
        Row_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Row_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Row_Iterator operator+(Row_Iterator it, size_t n) {return it += n;}
        friend Row_Iterator operator+(size_t n, Row_Iterator it) {return it + n;}
        friend Row_Iterator operator-(Row_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Row_Iterator& it1, const Row_Iterator& it2) {return it1.index_m - it2.index_m;}

        Row_Iterator       operator[](size_t n) {return *this + n;}
        const Row_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::View::Column_Iterator : public Matrix::View::Iterator {
    public:
        using value_type = Vector::View;
        using reference = value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Column_Iterator();
        Column_Iterator(const Matrix::View* m, size_t i);

        Column_Iterator(const Iterator& it) : Iterator(it) {}
        Column_Iterator(Iterator&& it) : Iterator(std::move(it)) {}

        Column_Iterator(const Column_Iterator&) = default;
        Column_Iterator(Column_Iterator&&)  = default;
        ~Column_Iterator(){}

        reference operator*();
        pointer operator->();

        Column_Iterator operator++(int) {Column_Iterator tmp = *this; this->add_n(1); return tmp;}
        Column_Iterator operator--(int) {Column_Iterator tmp = *this; this->sub_n(1); return tmp;}
        Column_Iterator& operator++(){this->add_n(1); return *this;}
        Column_Iterator& operator--(){this->sub_n(1); return *this;}
        Column_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Column_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Column_Iterator operator+(Column_Iterator it, size_t n) {return it += n;}
        friend Column_Iterator operator+(size_t n, Column_Iterator it) {return it + n;}
        friend Column_Iterator operator-(Column_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Column_Iterator& it1, const Column_Iterator& it2) {return it1.index_m - it2.index_m;}

        Column_Iterator       operator[](size_t n) {return *this + n;}
        const Column_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::View::Diagonal_Iterator : public Matrix::View::Iterator {
    public:
        using value_type = Vector::View;
        using reference = value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        reference operator*();
        pointer operator->();

        Diagonal_Iterator();
        Diagonal_Iterator(const Matrix::View* m, size_t i);

        Diagonal_Iterator(const Iterator& it) : Iterator(it) {}
        Diagonal_Iterator(Iterator&& it) : Iterator(std::move(it)) {}

        Diagonal_Iterator(const Diagonal_Iterator&) = default;
        Diagonal_Iterator(Diagonal_Iterator&&)  = default;
        ~Diagonal_Iterator(){}

        Diagonal_Iterator operator++(int) {Diagonal_Iterator tmp = *this; this->add_n(1); return tmp;}
        Diagonal_Iterator operator--(int) {Diagonal_Iterator tmp = *this; this->sub_n(1); return tmp;}
        Diagonal_Iterator& operator++(){this->add_n(1); return *this;}
        Diagonal_Iterator& operator--(){this->sub_n(1); return *this;}
        Diagonal_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Diagonal_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Diagonal_Iterator operator+(Diagonal_Iterator it, size_t n) {return it += n;}
        friend Diagonal_Iterator operator+(size_t n, Diagonal_Iterator it) {return it + n;}
        friend Diagonal_Iterator operator-(Diagonal_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Diagonal_Iterator& it1, const Diagonal_Iterator& it2) {return it1.index_m - it2.index_m;}

        Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Diagonal_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::View::Const_Iterator{
    protected:
        gsl_matrix_view m_m;
        Vector::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();
        Const_Iterator(const Matrix::View* m, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&)  = default;
        virtual ~Const_Iterator(){}

        Const_Iterator& operator=(const Const_Iterator&) = delete;
        Const_Iterator& operator=(Const_Iterator&&) = delete;
        
        Const_Iterator& add_n(const size_t n) noexcept {this->index_m += n; return *this;}
        Const_Iterator& sub_n(const size_t n) noexcept {this->index_m -= n; return *this;}

        bool operator==(const Const_Iterator& other);
        bool operator!=(const Const_Iterator& other);
        bool operator<=(const Const_Iterator& other);
        bool operator>=(const Const_Iterator& other);
        bool operator<(const Const_Iterator& other);
        bool operator>(const Const_Iterator& other);
};

class Matrix::View::Const_Row_Iterator : public Matrix::View::Const_Iterator {
    public:
        using value_type = const Vector::Const_View;
        using reference = value_type;
        using const_reference = value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Row_Iterator();
        Const_Row_Iterator(const Matrix::View* m, size_t i);

        Const_Row_Iterator(const Const_Row_Iterator&) = default;
        Const_Row_Iterator(Const_Row_Iterator&&)  = default;
        ~Const_Row_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Row_Iterator operator++(int) {Const_Row_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Row_Iterator operator--(int) {Const_Row_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Row_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Row_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Row_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Row_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Row_Iterator operator+(Const_Row_Iterator it, size_t n) {return it += n;}
        friend Const_Row_Iterator operator+(size_t n, Const_Row_Iterator it) {return it + n;}
        friend Const_Row_Iterator operator-(Const_Row_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Row_Iterator& it1, const Const_Row_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Row_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Row_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::View::Const_Column_Iterator : public Matrix::View::Const_Iterator {
    public:
        using value_type = const Vector::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Column_Iterator();
        Const_Column_Iterator(const Matrix::View* m, size_t i);

        Const_Column_Iterator(const Const_Column_Iterator&) = default;
        Const_Column_Iterator(Const_Column_Iterator&&)  = default;
        ~Const_Column_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Column_Iterator operator++(int) {Const_Column_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Column_Iterator operator--(int) {Const_Column_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Column_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Column_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Column_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Column_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Column_Iterator operator+(Const_Column_Iterator it, size_t n) {return it += n;}
        friend Const_Column_Iterator operator+(size_t n, Const_Column_Iterator it) {return it + n;}
        friend Const_Column_Iterator operator-(Const_Column_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Column_Iterator& it1, const Const_Column_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Column_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Column_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::View::Const_Diagonal_Iterator : public Matrix::View::Const_Iterator {
    public:
        using value_type = const Vector::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Diagonal_Iterator();
        Const_Diagonal_Iterator(const Matrix::View* m, size_t i);

        Const_Diagonal_Iterator(const Const_Diagonal_Iterator&) = default;
        Const_Diagonal_Iterator(Const_Diagonal_Iterator&&)  = default;
        ~Const_Diagonal_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Diagonal_Iterator operator++(int) {Const_Diagonal_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Diagonal_Iterator operator--(int) {Const_Diagonal_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Diagonal_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Diagonal_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Diagonal_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Diagonal_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Diagonal_Iterator operator+(Const_Diagonal_Iterator it, size_t n) {return it += n;}
        friend Const_Diagonal_Iterator operator+(size_t n, Const_Diagonal_Iterator it) {return it + n;}
        friend Const_Diagonal_Iterator operator-(Const_Diagonal_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Diagonal_Iterator& it1, const Const_Diagonal_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Diagonal_Iterator operator[](size_t n) const {return *this + n;}
};

class Matrix::Const_View{
private:
    gsl_matrix_const_view gsl_mat_view_m;
public:
    Const_View() = delete;
    Const_View(const Const_View&) = default;
    Const_View(Const_View&&) = default;
    Const_View& operator=(const Const_View&) = delete;
    Const_View& operator=(Const_View&&) = delete;
    ~Const_View() = default;

    Const_View(const Matrix& m, size_t k1, size_t k2, size_t n1, size_t n2);

    Const_View(const GSL::Block& b, size_t n1, size_t n2);
    Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2);
    Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda);

    Const_View(const double* data, size_t n1, size_t n2);
    Const_View(const double* data, size_t offset, size_t n1, size_t n2);
    Const_View(const double* data, size_t offset, size_t n1, size_t n2, size_t tda);

    Const_View(const Vector& v, size_t n1, size_t n2);
    Const_View(const Vector& v, size_t n1, size_t n2, size_t tda);

    operator const Matrix() const;

    const gsl_matrix* gsl_data() const;

    Matrix clone() const;

    Const_View view() const;
    Const_View cview() const;
    Const_View view(size_t k1, size_t k2, size_t n1, size_t n2) const;
    Const_View cview(size_t k1, size_t k2, size_t n1, size_t n2) const;

    size_t num_rows() const;
    size_t num_columns() const;
    std::pair<size_t, size_t> dim() const;
    size_t tda() const;

    double get(size_t i, size_t j);

    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    std::pair<size_t, size_t> max_index() const;
    std::pair<size_t, size_t> min_index() const;
    std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>> minmax_index() const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    Vector::Const_View row(size_t row) const;
    Vector::Const_View crow(size_t row) const;

    Vector::Const_View column(size_t column) const;
    Vector::Const_View ccolumn(size_t column) const;

    Vector::Const_View subrow(size_t i, size_t offset, size_t n) const;
    Vector::Const_View csubrow(size_t i, size_t offset, size_t n) const;
    Vector::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
    Vector::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
    Vector::Const_View diagonal() const;
    Vector::Const_View cdiagonal() const;
    Vector::Const_View subdiagonal(size_t k) const;
    Vector::Const_View csubdiagonal(size_t k) const;
    Vector::Const_View superdiagonal(size_t k) const;
    Vector::Const_View csuperdiagonal(size_t k) const;

    Vector::Const_View operator[](size_t row) const;

    Vector::Const_View at(size_t row) const;

    const double& operator()(size_t i, size_t j) const;

    const double& at(size_t i, size_t j) const;

    class Const_Iterator;
    class Const_Row_Iterator;
    class Const_Column_Iterator;
    class Const_Diagonal_Iterator;

    using value_type = Vector::Const_View;
    using const_value_type = Vector::Const_View;
    using difference_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    using const_row_iterator = Const_Row_Iterator;
    using const_reverse_row_iterator = std::reverse_iterator<const_row_iterator>;

    using const_column_iterator = Const_Column_Iterator;
    using const_reverse_column_iterator = std::reverse_iterator<const_column_iterator>;

    using const_diagonal_iterator = Const_Diagonal_Iterator;
    using const_reverse_diagonal_iterator = std::reverse_iterator<const_diagonal_iterator>;

    using const_iterator = const_row_iterator;
    using const_reverse_iterator = const_reverse_row_iterator;

    const_iterator begin() const noexcept; // {return this->rows_begin();}
    const_iterator cbegin() const noexcept; // {return this->rows_cbegin();}

    const_iterator end() const noexcept; // {return this->rows_end();}
    const_iterator cend() const noexcept; // {return this->rows_cend();}

    const_reverse_iterator rbegin() const noexcept; // {return rows_rbegin();}
    const_reverse_iterator crbegin() const noexcept; //  {return rows_crbegin();}

    const_reverse_iterator rend() const noexcept; // {return this->rows_rend();}
    const_reverse_iterator crend() const noexcept; // {return this->rows_crend();}

    const_value_type front() const {return rows_front();}
    const_value_type back() const {return rows_back();}


    const_row_iterator rows_begin() const noexcept;
    const_row_iterator rows_cbegin() const noexcept;

    const_row_iterator rows_end() const noexcept;
    const_row_iterator rows_cend() const noexcept;

    const_reverse_row_iterator rows_rbegin() const noexcept;
    const_reverse_row_iterator rows_crbegin() const noexcept;

    const_reverse_row_iterator rows_rend() const noexcept;
    const_reverse_row_iterator rows_crend() const noexcept;

    const_value_type rows_front() const;
    const_value_type rows_back() const;

    const_column_iterator columns_begin() const noexcept;
    const_column_iterator columns_cbegin() const noexcept;

    const_column_iterator columns_end() const noexcept;
    const_column_iterator columns_cend() const noexcept;

    const_reverse_column_iterator columns_rbegin() const noexcept;
    const_reverse_column_iterator columns_crbegin() const noexcept;

    const_reverse_column_iterator columns_rend() const noexcept;
    const_reverse_column_iterator columns_crend() const noexcept;

    const_value_type columns_front() const;
    const_value_type columns_back() const;

    const_diagonal_iterator diagonals_begin() const noexcept;
    const_diagonal_iterator diagonals_cbegin() const noexcept;

    const_diagonal_iterator diagonals_end() const noexcept;
    const_diagonal_iterator diagonals_cend() const noexcept;

    const_reverse_diagonal_iterator diagonals_rbegin() const noexcept;
    const_reverse_diagonal_iterator diagonals_crbegin() const noexcept;

    const_reverse_diagonal_iterator diagonals_rend() const noexcept;
    const_reverse_diagonal_iterator diagonals_crend() const noexcept;

    const_value_type diagonals_front() const;
    const_value_type diagonals_back() const;

};

class Matrix::Const_View::Const_Iterator{
    protected:
        gsl_matrix_const_view m_m;
        Vector::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();
        Const_Iterator(const Matrix::Const_View* m, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&)  = default;
        virtual ~Const_Iterator(){}

        Const_Iterator& operator=(const Const_Iterator&) = delete;
        Const_Iterator& operator=(Const_Iterator&&) = delete;

        Const_Iterator& add_n(const size_t n) {this->index_m += n; return *this;}
        Const_Iterator& sub_n(const size_t n) {this->index_m -= n; return *this;}

        bool operator==(const Const_Iterator& other);
        bool operator!=(const Const_Iterator& other);
        bool operator<=(const Const_Iterator& other);
        bool operator>=(const Const_Iterator& other);
        bool operator<(const Const_Iterator& other);
        bool operator>(const Const_Iterator& other);
    };

class Matrix::Const_View::Const_Row_Iterator : public Matrix::Const_View::Const_Iterator {
    public:
        using value_type = Vector::Const_View;
        using const_value_type = Vector::Const_View;
        using reference = const_value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Const_Row_Iterator();
        Const_Row_Iterator(const Matrix::Const_View* m, size_t i);

        Const_Row_Iterator(const Const_Row_Iterator&) = default;
        Const_Row_Iterator(Const_Row_Iterator&&)  = default;
        ~Const_Row_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Row_Iterator operator++(int) {Const_Row_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Row_Iterator operator--(int) {Const_Row_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Row_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Row_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Row_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Row_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Row_Iterator operator+(Const_Row_Iterator it, size_t n) {return it += n;}
        friend Const_Row_Iterator operator+(size_t n, Const_Row_Iterator it) {return it + n;}
        friend Const_Row_Iterator operator-(Const_Row_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Row_Iterator& it1, const Const_Row_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Row_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Row_Iterator operator[](size_t n) const {return *this + n;}
    };

class Matrix::Const_View::Const_Column_Iterator : public Matrix::Const_View::Const_Iterator {
    public:
        using value_type = Vector::Const_View;
        using const_value_type = Vector::Const_View;
        using reference = const_value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Const_Column_Iterator();
        Const_Column_Iterator(const Matrix::Const_View* m, size_t i);

        Const_Column_Iterator(const Const_Column_Iterator&) = default;
        Const_Column_Iterator(Const_Column_Iterator&&)  = default;
        ~Const_Column_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Column_Iterator operator++(int) {Const_Column_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Column_Iterator operator--(int) {Const_Column_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Column_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Column_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Column_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Column_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Column_Iterator operator+(Const_Column_Iterator it, size_t n) {return it += n;}
        friend Const_Column_Iterator operator+(size_t n, Const_Column_Iterator it) {return it + n;}
        friend Const_Column_Iterator operator-(Const_Column_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Column_Iterator& it1, const Const_Column_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Column_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Column_Iterator operator[](size_t n) const {return *this + n;}
    };

class Matrix::Const_View::Const_Diagonal_Iterator : public Matrix::Const_View::Const_Iterator {
    public:
        using value_type = Vector::Const_View;
        using const_value_type = Vector::Const_View;
        using reference = const_value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Const_Diagonal_Iterator();
        Const_Diagonal_Iterator(const Matrix::Const_View* m, size_t i);

        Const_Diagonal_Iterator(const Const_Diagonal_Iterator&) = default;
        Const_Diagonal_Iterator(Const_Diagonal_Iterator&&)  = default;
        ~Const_Diagonal_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Diagonal_Iterator operator++(int) {Const_Diagonal_Iterator tmp(*this); this->add_n(1); return tmp;}
        Const_Diagonal_Iterator operator--(int) {Const_Diagonal_Iterator tmp(*this); this->sub_n(1); return tmp;}
        Const_Diagonal_Iterator& operator++(){this->add_n(1); return *this;}
        Const_Diagonal_Iterator& operator--(){this->sub_n(1); return *this;}
        Const_Diagonal_Iterator& operator+=(size_t n){this->add_n(n); return *this;}
        Const_Diagonal_Iterator& operator-=(size_t n){this->sub_n(n); return *this;}

        friend Const_Diagonal_Iterator operator+(Const_Diagonal_Iterator it, size_t n) {return it += n;}
        friend Const_Diagonal_Iterator operator+(size_t n, Const_Diagonal_Iterator it) {return it + n;}
        friend Const_Diagonal_Iterator operator-(Const_Diagonal_Iterator it, size_t n) {return it -= n;}
        friend size_t operator-(const Const_Diagonal_Iterator& it1, const Const_Diagonal_Iterator& it2) {return it1.index_m - it2.index_m;}

        Const_Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Diagonal_Iterator operator[](size_t n) const {return *this + n;}
    };
}

#endif
