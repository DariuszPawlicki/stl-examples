#ifndef STRING_H
#define STRING_H


#include <iostream>
#include <cstddef> 
#include <cstring>
#include <utility>
#include <stdexcept>


class String
{
    private:
        char* str_arr;

        size_t size;

        static const size_t npos = -1;
    
    public:
        String()
        {
            this->str_arr = new char[1];
            this->str_arr[0] = '\0';

            this->size = 0;
        }

        String(const char* str_arr)
        {
            this->size = strlen(str_arr);
            this->str_arr = new char[this->size + 1];

            strcpy(this->str_arr, str_arr);
        }

        String(const String& str)
        {
            this->size = str.size;
            this->str_arr = new char[this->size + 1];

            strcpy(this->str_arr, str.str_arr);
        }

        String(String&& str) noexcept : 
            str_arr(std::exchange(str.str_arr, nullptr)),
            size(std::exchange(str.size, 0)) {}

        String(size_t n, char c)
        {
            this->size = n;
            this->str_arr = new char[this->size + 1];

            for(int i = 0; i < this->size; ++i)
                this->str_arr[i] = c;
            
            this->str_arr[this->size] = '\0';
        }

        ~String() { delete[] this->str_arr; }

        String operator+(const String& str)
        {
            String tmp_str = *this;
            tmp_str.append(str);

            return tmp_str;
        }

        String operator+(const char* str_arr)
        {
            String tmp_str = *this;
            tmp_str.append(str_arr);

            return tmp_str;
        }

        String& operator+=(const String& str)
        {
            this->append(str);

            return *this;
        }

        String& operator+=(const char* str_arr)
        {
            this->append(str_arr);

            return *this;
        }

        String& operator=(const String& str)
        {
            if(this != &str)
            {
                delete[] this->str_arr;
                
                this->size = str.size;
                this->str_arr = new char[this->size + 1];

                for(size_t i = 0; i < this->size; ++i)
                    this->str_arr[i] = str[i];
                
            }

            return *this;
        }

        String& operator=(String&& str)
        {
            if(this != &str)
            {
                delete[] this->str_arr;
                
                this->size = std::exchange(str.size, 0);
                this->str_arr = std::exchange(str.str_arr, nullptr);
                
            }

            return *this;
        }

        bool operator==(const String& str)
        {
            if(this->size != str.size)
                return false;
            else
            {
                for(int i = 0; i < this->size; ++i)
                {
                    if(this->str_arr[i] != str.str_arr[i])
                        return false;
                }
            }

            return true;
        }

        bool operator==(const char* str_arr)
        {
            if(this->size != strlen(str_arr))
                return false;
            else
            {
                for(int i = 0; i < this->size; ++i)
                {
                    if(this->str_arr[i] != str_arr[i])
                        return false;
                }
            }

            return true;
        }

        char& operator[](size_t index) { return this->str_arr[index]; }

        const char& operator[](size_t index) const { return this->str_arr[index]; }

        String& append(const String& str)
        {
            char prev_str[this->size + 1];
            size_t prev_str_size = this->size;

            strcpy(prev_str, this->str_arr);

            delete[] this->str_arr;

            this->size = prev_str_size + str.size;

            this->str_arr = new char[this->size];

            strcpy(this->str_arr, prev_str);
            strcpy(this->str_arr + prev_str_size, str.str_arr);

            return *this;
        }

        String& append(const char* str_arr)
        {
            char prev_str[this->size + 1];
            size_t prev_str_size = this->size;

            strcpy(prev_str, this->str_arr);

            delete[] this->str_arr;

            this->size = prev_str_size + strlen(str_arr);

            this->str_arr = new char[this->size];

            strcpy(this->str_arr, prev_str);
            strcpy(this->str_arr + prev_str_size, str_arr);

            return *this;
        }

        void push_back(char c)
        {
            const char str_arr[] = {c};

            this->append(str_arr);
        }

        const char* c_str() const { return this->str_arr; }

        size_t copy(char* str_arr, size_t len, size_t pos = 0)
        {
            if(pos >= this->size || len == 0 || this->size == 0)
                return 0;
            
            size_t possible_chars_to_copy_count = this->size - pos;

            str_arr = new char[possible_chars_to_copy_count];

            if(len >= possible_chars_to_copy_count)
            {
                memcpy(str_arr, this->str_arr + pos, possible_chars_to_copy_count);

                return possible_chars_to_copy_count;
            } 
            else
            {
                memcpy(str_arr, this->str_arr + pos, len);

                return len;
            }
        }

        size_t find(const String& str, size_t pos = 0)
        {
            if(str.size > this->size || pos >= this->size - str.size)
                return String::npos;

            char cur_substr[str.size];

            for(size_t i = 0; i <= this->size - str.size; ++i)
            {
                memcpy(cur_substr, this->str_arr + i, str.size);

                size_t counter = 0;

                for(size_t j = 0; j < str.size; ++j)
                {
                    if(cur_substr[j] != str[j])
                        break;
                    else
                        ++counter;
                    
                    if(counter == str.size)
                        return i;
                }
            }
            
            return String::npos;
        }

        String substr(size_t pos = 0, size_t len = String::npos)
        {
            if(pos >= this->size)
                throw std::out_of_range("Position exceeds string length!");

            if((len > this->size && len != String::npos) || this->size - pos < len)
                return String();
            
            char tmp_str[this->size - pos + 1];

            if(len == String::npos)
                strcpy(tmp_str, this->str_arr + pos);
            else
            {
                memcpy(tmp_str, this->str_arr + pos, len);
                tmp_str[this->size - pos] = '\0';
            }
                
            return String(tmp_str);
        }

        void resize(size_t n)
        {
            if(n != this->size)
            {
                char prev_str[this->size + 1];
                size_t prev_str_size = this->size;

                strcpy(prev_str, this->str_arr);

                this->size = n;
                
                delete[] this->str_arr;

                this->str_arr = new char[this->size];

                if(prev_str_size < this->size)
                {
                    strcpy(this->str_arr, prev_str);
                }
                else
                {
                    for(int i = 0; i < this->size; ++i)
                        this->str_arr[i] = prev_str[i];
                }
            }
        }

        void resize(size_t n, char c)
        {
            if(n != this->size)
            {
                char prev_str[this->size + 1];
                size_t prev_str_size = this->size;

                strcpy(prev_str, this->str_arr);

                this->size = n;
                
                delete[] this->str_arr;

                this->str_arr = new char[this->size];

                if(prev_str_size < this->size)
                {
                    strcpy(this->str_arr, prev_str);

                    for(int i = prev_str_size; i < this->size; ++i)
                        this->str_arr[i] = c;
                }
                else
                {
                    for(int i = 0; i < this->size; ++i)
                        this->str_arr[i] = prev_str[i];         
                }
            }
        }

        void clear()
        {
            delete[] this->str_arr;

            this->size = 0;
        }

        size_t length() const { return this->size; }

        bool empty() const { return this->size == 0; }

        friend std::ostream& operator<<(std::ostream& stream, const String& str);
};

std::ostream& operator<<(std::ostream& stream, const String& str)
{
    stream << str.str_arr;

    return stream;
}

#endif