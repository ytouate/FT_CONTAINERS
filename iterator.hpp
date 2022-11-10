/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:08:00 by ytouate           #+#    #+#             */
/*   Updated: 2022/11/10 12:55:25 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MACRO)
#define MACRO

#include <iostream>
#include <iterator>
#include <set>

template <class T>
class iterator
{
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;

    inline iterator(pointer ptr) : _ptr(ptr) {}
    inline reference operator*(void) { return *_ptr; }
    inline pointer operator->(void) { return _ptr; }
    inline ptrdiff_t operator - (iterator const &right) {return this->_ptr - right._ptr; }
    inline ptrdiff_t operator + (iterator const &right) {return this->_ptr + right._ptr; }
    inline iterator operator - (const int n) {return this->_ptr - n; }
    inline iterator operator + (const int n) {return this->_ptr + n; }
    inline bool operator==(iterator const &right) { return this->_ptr == right._ptr; }
    inline bool operator!=(iterator const &right) { return this->_ptr != right._ptr; }
    inline bool operator<(iterator const &right) { return this->_ptr < right._ptr; }
    inline bool operator>(iterator const &right) { return this->_ptr > right._ptr; }
    inline bool operator<=(iterator const &right) { return this->_ptr <= right._ptr; }
    inline bool operator>=(iterator const &right) { return this->_ptr >= right._ptr; }
    inline reference operator[](const int n) { return _ptr[n]; }
    inline iterator(iterator const &obj) { this->_ptr = obj._ptr; }

    inline iterator operator+=(difference_type n)
    {
        this->_ptr += n;
        return this->_ptr;
    }
    inline iterator operator-=(difference_type n)
    {
        this->_ptr -= n;
        return this;
    }
    inline iterator operator--(void)
    {
        iterator temp = *this;
        this->_ptr--;
        return temp;
    }
    inline iterator operator++(void)
    {
        iterator temp = *this;
        this->_ptr++;
        return temp;
    }
    inline iterator operator++(int notUsed)
    {
        (void)notUsed;
        this->_ptr++;
        return *this;
    }
    inline iterator operator--(int notUsed)
    {
        (void)notUsed;
        this->_ptr--;
        return *this;
    }
    inline iterator &operator=(iterator const &rhs)
    {
        rhs._ptr = this->_ptr;
        return *this;
    }

    ~iterator() {}

private:
    T *_ptr;
};

#endif
