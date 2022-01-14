#ifndef NEW_MATRIX_COMPLEX_VIEW_GLSPP_LIB_H
#define NEW_MATRIX_COMPLEX_VIEW_GLSPP_LIB_H

#include "GSLpp/block.h"

namespace GSL{
class Matrix_Complex::View {
private:
    gsl_matrix_complex_view gsl_mat_view_m;
public:
    View() = default;
    View(const View&) = default;
    View(View&&) = default;
    View& operator=(const View&) = default;
    View& operator=(View&&) = default;
    ~View() = default;

    View(const Matrix_Complex& m);
    View(const Matrix_Complex& m, size_t k1, size_t k2, size_t n1, size_t n2);

    View(GSL::Block& b, size_t n1, size_t n2);
    View(GSL::Block& b, size_t offset, size_t n1, size_t n2);
    View(GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda);

    View(double* data, size_t n1, size_t n2);
    View(double* data, size_t offset, size_t n1, size_t n2);
    View(double* data, size_t offset, size_t n1, size_t n2, size_t tda);

    View(Vector_Complex& v, size_t n1, size_t n2);
    View(Vector_Complex& v, size_t n1, size_t n2, size_t tda);

    View view();
    Const_View view() const;
    Const_View cview() const;
    View view(size_t k1, size_t k2, size_t n1, size_t n2);
    Const_View view(size_t k1, size_t k2, size_t n1, size_t n2) const;
    Const_View cview(size_t k1, size_t k2, size_t n1, size_t n2) const;

    operator Matrix_Complex();
    operator const Matrix_Complex() const;

    gsl_matrix_complex* gsl_data();
    const gsl_matrix_complex* gsl_data() const;

    View& operator=(const Matrix_Complex& m);
    View& operator=(Matrix_Complex&& m);

    View& swap(View& mv);
    View& swap(View&& mv);
    View& swap(Matrix_Complex& mv);
    View& swap(Matrix_Complex&& mv);


    View& copy(const View& mv);
    View& copy(View&& mv);
    View& copy(const Matrix_Complex& mv);
    View& copy(Matrix_Complex&& mv);

    View& transpose_copy(const Matrix_Complex& other);
    View&swap_rows(size_t i, size_t j);
    View& swap_columns(size_t i, size_t j);
    View& swap_rowcol(size_t i, size_t j);

    View& transpose();
    View& T();

    View& hermitian_transpose();
    View& H();

    size_t num_rows() const;
    size_t num_columns() const;
    std::pair<size_t, size_t> dim() const;
    size_t tda() const;

    View& set_all(Complex val);
    View& set_zero();
    View& set(size_t i, size_t j, Complex val);
    View& set_identity();
    Complex get(size_t i, size_t j) const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    View& operator+=(const Matrix_Complex& other);
    View& operator-=(const Matrix_Complex& other);
    View& operator*=(const Matrix_Complex& other);
    View& operator/=(const Matrix_Complex& other);

    View& operator+=(Complex s);
    View& operator-=(Complex s);
    View& operator*=(Complex s);
    View& operator/=(Complex s);

    View& multiply(const Matrix_Complex& other);

    Vector_Complex::View row(size_t row);
    Vector_Complex::Const_View row(size_t row) const;
    Vector_Complex::Const_View crow(size_t row) const;

    Vector_Complex::View column(size_t column);
    Vector_Complex::Const_View column(size_t column) const;
    Vector_Complex::Const_View ccolumn(size_t column) const;

    Vector_Complex::View subrow(size_t i, size_t offset, size_t n);
    Vector_Complex::Const_View subrow(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View csubrow(size_t i, size_t offset, size_t n) const;
    Vector_Complex::View subcolumn(size_t i, size_t offset, size_t n);
    Vector_Complex::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
    Vector_Complex::View diagonal();
    Vector_Complex::Const_View diagonal() const;
    Vector_Complex::Const_View cdiagonal() const;
    Vector_Complex::View subdiagonal(size_t k);
    Vector_Complex::Const_View subdiagonal(size_t k) const;
    Vector_Complex::Const_View csubdiagonal(size_t k) const;
    Vector_Complex::View superdiagonal(size_t k);
    Vector_Complex::Const_View superdiagonal(size_t k) const;
    Vector_Complex::Const_View csuperdiagonal(size_t k) const;

    Vector_Complex::View operator[](size_t row);
    Vector_Complex::Const_View operator[](size_t row) const;

    Vector_Complex::View at(size_t row);
    Vector_Complex::Const_View at(size_t row) const;

    Complex& operator()(size_t i, size_t j);
    const Complex& operator()(size_t i, size_t j) const;

    Complex& at(size_t i, size_t j);
    const Complex& at(size_t i, size_t j) const;

    class Iterator{
    protected:
        Matrix_Complex::View* m_m;
        Vector_Complex::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Iterator();
        Iterator(Matrix_Complex::View* m, size_t i);

        Iterator(const Iterator&) = default;
        Iterator(Iterator&&)  = default;
        virtual ~Iterator(){}

        Iterator& operator=(const Iterator&) = default;
        Iterator& operator=(Iterator&&) = default;

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);
        bool operator<=(const Iterator& other);
        bool operator>=(const Iterator& other);
        bool operator<(const Iterator& other);
        bool operator>(const Iterator& other);

    };

    class Row_Iterator : public Iterator {
    public:
        using value_type = Vector_Complex::View;
        using const_value_type = const Vector_Complex::View;
        using reference = value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Row_Iterator();
        Row_Iterator(Matrix_Complex::View* m, size_t i);

        Row_Iterator(const Row_Iterator&) = default;
        Row_Iterator(Row_Iterator&&)  = default;
        ~Row_Iterator(){}

        reference operator*();
        pointer operator->();


        difference_type operator-(Row_Iterator const& other);

        Row_Iterator& operator++(){this->index_m += 1; return *this;}
        Row_Iterator& operator--(){this->index_m -= 1; return *this;}
        Row_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Row_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Row_Iterator operator+(size_t n) const {Row_Iterator tmp(*this); return tmp += n;}
        friend Row_Iterator operator+(size_t n, const Row_Iterator& it) {return it + n;}
        Row_Iterator operator-(size_t n) const {Row_Iterator tmp(*this); return tmp -= n;}
        Row_Iterator operator++(int) {Row_Iterator tmp(*this); ++(*this); return tmp;}
        Row_Iterator operator--(int) {Row_Iterator tmp(*this); --(*this); return tmp;}

        Row_Iterator       operator[](size_t n) {return *this + n;}
        const Row_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Column_Iterator : public Iterator {
    public:
        using value_type = Vector_Complex::View;
        using const_value_type = const Vector_Complex::View;
        using reference = value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Column_Iterator();
        Column_Iterator(Matrix_Complex::View* m, size_t i);

        Column_Iterator(const Column_Iterator&) = default;
        Column_Iterator(Column_Iterator&&)  = default;
        ~Column_Iterator(){}

        reference operator*();
        pointer operator->();


        difference_type operator-(Column_Iterator const& other);

        Column_Iterator& operator++(){this->index_m += 1; return *this;}
        Column_Iterator& operator--(){this->index_m -= 1; return *this;}
        Column_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Column_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Column_Iterator operator+(size_t n) const {Column_Iterator tmp(*this); return tmp += n;}
        friend Column_Iterator operator+(size_t n, const Column_Iterator& it) {return it + n;}
        Column_Iterator operator-(size_t n) const {Column_Iterator tmp(*this); return tmp -= n;}
        Column_Iterator operator++(int){Column_Iterator tmp(*this); (*this)++; return tmp;}
        Column_Iterator operator--(int){Column_Iterator tmp(*this); (*this)--; return tmp;}

        Column_Iterator       operator[](size_t n) {return *this + n;}
        const Column_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Diagonal_Iterator : public Iterator {
    public:
        using value_type = Vector_Complex::View;
        using const_value_type = Vector_Complex::View;
        using reference = value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const_value_type*;

        Diagonal_Iterator();
        Diagonal_Iterator(Matrix_Complex::View* m, size_t i);

        Diagonal_Iterator(const Diagonal_Iterator&) = default;
        Diagonal_Iterator(Diagonal_Iterator&&)  = default;
        ~Diagonal_Iterator(){}

        reference operator*();
        pointer operator->();


        difference_type operator-(Diagonal_Iterator const& other);

        Diagonal_Iterator& operator++(){this->index_m += 1; return *this;}
        Diagonal_Iterator& operator--(){this->index_m -= 1; return *this;}
        Diagonal_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Diagonal_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Diagonal_Iterator operator+(size_t n) const {Diagonal_Iterator tmp(*this); return tmp += n;}
        friend Diagonal_Iterator operator+(size_t n, const Diagonal_Iterator& it) {return it + n;}
        Diagonal_Iterator operator-(size_t n) const {Diagonal_Iterator tmp(*this); return tmp -= n;}
        Diagonal_Iterator operator++(int){Diagonal_Iterator tmp(*this); (*this)++; return tmp;}
        Diagonal_Iterator operator--(int){Diagonal_Iterator tmp(*this); (*this)--; return tmp;}

        Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Diagonal_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Const_Iterator{
    protected:
        const Matrix_Complex::View* m_m;
        Vector_Complex::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();
        Const_Iterator(const Matrix_Complex::View* m, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&)  = default;
        virtual ~Const_Iterator(){}

        Const_Iterator& operator=(const Const_Iterator&) = default;
        Const_Iterator& operator=(Const_Iterator&&) = default;

        bool operator==(const Const_Iterator& other);
        bool operator!=(const Const_Iterator& other);
        bool operator<=(const Const_Iterator& other);
        bool operator>=(const Const_Iterator& other);
        bool operator<(const Const_Iterator& other);
        bool operator>(const Const_Iterator& other);
    };

    class Const_Row_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const_value_type;
        using const_reference = const_value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Row_Iterator();
        Const_Row_Iterator(const Matrix_Complex::View* m, size_t i);

        Const_Row_Iterator(const Const_Row_Iterator&) = default;
        Const_Row_Iterator(Const_Row_Iterator&&)  = default;
        ~Const_Row_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Row_Iterator& operator++(){this->index_m += 1; return *this;}
        Const_Row_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Row_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Row_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Row_Iterator operator+(size_t n) const {Const_Row_Iterator tmp(*this); return tmp += n;}
        friend Const_Row_Iterator operator+(size_t n, const Const_Row_Iterator& it) {return it + n;}
        Const_Row_Iterator operator-(size_t n) const {Const_Row_Iterator tmp(*this); return tmp -= n;}
        Const_Row_Iterator operator++(int) const {Const_Row_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Row_Iterator operator--(int) const {Const_Row_Iterator tmp(*this); (*this)--; return tmp;}
        difference_type operator-(Const_Row_Iterator const& other);

        Const_Row_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Row_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Const_Column_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Column_Iterator();
        Const_Column_Iterator(const Matrix_Complex::View* m, size_t i);

        Const_Column_Iterator(const Const_Column_Iterator&) = default;
        Const_Column_Iterator(Const_Column_Iterator&&)  = default;
        ~Const_Column_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Column_Iterator& operator++(){this->index_m += 1; return *this;}
        Const_Column_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Column_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Column_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Column_Iterator operator+(size_t n) const {Const_Column_Iterator tmp(*this); return tmp += n;}
        friend Const_Column_Iterator operator+(size_t n, const Const_Column_Iterator& it) {return it + n;}
        Const_Column_Iterator operator-(size_t n) const {Const_Column_Iterator tmp(*this); return tmp -= n;}
        Const_Column_Iterator operator++(int){Const_Column_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Column_Iterator operator--(int){Const_Column_Iterator tmp(*this); (*this)--; return tmp;}
        difference_type operator-(Const_Column_Iterator const& other);

        Const_Column_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Column_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Const_Diagonal_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Diagonal_Iterator();
        Const_Diagonal_Iterator(const Matrix_Complex::View* m, size_t i);

        Const_Diagonal_Iterator(const Const_Diagonal_Iterator&) = default;
        Const_Diagonal_Iterator(Const_Diagonal_Iterator&&)  = default;
        ~Const_Diagonal_Iterator(){}

        const_reference operator*();
        pointer operator->();

        Const_Diagonal_Iterator& operator++(){this->index_m += 1;; return *this;}
        Const_Diagonal_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Diagonal_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Diagonal_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Diagonal_Iterator operator+(size_t n) const {Const_Diagonal_Iterator tmp(*this); return tmp += n;}
        friend Const_Diagonal_Iterator operator+(size_t n, const Const_Diagonal_Iterator& it) {return it + n;}
        Const_Diagonal_Iterator operator-(size_t n) const {Const_Diagonal_Iterator tmp(*this); return tmp -= n;}
        Const_Diagonal_Iterator operator++(int){Const_Diagonal_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Diagonal_Iterator operator--(int){Const_Diagonal_Iterator tmp(*this); (*this)--; return tmp;}
        difference_type operator-(Const_Diagonal_Iterator const& other);

        Const_Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Diagonal_Iterator operator[](size_t n) const {return *this + n;}
    };

    using value_type = Vector_Complex::View;
    using const_value_type = Vector_Complex::Const_View;
    using difference_type = size_t;
    using reference = value_type   ;
    using const_reference = const value_type;
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

    iterator begin() noexcept {return this->rows_begin();}
    const_iterator begin() const noexcept {return this->rows_begin();}
    const_iterator cbegin() const noexcept {return this->rows_cbegin();}

    iterator end() noexcept {return this->rows_end();}
    const_iterator end() const noexcept {return this->rows_end();}

    const_iterator cend() const noexcept {return this->rows_cend();}
    reverse_iterator rbegin() noexcept {return rows_rbegin();}
    const_reverse_iterator rbegin() const noexcept {return rows_rbegin();}
    const_reverse_iterator crbegin() const noexcept  {return rows_crbegin();}

    reverse_iterator rend() noexcept {return this->rows_rend();}
    const_reverse_iterator rend() const noexcept {return this->rows_rend();}
    const_reverse_iterator crend() const noexcept {return this->rows_crend();}

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

class Matrix_Complex::Const_View{
private:
    gsl_matrix_complex_const_view gsl_mat_view_m;
public:
    Const_View() = default;
    Const_View(const Const_View&) = default;
    Const_View(Const_View&&) = default;
    Const_View& operator=(const Const_View&) = default;
    Const_View& operator=(Const_View&&) = default;
    ~Const_View() = default;

    Const_View(const Matrix_Complex& m, size_t k1, size_t k2, size_t n1, size_t n2);

    Const_View(const GSL::Block& b, size_t n1, size_t n2);
    Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2);
    Const_View(const GSL::Block& b, size_t offset, size_t n1, size_t n2, size_t tda);

    Const_View(const double* data, size_t n1, size_t n2);
    Const_View(const double* data, size_t offset, size_t n1, size_t n2);
    Const_View(const double* data, size_t offset, size_t n1, size_t n2, size_t tda);

    Const_View(const Vector_Complex& v, size_t n1, size_t n2);
    Const_View(const Vector_Complex& v, size_t n1, size_t n2, size_t tda);

    operator const Matrix_Complex() const;

    const gsl_matrix_complex* gsl_data() const;

    Const_View view() const;
    Const_View cview() const;

    size_t num_rows() const;
    size_t num_columns() const;
    std::pair<size_t, size_t> dim() const;
    size_t tda() const;

    Complex get(size_t i, size_t j);

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    Vector_Complex::Const_View row(size_t row) const;
    Vector_Complex::Const_View crow(size_t row) const;

    Vector_Complex::Const_View column(size_t column) const;
    Vector_Complex::Const_View ccolumn(size_t column) const;

    Vector_Complex::Const_View subrow(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View csubrow(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View subcolumn(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View csubcolumn(size_t i, size_t offset, size_t n) const;
    Vector_Complex::Const_View diagonal() const;
    Vector_Complex::Const_View cdiagonal() const;
    Vector_Complex::Const_View subdiagonal(size_t k) const;
    Vector_Complex::Const_View csubdiagonal(size_t k) const;
    Vector_Complex::Const_View superdiagonal(size_t k) const;
    Vector_Complex::Const_View csuperdiagonal(size_t k) const;

    Vector_Complex::Const_View operator[](size_t row) const;

    Vector_Complex::Const_View at(size_t row) const;

    const Complex& operator()(size_t i, size_t j) const;

    const Complex& at(size_t i, size_t j) const;

    class Const_Iterator{
    protected:
        const Matrix_Complex::Const_View* m_m;
        Vector_Complex::View vector_view_m;
        size_t index_m;

    public:
        using difference_type = size_t;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();
        Const_Iterator(const Matrix_Complex::Const_View* m, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&)  = default;
        virtual ~Const_Iterator(){}

        Const_Iterator& operator=(const Const_Iterator&) = default;
        Const_Iterator& operator=(Const_Iterator&&) = default;

        bool operator==(const Const_Iterator& other);
        bool operator!=(const Const_Iterator& other);
        bool operator<=(const Const_Iterator& other);
        bool operator>=(const Const_Iterator& other);
        bool operator<(const Const_Iterator& other);
        bool operator>(const Const_Iterator& other);
    };

    class Const_Row_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Row_Iterator();
        Const_Row_Iterator(const Matrix_Complex::Const_View* m, size_t i);

        Const_Row_Iterator(const Const_Row_Iterator&) = default;
        Const_Row_Iterator(Const_Row_Iterator&&)  = default;
        ~Const_Row_Iterator(){}

        const_reference operator*();
        pointer operator->();

        difference_type operator-(Const_Row_Iterator const& other);

        Const_Row_Iterator& operator++(){this->index_m += 1; return *this;}
        Const_Row_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Row_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Row_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Row_Iterator operator+(size_t n) const {Const_Row_Iterator tmp(*this); return tmp += n;}
        friend Const_Row_Iterator operator+(size_t n, const Const_Row_Iterator& it) {return it + n;}
        Const_Row_Iterator operator-(size_t n) const {Const_Row_Iterator tmp(*this); return tmp -= n;}
        Const_Row_Iterator operator++(int){Const_Row_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Row_Iterator operator--(int){Const_Row_Iterator tmp(*this); (*this)--; return tmp;}

        Const_Row_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Row_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Const_Column_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Column_Iterator();
        Const_Column_Iterator(const Matrix_Complex::Const_View* m, size_t i);

        Const_Column_Iterator(const Const_Column_Iterator&) = default;
        Const_Column_Iterator(Const_Column_Iterator&&)  = default;
        ~Const_Column_Iterator(){}

        const_reference operator*();
        pointer operator->();

        difference_type operator-(Const_Column_Iterator const& other);

        Const_Column_Iterator& operator++(){this->index_m += 1; return *this;}
        Const_Column_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Column_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Column_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Column_Iterator operator+(size_t n) const {Const_Column_Iterator tmp(*this); return tmp += n;}
        friend Const_Column_Iterator operator+(size_t n, const Const_Column_Iterator& it) {return it + n;}
        Const_Column_Iterator operator-(size_t n) const {Const_Column_Iterator tmp(*this); return tmp -= n;}
        Const_Column_Iterator operator++(int){Const_Column_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Column_Iterator operator--(int){Const_Column_Iterator tmp(*this); (*this)--; return tmp;}

        Const_Column_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Column_Iterator operator[](size_t n) const {return *this + n;}
    };

    class Const_Diagonal_Iterator : public Const_Iterator {
    public:
        using value_type = Vector_Complex::Const_View;
        using const_value_type = Vector_Complex::Const_View;
        using reference = const value_type;
        using const_reference = const value_type;
        using pointer = value_type*;
        using const_pointer = const value_type*;

        Const_Diagonal_Iterator();
        Const_Diagonal_Iterator(const Matrix_Complex::Const_View* m, size_t i);

        Const_Diagonal_Iterator(const Const_Diagonal_Iterator&) = default;
        Const_Diagonal_Iterator(Const_Diagonal_Iterator&&)  = default;
        ~Const_Diagonal_Iterator(){}

        const_reference operator*();
        pointer operator->();

        difference_type operator-(Const_Diagonal_Iterator const& other);

        Const_Diagonal_Iterator& operator++(){this->index_m += 1; return *this;}
        Const_Diagonal_Iterator& operator--(){this->index_m -= 1; return *this;}
        Const_Diagonal_Iterator& operator+=(size_t n){this->index_m += n; return *this;}
        Const_Diagonal_Iterator& operator-=(size_t n){this->index_m -= n; return *this;}

        Const_Diagonal_Iterator operator+(size_t n) const {Const_Diagonal_Iterator tmp(*this); return tmp += n;}
        friend Const_Diagonal_Iterator operator+(size_t n, const Const_Diagonal_Iterator& it) {return it + n;}
        Const_Diagonal_Iterator operator-(size_t n) const {Const_Diagonal_Iterator tmp(*this); return tmp -= n;}
        Const_Diagonal_Iterator operator++(int){Const_Diagonal_Iterator tmp(*this); (*this)++; return tmp;}
        Const_Diagonal_Iterator operator--(int){Const_Diagonal_Iterator tmp(*this); (*this)--; return tmp;}

        Const_Diagonal_Iterator       operator[](size_t n) {return *this + n;}
        const Const_Diagonal_Iterator operator[](size_t n) const {return *this + n;}
    };

    using value_type = Vector_Complex::Const_View;
    using const_value_type = Vector_Complex::Const_View;
    using difference_type = size_t;
    using reference = value_type;
    using const_reference = const_value_type;
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

    const_iterator begin() const noexcept {return this->rows_begin();}
    const_iterator cbegin() const noexcept {return this->rows_cbegin();}

    const_iterator end() const noexcept {return this->rows_end();}
    const_iterator cend() const noexcept {return this->rows_cend();}

    const_reverse_iterator rbegin() const noexcept {return rows_rbegin();}
    const_reverse_iterator crbegin() const noexcept  {return rows_crbegin();}

    const_reverse_iterator rend() const noexcept {return this->rows_rend();}
    const_reverse_iterator crend() const noexcept {return this->rows_crend();}

    const value_type front() const {return rows_front();}
    const value_type back() const {return rows_back();}


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
}

#endif
