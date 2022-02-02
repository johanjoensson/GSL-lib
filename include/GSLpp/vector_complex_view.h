#ifndef NEW_VECTOR_COMPLEX_VIEW_GLSPP_LIB_H
#define NEW_VECTOR_COMPLEX_VIEW_GLSPP_LIB_H

#include "GSLpp/block.h"

namespace GSL{

class Vector_Complex::View{
private:
    gsl_vector_complex_view gsl_vec_view_m;
protected:
    View() = default;

public:
    View(const View&) = default;
    View(View&&) = default;

    View& operator=(const View&) = default;
    View& operator=(View&&) = default;
    ~View() =  default;

    View(const Vector_Complex& v);
    View(const Vector_Complex& v, size_t offset, size_t size);
    View(const Vector_Complex& v, size_t offset, size_t stride, size_t size);

    View(Block& b);
    View(Block& b, size_t offset, size_t size);
    View(Block& b, size_t offset, size_t stride, size_t size);

    View(double* data, size_t size);
    View(double* data, size_t offset, size_t size);
    View(double* data, size_t offset, size_t stride, size_t size);

    View(gsl_vector_complex_view v);

    operator Vector_Complex();
    operator const Vector_Complex() const;

    gsl_vector_complex* gsl_data();
    const gsl_vector_complex* gsl_data() const;

    View& operator=(const Vector_Complex& v);
    View& operator=(Vector_Complex&& v);

    View& swap(Vector_Complex& v);
    View& swap(Vector_Complex&& v);
    View& swap(View& vv);
    View& swap(View&& vv);

    View& copy(const View& vv);
    View& copy(View&& vv);
    View& copy(const Vector_Complex& vv);
    View& copy(Vector_Complex&& vv);

    View& swap_elements(size_t i, size_t j);
    View& reverse();
    Vector_Complex clone() const;
    View& set_all(Complex val);
    View& set_zero();
    View& set(size_t i, Complex val);
    View& set_basis(size_t i);
    Complex get(size_t i) const;

/*
    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;
*/

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    double norm() const;
    double norm2() const;
    double l1_norm() const;

    // friend Complex dot(const Vector_Complex::View& a, const Vector_Complex::View& b)
    // {
    //     return dorc(a, b);
    // }
    // friend Complex dotc(const Vector_Complex::View& a, const Vector_Complex::View& b);
    // friend Complex dotu(const Vector_Complex::View& a, const Vector_Complex::View& b);
    //

    size_t size() const;
    size_t stride() const;

    Complex& operator[](size_t i);
    const Complex& operator[](size_t i) const;
    Complex& at(const size_t i);
    const Complex& at(const size_t i) const;

    View& conjugate();
    View& conj(){return this->conjugate();}

    View& operator+=(const Vector_Complex& other);
    View& operator-=(const Vector_Complex& other);
    View& operator*=(const Vector_Complex& other);
    View& operator/=(const Vector_Complex& other);

    View& operator+=(const Vector& other);
    View& operator-=(const Vector& other);
    View& operator*=(const Vector& other);
    View& operator/=(const Vector& other);

    View& operator+=(Complex s);
    View& operator-=(Complex s);
    View& operator*=(Complex s);
    View& operator/=(Complex s);

    Vector_Complex operator-() const;

    View view();
    Const_View view() const;
    View view(const size_t offset, const size_t size);
    Const_View view(const size_t offset, const size_t size) const;
    View view(const size_t offset, const size_t stride, const size_t size);
    Const_View view(const size_t offset, const size_t stride, const size_t size) const;
    Const_View cview() const;
    Const_View cview(const size_t offset, const size_t size) const;
    Const_View cview(const size_t offset, const size_t stride, const size_t size) const;


    Vector::View real();
    Vector::Const_View real() const;

    Vector::View imag();
    Vector::Const_View imag() const;


    class Iterator {
    private:
        gsl_vector_complex_view v_m;
        gsl_complex* data_m;
    public:
        using value_type = Complex;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Iterator();
        Iterator(Vector_Complex::View* v, size_t i);

        Iterator(const Iterator&) = default;
        Iterator(Iterator&&) = default;
        ~Iterator() = default;

        reference operator*();
        const_reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const_reference operator[](size_t n) const;

        Iterator& operator++();
        Iterator& operator--();
        Iterator  operator++(int);
        Iterator  operator--(int);

        Iterator& operator+=(size_t n);
        Iterator& operator-=(size_t n);

        Iterator operator+(size_t n)   const;
        Iterator operator-(size_t n)   const;

        difference_type operator-(Iterator const& other) const;

        bool operator<(Iterator const& other)  const;
        bool operator<=(Iterator const& other) const;
        bool operator>(Iterator const& other)  const;
        bool operator>=(Iterator const& other) const;
        bool operator!=(const Iterator &other) const;
        bool operator==(const Iterator &other) const;

    };
    class Const_Iterator {
    private:
        gsl_vector_complex_view v_m;
        const gsl_complex* data_m;
    public:
        using value_type = const Complex;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();

        Const_Iterator(const Vector_Complex::View* v, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&) = default;
        ~Const_Iterator() = default;

        reference operator*();
        const_reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const_reference operator[](size_t n) const;

        Const_Iterator& operator++();
        Const_Iterator& operator--();
        Const_Iterator  operator++(int);
        Const_Iterator  operator--(int);

        Const_Iterator& operator+=(size_t n);
        Const_Iterator& operator-=(size_t n);

        Const_Iterator operator+(size_t n)   const;
        Const_Iterator operator-(size_t n)   const;

        difference_type operator-(const Const_Iterator& other) const;

        bool operator<(const Const_Iterator& other)  const;
        bool operator<=(const Const_Iterator& other) const;
        bool operator>(const Const_Iterator& other)  const;
        bool operator>=(const Const_Iterator& other) const;
        bool operator!=(const Const_Iterator &other) const;
        bool operator==(const Const_Iterator &other) const;
    };

    using value_type = Complex;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = Iterator;
    using const_iterator = Const_Iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    reference& front();
    const_reference& front() const;
    reference& back();
    const_reference& back() const;
};

class Vector_Complex::Const_View{
private:
    gsl_vector_complex_const_view gsl_vec_view_m;
protected:
    Const_View() = delete;
public:
    Const_View(const Const_View&) = default;
    Const_View(Const_View&&) = default;

    Const_View& operator=(const Const_View&) = delete;
    Const_View& operator=(Const_View&&) = delete;
    ~Const_View() = default;

    Const_View(const Vector_Complex& v);
    Const_View(const Vector_Complex& v, const size_t offset, const size_t size);
    Const_View(const Vector_Complex& v, const size_t offset, const size_t stride, const size_t size);

    Const_View(const Block& b);
    Const_View(const Block& b, size_t offset, size_t size);
    Const_View(const Block& b, size_t offset, size_t stride, size_t size);

    Const_View(const double* data, size_t size);
    Const_View(const double* data, size_t offset, size_t size);
    Const_View(const double* data, size_t offset, size_t stride, size_t size);

    Const_View(gsl_vector_complex_const_view v);

    operator const Vector_Complex() const;

    const gsl_vector_complex* gsl_data() const;

    size_t size() const;
    size_t stride() const;

    const Complex& operator[](size_t i) const;
    const Complex& at(const size_t i) const;

    Vector_Complex clone() const;
    Complex get(size_t i) const;

/*
    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;
*/

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    // friend double norm(const Vector_Complex::Const_View& a);
    double norm() const;
    // friend double norm2(const Vector_Complex::Const_View& a);
    double norm2() const;
    // friend double l1_norm(const Vector_Complex::Const_View& a);
    double l1_norm() const;

    Vector::Const_View real() const;
    Vector::Const_View imag() const;


    Vector_Complex operator-() const;

    // friend Complex dot(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b)
    // {
    //     return dorc(a, b);
    // }
    // friend Complex dotc(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);
    // friend Complex dotu(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);

    // friend bool operator==(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);
    // friend bool operator!=(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);

    Const_View view() const;
    Const_View view(const size_t offset, const size_t size) const;
    Const_View view(const size_t offset, const size_t stride, const size_t size) const;
    Const_View cview() const;
    Const_View cview(const size_t offset, const size_t size) const;
    Const_View cview(const size_t offset, const size_t stride, const size_t size) const;

    class Const_Iterator {
    private:
        gsl_vector_complex_const_view const v_m;
        const gsl_complex * data_m;
    public:
        using value_type = const Complex;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();

        Const_Iterator(const Vector_Complex::Const_View* v, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&) = default;
        ~Const_Iterator() = default;

        reference operator*();
        const_reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const_reference operator[](size_t n) const;

        Const_Iterator& operator++();
        Const_Iterator& operator--();
        Const_Iterator  operator++(int);
        Const_Iterator  operator--(int);

        Const_Iterator& operator+=(size_t n);
        Const_Iterator& operator-=(size_t n);

        Const_Iterator operator+(size_t n)   const;
        Const_Iterator operator-(size_t n)   const;

        difference_type operator-(const Const_Iterator& other) const;

        bool operator<(const Const_Iterator& other)  const;
        bool operator<=(const Const_Iterator& other) const;
        bool operator>(const Const_Iterator& other)  const;
        bool operator>=(const Const_Iterator& other) const;
        bool operator!=(const Const_Iterator &other) const;
        bool operator==(const Const_Iterator &other) const;

    };

    using value_type = Complex;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using const_iterator = Const_Iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    const Complex& front() const;

    const Complex& back() const;
};
// double norm(const Vector_Complex::Const_View& a);
// double norm2(const Vector_Complex::Const_View& a);
// double l1_norm(const Vector_Complex::Const_View& a);
// Complex dotu(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);
// Complex dotc(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);

// Vector_Complex normalize(const Vector_Complex::Const_View& a);
// Vector_Complex mirror(const Vector_Complex::Const_View& v, const Vector_Complex::Const_View& a);

// bool operator==(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);
// bool operator!=(const Vector_Complex::Const_View& a, const Vector_Complex::Const_View& b);

}
#endif
