#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>
#include <iterator>
#include <cstddef>
#include <utility>
#include <cmath>


template<typename T>
class Vector
{
    private:

        T* items;
        size_t sz;
        size_t cap;
    

    private:

        class Iterator
        {
            using iterator_tag = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            private:

                pointer ptr;
            
            public:

                Iterator(pointer ptr)
                    :ptr(ptr){}
                

                reference operator*() { return *this->ptr; }
                pointer operator->() { return this->ptr; }


                Iterator& operator++() { ++this->ptr; return *this;}
                Iterator operator++(int) { Iterator tmp = *this; ++this->ptr; return tmp; }


                Iterator& operator+(difference_type n) { this->ptr += n; return *this; }
                Iterator& operator-(difference_type n) { this->ptr -= n; return *this; }

                Iterator& operator+=(difference_type n) { this->ptr += n; return *this; }
                Iterator& operator-=(difference_type n) { this->ptr -= n; return *this; }


                friend bool operator==(const Iterator& a, const Iterator& b) { return (a.ptr == b.ptr); }
                friend bool operator!=(const Iterator& a, const Iterator& b) { return (a.ptr != b.ptr); }
        };


        class ReverseIterator
        {
            using iterator_tag = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

            private:

                pointer ptr;
            
            public:

                ReverseIterator(pointer ptr)
                    :ptr(ptr){}
                

                reference operator*() { return *this->ptr; }
                pointer operator->() { return this->ptr; }


                ReverseIterator& operator++() { --this->ptr; return *this;}
                ReverseIterator operator++(int) { ReverseIterator tmp = *this; --this->ptr; return tmp; }


                ReverseIterator& operator+(difference_type n) { this->ptr -= n; return *this; }
                ReverseIterator& operator-(difference_type n) { this->ptr += n; return *this; }

                ReverseIterator& operator+=(difference_type n) { this->ptr -= n; return *this; }
                ReverseIterator& operator-=(difference_type n) { this->ptr += n; return *this; }


                friend bool operator==(const ReverseIterator& a, const ReverseIterator& b) { return (a.ptr == b.ptr); }
                friend bool operator!=(const ReverseIterator& a, const ReverseIterator& b) { return (a.ptr != b.ptr); }
        };


        class ConstIterator
        {
            using iterator_tag = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using const_pointer = const T*;
            using const_reference = const T&;


            private:

                const_pointer ptr;
            

            public:
                
                ConstIterator(const_pointer ptr)
                    :ptr(ptr){}
                

                const_reference operator*() const { return *this->ptr; }
                const_pointer operator->() const { return this->ptr; }


                ConstIterator& operator++() { ++this->ptr; return *this;}
                ConstIterator operator++(int) { ConstIterator tmp = *this; ++this->ptr; return tmp; }


                ConstIterator& operator+(difference_type n) { this->ptr += n; return *this; }
                ConstIterator& operator-(difference_type n) { this->ptr -= n; return *this; }

                ConstIterator& operator+=(difference_type n) { this->ptr += n; return *this; }
                ConstIterator& operator-=(difference_type n) { this->ptr -= n; return *this; }


                friend bool operator==(const ConstIterator& a, const ConstIterator& b) { return (a.ptr == b.ptr); }
                friend bool operator!=(const ConstIterator& a, const ConstIterator& b) { return (a.ptr != b.ptr); }
        };


        class ConstReverseIterator
        {
            using iterator_tag = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using const_pointer = const T*;
            using const_reference = const T&;

            private:

                const_pointer ptr;
            
            public:

                ConstReverseIterator(const_pointer ptr)
                    :ptr(ptr){}
                

                const_reference operator*() const { return *this->ptr; }
                const_pointer operator->() const { return this->ptr; }


                ConstReverseIterator& operator++() { --this->ptr; return *this;}
                ConstReverseIterator operator++(int) { ConstReverseIterator tmp = *this; --this->ptr; return tmp; }


                ConstReverseIterator& operator+(difference_type n) { this->ptr -= n; return *this; }
                ConstReverseIterator& operator-(difference_type n) { this->ptr += n; return *this; }

                ConstReverseIterator& operator+=(difference_type n) { this->ptr -= n; return *this; }
                ConstReverseIterator& operator-=(difference_type n) { this->ptr += n; return *this; }


                friend bool operator==(const ConstReverseIterator& a, const ConstReverseIterator& b) { return (a.ptr == b.ptr); }
                friend bool operator!=(const ConstReverseIterator& a, const ConstReverseIterator& b) { return (a.ptr != b.ptr); }
        };
    

    private:

        void re_alloc(size_t new_capacity)
        {
            T* new_items = new T[new_capacity];

            for(size_t i = 0; i < this->sz; ++i)
                new_items[i] = this->items[i];

            delete[] this->items;

            this->items = new_items;
            this->cap = new_capacity;
        }


    public:

        Vector()
            :items(new T[0]), sz(0), cap(0){}
        

        Vector(size_t size)
            :items(new T[size]), sz(0), cap(size){}
        

        Vector(size_t size, const T& item)
            :items(new T[size]), sz(size), cap(size)
            {
                for(size_t i = 0; i < this->sz; ++i)
                    this->items[i] = item;
            }
        

        Vector(const Vector<T>& vec)
            :sz(vec.sz), cap(vec.cap)
        {
            this->items = new T[this->cap];

            for(size_t i = 0; i < this->sz; ++i)
                this->items[i] = vec[i];
        }
        

        Vector(Vector<T>&& rhs) noexcept
            :items(std::exchange(rhs.items, nullptr)), sz(std::exchange(rhs.sz, 0)), 
             cap(std::exchange(rhs.cap, 0)) {}


        Vector(std::initializer_list<T> list)
            :sz(0), cap(list.size() * 2)
        {
            this->items = new T[this->cap];

            for(auto& item : list)
                this->push_back(item);
        }


        ~Vector() { delete[] this->items; }


        Vector<T>& operator=(const Vector<T>& vec) noexcept
        {   
            if(this != &vec)
            {
                delete[] this->items;

                this->sz = vec.sz;
                this->cap = vec.cap;
                this->items = new T[this->cap];

                for(size_t i = 0; i < this->sz; ++i)
                    this->items[i] = vec[i];
            }    

            return *this; 
        }    


        Vector<T>& operator=(Vector<T>&& rhs) noexcept
        {
            if(this != &rhs)
            {
                delete[] this->items;

                this->items = std::exchange(rhs.items, nullptr);
                this->sz = std::exchange(rhs.sz, 0);
                this->cap = std::exchange(rhs.cap, 0);
            }

            return *this;
        }
        

        T& operator[](size_t index) { return this->items[index]; }
        T& operator[](size_t index) const { return this->items[index]; }


        T& at(size_t n)
        {
            if(n < 0 || n >= this->sz)
                throw std::out_of_range("Cannot access vector outside it's boundries.");
            
            return *(this->items + n);
        }


        const T& at(size_t n) const
        {
            if(n < 0 || n >= this->sz)
                throw std::out_of_range("Cannot access vector outside it's boundries.");
            
            return *(this->items + n);
        }


        T& front() { return *this->begin(); }
        T& back() { return *(this->end() - 1); }


        void push_back(const T& item)
        {
            if(this->sz == this->cap)
            {
                size_t new_cap = this->cap;

                if(this->cap == 0)
                    new_cap = ++this->cap; 
                else
                    new_cap *= 2;
                
                this->re_alloc(new_cap);
            }

            this->items[this->sz] = item; 
            ++this->sz;
        }


        void pop_back()
        {
            if(this->sz > 0)
            {
                this->items[this->sz - 1].~T();
                --this->sz;

                if(this->sz <= std::round(this->cap / 4))
                    this->re_alloc(this->cap / 2);
            }
        }


        void resize(size_t n)
        {
            if(n < this->sz && n >= 0)
            {
                while(this->sz > n)
                    this->pop_back();
            }
            else if(n > this->sz)
            {
                if(n > this->cap)
                    this->re_alloc(n * 2);
                
                while(this->sz < n)
                    this->push_back(T());
            }
        }


        void resize(size_t n, const T& item)
        {
            if(n < this->sz)
            {
                while(this->sz > n)
                    this->pop_back();
            }
            else if(n > this->sz)
            {
                if(n > this->cap)
                    this->re_alloc(n * 2);
                
                while(this->sz < n)
                    this->push_back(item);
            }
        }


        void reserve(size_t n)
        {
            if(n > this->cap)
                this->re_alloc(n);
        }


        void shrink_to_fit()
        {
            if(this->cap > this->sz)
                this->re_alloc(this->sz);
        }


        void swap(Vector<T>& vec)
        {
            std::swap(this->items, vec.items);
            std::swap(this->cap, vec.cap);
            std::swap(this->sz, vec.sz);
        }


        void clear()
        {
            while(this->sz > 0)
                this->pop_back();
        }


        Iterator begin() { return Iterator(&this->items[0]); }
        Iterator end() { return Iterator(this->items + this->sz); }


        ReverseIterator rbegin() { return ReverseIterator(&this->items[this->sz - 1]); }
        ReverseIterator rend() { return ReverseIterator(this->items - 1); }


        ConstIterator cbegin() const { return ConstIterator(&this->items[0]); }
        ConstIterator cend() const { return ConstIterator(this->items + this->sz); }


        ConstReverseIterator crbegin() const { return ConstReverseIterator(&this->items[this->sz - 1]); }
        ConstReverseIterator crend() const { return ConstReverseIterator(this->items - 1); }


        T* data() { return this->items; }

        
        size_t size() const { return this->sz; }
        size_t capacity() const { return this->cap; }


        bool empty() const { return (this->sz == 0); }
};


template<typename T>
std::ostream& operator<<(std::ostream& ostr, const Vector<T>& vec)
{
    ostr << "{ ";

    for(size_t i = 0; i < vec.size(); ++i)
        ostr << vec[i] << ", ";
    
    ostr << " }";
    ostr << std::endl;

    return ostr;
}

#endif