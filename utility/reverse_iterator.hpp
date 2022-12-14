/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:35:09 by ytouate           #+#    #+#             */
/*   Updated: 2023/01/05 19:45:55 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(REVERSE_ITERATOR_HPP)
#define REVERSE_ITERATOR_HPP

#include "../inc.hpp"

template <class T>
class iterator;

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer pointer;
        typedef typename ft::iterator_traits<Iterator>::reference reference;

        explicit reverse_iterator(Iterator x) : _iter(x) {}
        template <class U>
        reverse_iterator(const reverse_iterator<U> &u)
        {
            _iter = u.base();
        }
        Iterator base() const
        {
            return _iter;
        }
        inline reference operator*(void) const
        {
            Iterator temp = _iter;
            return *--temp;
        }
        pointer operator->(void) const
        {
            return &(operator*());
        }
        reverse_iterator() : _iter() {}

        inline reverse_iterator operator++(int)
        {
            reverse_iterator temp = *this;
            --this->_iter;
            return temp;
        }
        inline reverse_iterator operator--(int)
        {
            reverse_iterator temp = *this;
            ++this->_iter;
            return temp;
        }
        inline reverse_iterator operator++(void)
        {
            --this->_iter;
            return *this;
        }
        inline reverse_iterator operator--(void)
        {
            ++this->_iter;
            return *this;
        }
        inline reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator<Iterator>(this->base() - n);
        }
        reverse_iterator &operator+=(difference_type n)
        {
            this->_iter -= n;
            return *this;
        }
        reverse_iterator operator-(difference_type n) const
        {
            reverse_iterator<Iterator> temp(this->base() + n);
            return temp;
        }
        reverse_iterator &operator-=(difference_type n)
        {
            this->_iter += n;
            return *this;
        }
        reference operator[](reverse_iterator<Iterator>::difference_type n)
        {
            return _iter[-n - 1];
        }
        inline reverse_iterator &operator=(reverse_iterator const &rhs)
        {
            this->_iter.operator=(rhs._iter);
            return *this;
        }
        difference_type operator-(const reverse_iterator &other) const
        {
            return other._iter - this->_iter;
        }

    private:
        Iterator _iter;
    };
    template <class Iterator_a, class Iterator_b>
    inline bool operator==(
        ft::reverse_iterator<Iterator_a> const &x,
        ft::reverse_iterator<Iterator_b> const &y)
    {
        return x.base() == y.base();
    }

    template <class Iterator_a, class Iterator_b>
    bool operator<(
        const ft::reverse_iterator<Iterator_a> &x,
        const ft::reverse_iterator<Iterator_b> &y)
    {
        return x.base() > y.base();
    }

    template <class Iterator_a, class Iterator_b>
    bool operator!=(
        const ft::reverse_iterator<Iterator_a> &x,
        const ft::reverse_iterator<Iterator_b> &y)
    {
        return x.base() != y.base();
    }

    template <class Iterator, class Iterator_b>
    bool operator>(
        const ft::reverse_iterator<Iterator> &x,
        const ft::reverse_iterator<Iterator_b> &y)
    {
        return x.base() < y.base();
    }

    template <class Iterator, class Iterator_b>
    bool operator>=(
        const ft::reverse_iterator<Iterator> &x,
        const ft::reverse_iterator<Iterator_b> &y)
    {
        return x.base() <= y.base();
    }

    template <class Iterator, class Iterator_b>
    bool operator<=(
        const ft::reverse_iterator<Iterator> &x,
        const ft::reverse_iterator<Iterator_b> &y)
    {
        return x.base() >= y.base();
    }

    template <class Iterator>
    typename ft::reverse_iterator<Iterator> operator+(
        typename ft::reverse_iterator<Iterator>::difference_type n,
        const ft::reverse_iterator<Iterator> &x)
    {
        ft::reverse_iterator<Iterator> temp(x.base() - n);
        return temp;
    }
};

#endif // REVERSE_ITERATOR_HPP
