#include <inttypes.hpp>
#include <defines.hpp>

#ifndef _OSL_LIST_HPP
#define _OSL_LIST_HPP

namespace osl
{
    template <class _type>
    class list
    {
    public:

        using type = _type;

    protected:

        struct node
        {
            type value;
            node *prev = 0, *next = 0;

            node(type value) _OSL_NOEXCEPT : value(value) { }
        };

    public:

        class const_iterator
        {
        public:

            explicit const_iterator(node *pointer) _OSL_NOEXCEPT : _node(pointer) { }

            type operator*() const _OSL_NOEXCEPT { 
                return _node->value;
            }

            bool operator==(const_iterator const &object) _OSL_NOEXCEPT {
                return _node == object._node;
            }

            bool operator!=(const_iterator const &object) _OSL_NOEXCEPT {
                return _node != object._node;
            }

            const_iterator operator--() _OSL_NOEXCEPT { 
                return _node = _node->prev, *this;
            }

            const_iterator operator++() _OSL_NOEXCEPT { 
                return _node = _node->next, *this;
            }

        protected:

            mutable node *_node;

        };

        class iterator : public const_iterator 
        {
        public:

            using const_iterator::const_iterator;

            type &operator*() _OSL_NOEXCEPT { 
                return this->_node->value;
            }

        };

    public:

        _OSL_CONSTEXPR list() _OSL_NOEXCEPT : _front(0), _back(0), _size(0) { }

        const_iterator start() const _OSL_NOEXCEPT {
            return const_iterator(_front);
        }

        iterator start() _OSL_NOEXCEPT {
            return iterator(_front);
        }

        type front() const _OSL_NOEXCEPT {
            return _front->value;
        }

        iterator push_front(type value) {
            node *to_push = new node(value);

            if (_front)
                _front->prev = to_push;
            else
                _back = to_push;

            to_push->next = _front;
            _front = to_push;
            _size++;

            return iterator(to_push);
        }

        void pop_front() {
            _front->next->prev = 0;
            node *buffer = _front;
            _front = _front->next;
            delete buffer;
        }

        const_iterator end() const _OSL_NOEXCEPT {
            return const_iterator(_back);
        }

        iterator end() _OSL_NOEXCEPT {
            return iterator(_back);
        }

        type back() const _OSL_NOEXCEPT {
            return _back->value;
        }

        iterator push_back(type value) {
            node *new_back = new node(value);

            if (_back)
                _back->next = new_back;
            else
                _front = new_back;  

            new_back->prev = _back;
            _back = new_back;
            _size++;
            
            return iterator(new_back);
        }

        void pop_back() {
            _back->prev->next = 0;
            node *buffer = _back;
            _back = _back->prev;
            delete buffer;
        }

    protected:

        node *_front, *_back;
        u64 _size;

    };
}

#endif