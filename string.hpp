#ifndef STRING_H
#define STRING_H


#include <cstddef> 
#include <cstring>
#include <iostream>


class String
{
    private:
        char* str_arr;

        size_t size;
    
    public:
        String() = default;

        String(const char* str_arr)
        {
            this->size = strlen(str_arr);
            this->str_arr = new char[this->size];

            strcpy(this->str_arr, str_arr);
        }

        String(const String& str)
        {
            this->size = str.size;
            this->str_arr = new char[this->size];

            strcpy(this->str_arr, str.str_arr);
        }

        String(size_t n, char c)
        {
            this->size = n;
            this->str_arr = new char[this->size];

            for(int i = 0; i < this->size; ++i)
                this->str_arr[i] = c;
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

        char& operator[](unsigned int index) { return this->str_arr[index]; }

        String& append(const String& str)
        {
            char* prev_str = new char[this->size];
            size_t prev_str_size = this->size;

            strcpy(prev_str, this->str_arr);

            delete[] this->str_arr;

            this->size = prev_str_size + str.size;

            this->str_arr = new char[this->size];

            strcpy(this->str_arr, prev_str);
            strcpy(this->str_arr + prev_str_size, str.str_arr);

            delete[] prev_str;

            return *this;
        }

        String& append(const char* str_arr)
        {
            char* prev_str = new char[this->size];
            size_t prev_str_size = this->size;

            strcpy(prev_str, this->str_arr);

            delete[] this->str_arr;

            this->size = prev_str_size + strlen(str_arr);

            this->str_arr = new char[this->size];

            strcpy(this->str_arr, prev_str);
            strcpy(this->str_arr + prev_str_size, str_arr);

            delete[] prev_str;

            return *this;
        }

        const char* c_str() const { return this->str_arr; }

        void resize(size_t n)
        {
            if(n != this->size)
            {
                char* prev_str = new char[this->size];
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

                delete[] prev_str;
            }
        }

        void resize(size_t n, char c)
        {
            if(n != this->size)
            {
                char* prev_str = new char[this->size];
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

                delete[] prev_str;
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