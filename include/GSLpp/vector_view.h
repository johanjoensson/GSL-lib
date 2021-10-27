#ifndef NEW_VECTOR_VIEW_GLSPP_LIB_H
#define NEW_VECTOR_VIEW_GLSPP_LIB_H

#include "GSLpp/block.h"

namespace GSL{

class Vector::View{
private:
    gsl_vector_view gsl_vec_view_m;
protected:
    View() = default;

public:
    View(const View&) = default;
    View(View&&) = default;

    View& operator=(const View&) = default;
    View& operator=(View&&) = default;
    ~View() =  default;

    View(const Vector& v);
    View(const Vector& v, size_t offset, size_t size);
    View(const Vector& v, size_t offset, size_t stride, size_t size);

    View(Block& b);
    View(Block& b, size_t offset, size_t size);
    View(Block& b, size_t offset, size_t stride, size_t size);

    View(double* data, size_t size);
    View(double* data, size_t offset, size_t size);
    View(double* data, size_t offset, size_t stride, size_t size);

    View(gsl_vector_view v);

    operator Vector();
    operator const Vector() const;

    View& operator=(const Vector& v);
    View& operator=(Vector&& v);

    View& swap(Vector& v);
    View& swap(Vector&& v);
    View& swap(View& vv);
    View& swap(View&& vv);

    View& copy(const View& vv);
    View& copy(View&& vv);
    View& copy(const Vector& vv);
    View& copy(Vector&& vv);

    View& swap_elements(size_t i, size_t j);
    View& reverse();
    Vector clone() const;
    View& set_all(double val);
    View& set_zero();
    View& set(size_t i, double val);
    View& set_basis(size_t i);
    double get(size_t i) const;

    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    double norm() const;
    double norm2() const;
    double l1_norm() const;

    size_t size() const;
    size_t stride() const;

    double& operator[](size_t i);
    const double& operator[](size_t i) const;
    double& at(const size_t i);
    const double& at(const size_t i) const;

    View& operator+=(const Vector& other);
    View& operator-=(const Vector& other);
    View& operator*=(const Vector& other);
    View& operator/=(const Vector& other);

    View& operator+=(double s);
    View& operator-=(double s);
    View& operator*=(double s);
    View& operator/=(double s);

    Vector operator-() const;

    View view();
    Const_View view() const;
    View view(const size_t offset, const size_t size);
    Const_View view(const size_t offset, const size_t size) const;
    View view(const size_t offset, const size_t stride, const size_t size);
    Const_View view(const size_t offset, const size_t stride, const size_t size) const;
    Const_View cview() const;
    Const_View cview(const size_t offset, const size_t size) const;
    Const_View cview(const size_t offset, const size_t stride, const size_t size) const;

    class Iterator {
    private:
        Vector::View* v_m;
        double* data_m;
    public:
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Iterator();
        Iterator(Vector::View* v, size_t i);

        Iterator(const Iterator&) = default;
        Iterator(Iterator&&) = default;
        ~Iterator() = default;

        reference operator*();
        const reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const reference operator[](size_t n) const;

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
        const Vector::View* v_m;
        double* data_m;
    public:
        using value_type = const double;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();

        Const_Iterator(const Vector::View* v, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&) = default;
        ~Const_Iterator() = default;

        reference operator*();
        const reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const reference operator[](size_t n) const;

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

    using value_type = double;
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

    double& front();
    const double& front() const;
    double& back();
    const double& back() const;
};

class Vector::Const_View{
private:
    gsl_vector_const_view gsl_vec_view_m;
protected:
    Const_View() = default;
public:
    Const_View(const Const_View&) = default;
    Const_View(Const_View&&) = default;

    Const_View& operator=(const Const_View&) = default;
    Const_View& operator=(Const_View&&) = default;
    ~Const_View() = default;

    Const_View(const Vector& v);
    Const_View(const Vector& v, const size_t offset, const size_t size);
    Const_View(const Vector& v, const size_t offset, const size_t stride, const size_t size);

    Const_View(Block& b);
    Const_View(Block& b, size_t offset, size_t size);
    Const_View(Block& b, size_t offset, size_t stride, size_t size);

    Const_View(double* data, size_t size);
    Const_View(double* data, size_t offset, size_t size);
    Const_View(double* data, size_t offset, size_t stride, size_t size);

    Const_View(gsl_vector_const_view v);

    operator const Vector() const;

    size_t size() const;
    size_t stride() const;

    const double& operator[](size_t i) const;
    const double& at(const size_t i) const;

    Vector clone() const;
    double get(size_t i) const;

    double max() const;
    double min() const;
    std::pair<double, double> minmax() const;

    size_t max_index() const;
    size_t min_index() const;
    std::pair<size_t, size_t> minmax_index() const;

    bool isnull() const;
    bool ispos() const;
    bool isneg() const;
    bool isnonneg() const;

    double norm() const;
    double norm2() const;
    double l1_norm() const;

    Const_View view() const;
    Const_View view(const size_t offset, const size_t size) const;
    Const_View view(const size_t offset, const size_t stride, const size_t size) const;
    Const_View cview() const;
    Const_View cview(const size_t offset, const size_t size) const;
    Const_View cview(const size_t offset, const size_t stride, const size_t size) const;

    Vector operator-() const;

    class Const_Iterator {
    private:
        const Vector::Const_View* v_m;
        double const * data_m;
    public:
        using value_type = const double;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator_category = std::random_access_iterator_tag;

        Const_Iterator();

        Const_Iterator(const Vector::Const_View* v, size_t i);

        Const_Iterator(const Const_Iterator&) = default;
        Const_Iterator(Const_Iterator&&) = default;
        ~Const_Iterator() = default;

        reference operator*();
        const reference operator*() const;
        pointer operator->();
        reference       operator[](size_t n);
        const reference operator[](size_t n) const;

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

    using value_type = double;
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

    const double& front() const;

    const double& back() const;
};
}
#endif
