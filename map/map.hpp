/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:16:00 by ytouate           #+#    #+#             */
/*   Updated: 2023/01/12 13:42:16 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MAP_HPP)
#define MAP_HPP

#include "../inc.hpp"

namespace ft
{
    template <class Key,
              class Value,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, Value> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef Value mapped_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef ft::pair<const Key, Value> value_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::const_pointer const_pointer;
        typedef ft::map_iterator<value_type, allocator_type> iterator;
        typedef ft::map_iterator<value_type, allocator_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator::difference_type difference_type;
        typedef t_node<value_type, allocator_type> node_type;
        typedef size_t size_type;

        class value_compare
            : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : _alloc(alloc), _comp(comp) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
        {
            while (first != last)
            {
                _tree.insert(*first);
                first++;
            }
            _alloc = alloc;
            _comp = comp;
        }

        map(const map &x)
            : _tree(x._tree), _alloc(x._alloc), _comp(x._comp) {}

        ~map() { _tree.clear(); }

        map &operator=(const map &x)
        {
            this->_tree = x._tree;
            this->_alloc = x._alloc;
            this->_comp = x._comp;
            return *this;
        }

        iterator begin() { return _tree.begin(); }
        iterator end() { return _tree.end(); }
        const_iterator begin() const { return _tree.begin(); }
        const_iterator end() const { return _tree.end(); }
        reverse_iterator rbegin() { return _tree.rbegin(); }
        reverse_iterator rend() { return _tree.rend(); }
        reverse_iterator rbegin() const { return _tree.rbegin(); }
        reverse_iterator rend() const { return _tree.rend(); }

        bool empty() const { return _tree.size() == 0; }
        size_type size() const { return _tree.size(); }
        size_type max_size() const { return _alloc.max_size(); }

        pair<iterator, bool> insert(const value_type &val)
        {
            node_type *node = _tree.search(val.first);
            if (node)
                return ft::make_pair(iterator(node, _tree.getRoot()), false);
            return ft::make_pair(_tree.insert(val), true);
        }

        iterator insert(iterator, const value_type &val)
        {
            _tree.insert(val);
            return iterator(_tree.search(val.first), _tree.getRoot());
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                _tree.insert(*first);
        }

        void erase(iterator position)
        {
            iterator it = begin();
            iterator ite = end();
            while (it != ite)
            {
                if (it == position)
                    return _tree.erase(*it);
                ++it;
            }
        }

        void erase(iterator first, iterator last)
        {
            if (first == begin() and last == end())
                return clear();
            while (first != last)
                _tree.erase(*first++);
        }

        size_type erase(const key_type &k)
        {
            node_type *node = _tree.search(k);
            if (node == NULL)
                return 0;
            return (_tree.erase(*node->data), 1);
        }

        void swap(map &x)
        {
            _tree.swap(x._tree);
        }

        void clear() { _tree.clear(); }

        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return value_compare(_comp); }
        allocator_type get_allocator() const { return _alloc; }

        iterator find(const key_type &k) { return iterator(_tree.search(k), _tree.getRoot()); }
        const_iterator find(const key_type &k) const { return const_iterator(_tree.search(k), _tree.getRoot()); }
        size_type count(const key_type &k) const { return _tree.count(k); }

        iterator lower_bound(const key_type &k) const
        {
            return _tree.lower_bound(k);
        }
        iterator upper_bound(const key_type &k) const
        {
            return _tree.upper_bound(k);
        }
        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }
        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        mapped_type &operator[](const key_type &k)
        {
            return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
        }

        mapped_type &at(const key_type &k)
        {
            node_type *node = _tree.search(k);
            if (node == NULL)
                throw std::out_of_range("key not in map");
            else
                return node->data->second;
        }
        const mapped_type &at(const key_type &k) const
        {
            node_type *node = _tree.search(k);
            if (node == NULL)
                throw std::out_of_range("key not in map");
            else
                return node->data->second;
        }

    private:
        redBlackTree<value_type, allocator_type, key_compare> _tree;
        allocator_type _alloc;
        key_compare _comp;
    };
    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs,
                    const map<Key, T, Compare, Alloc> &rhs)
    {
        if (lhs.size() == rhs.size())
        {
            return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
        return false;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
                    const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs,
                   const map<Key, T, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
                    const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs,
                   const map<Key, T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
                    const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
}

#endif // MAP_HPP
