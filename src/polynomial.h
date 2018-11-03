#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include <gsl/gsl_poly.h>
#include "complex.h"

namespace GSL{
    /**************************************************************************
    * "Private" functions for "partial" specifications of polynomials.
    * Different functions needed for evaluating and printing real and
    * imagninary polynomials.
    **************************************************************************/
    namespace PolynomialInternal{
        double evaluate_polynomial(const std::vector<double>& coeffs, const int order, const double& x)
        {
            return gsl_poly_eval(&coeffs[0], order + 1, x);
        }

        Complex evaluate_polynomial(const std::vector<double>& coeffs, const int order, const Complex& z)
        {
            return Complex(gsl_poly_complex_eval(&coeffs[0], order + 1, *z.gsl_c));
        }

        Complex evaluate_polynomial(const std::vector<Complex>& coeffs, const int order, const Complex& z)
        {
            gsl_complex* ar = new gsl_complex[order + 1];
            for(int i = 0; i < order + 1; i++){
                ar[i] = *coeffs[i].gsl_c;
            }

            gsl_complex res = gsl_complex_poly_complex_eval(ar, order + 1, *z.gsl_c);
            delete [] ar;

            return res;
        }
	    template<class C>
	    std::string print_coefficient(const C& c)
	    {
		    return std::to_string(c);
	    }

	    std::string print_coefficient(const Complex& c)
	    {
		    return "(" + c.to_string() + ")";
	    }
    }

    template<class X, class C>
    class Polynomial{
    private:
        int order;
        std::vector<C> coeffs;
        int calc_order()
        {
            C zero = {};
            int i = 0;
            for(i = coeffs.size() - 1; i >= 0; i--){
                if(abs(coeffs[i] - zero) > 5e-16){
                    break;
                }
            }
            return i;
        };
    public:
        Polynomial(const std::vector<C>& c)
         : order(0), coeffs(c)
        {
            order = calc_order();
            coeffs.resize(order + 1);
        };

        Polynomial(std::initializer_list<C> c)
         : order(0), coeffs(c)
        {
            order = calc_order();
            coeffs.resize(order + 1);
        };

        template<class T>
        X evaluate(const T& x)
        {
            return PolynomialInternal::evaluate_polynomial(coeffs, order, x);
        }

        template<class T>
        X operator()(const T& x)
        {
            return this->evaluate(x);
        }

        Polynomial<X,C> operator+(const Polynomial<X,C> &p) const
        {
            int n = std::max(this->coeffs.size(), p.coeffs.size());
            std::vector<C> coeffs(n);
            for(size_t i = 0; i < n; i++){
                if(i < this->coeffs.size()){
                    coeffs[i] += this->coeffs[i];
                }
                if(i < p.coeffs.size()){
                    coeffs[i] += p.coeffs[i];
                }
            }

            return Polynomial<X, C>(coeffs);
        };

        Polynomial<X,C> operator-(const Polynomial<X,C> &p) const
        {
            size_t n = std::max(this->coeffs.size(), p.coeffs.size());
            std::vector<C> coeffs(n, C {});
            for(size_t i = 0; i < n; i++){
                if(i < this->coeffs.size()){
                    coeffs[i] += this->coeffs[i];
                }
                if(i < p.coeffs.size()){
                    coeffs[i] -= p.coeffs[i];
                }
            }
            return Polynomial<X, C>(coeffs);
        };

        Polynomial<X,C> operator*(const Polynomial<X,C> &p) const
        {
            int n = this->coeffs.size() + p.coeffs.size();
            std::vector<C> coeffs(n);
            for(size_t i = 0; i < this->coeffs.size(); i++){
                for(size_t j = 0; j < p.coeffs.size(); j++){
                    coeffs[i + j] += this->coeffs[i]*p.coeffs[j];
                }
            }

            return Polynomial<X, C>(coeffs);
        };

        std::pair<Polynomial<X,C>, Polynomial<X,C>> operator/(const Polynomial<X,C> &p) const
        {
            if( p.order < 0){
                throw std::runtime_error("Division by a polynomial of negative order!");
            }
            C zero = {};

            Polynomial<X, C> r = *this;
            Polynomial<X, C> q = {};
            q.order = r.order - p.order;
            q.coeffs = std::vector<C>(q.order + 1, zero);
            Polynomial<X, C> d = p;


            int shift = r.order - p.order;
            while(shift >= 0){
                d = p;
                for(int i = 0; i < shift; i++){
                    d.coeffs.insert(d.coeffs.begin(), zero);
                }
                d.order = d.calc_order();
                q.coeffs[shift] = r.coeffs[r.order]/d.coeffs[d.order];
                q.order = q.calc_order();
                for(size_t i = 0; i < d.coeffs.size(); i++){
                    d.coeffs[i] *= q.coeffs[shift];
                }
                r -= d;
                shift = r.order - p.order;
            }

            q.order = q.calc_order();
            q.coeffs.resize(q.order + 1);
            r.order = r.calc_order();
            r.coeffs.resize(r.order + 1);

            return std::pair<Polynomial<X, C>, Polynomial<X,C>> (q, r);
        };

        Polynomial<X,C>& operator+=(const Polynomial<X,C> &p)
        {
            *this = (*this) + p;
            return *this;
        };

        Polynomial<X,C>& operator-=(const Polynomial<X,C> &p)
        {
            *this = (*this) - p;
            return *this;
        };

        Polynomial<X,C>& operator*=(const Polynomial<X,C> &p)
        {
            *this = (*this) * p;
            return *this;
        };
        Polynomial<X,C>& operator/=(const Polynomial<X,C> &p)
        {
            *this = (*this/p).first;
            return *this;
        };

        friend std::ostream& operator<<(std::ostream &os, const Polynomial &p)
 	{
		bool first = true;
		C zero = {};
		for(int i = p.order; i >= 0; i--){
			if(!first){
				os <<  " + ";
			}
			if(i == 0 && p.coeffs[0] != zero){
				os << PolynomialInternal::print_coefficient(p.coeffs[0]);
				first = false;
			}else if(p.coeffs[i] != zero){
				os << PolynomialInternal::print_coefficient(p.coeffs[i]) << "x^" << i;
				first = false;
			}
		}
		return os;
	};
    };

}

#endif //POLYNOMIAL
