#include <exception>
#include <initializer_list>
#include <iostream>
template<class T>
class Stack {
public:
    Stack() {
        sz_ = 4;
        arr_ = new T[sz_];
        top_ = 0;
    }

    Stack(const Stack& other) {
        arr_ = new T[other.sz_];
        for (int i = 0; i < other.sz_; ++i) {
            arr_[i] = other.arr_[i];
        }
        sz_ = other.sz_;
        top_ = other.top_;
    }

    Stack(std::initializer_list<T> list) {
        sz_ = list.size();
        arr_ = new T[sz_];
        auto it = list.begin();
        top_ = 0;
        while (it != list.end()) {
            arr_[top_] = *it;
            top_++;
            it++;
        }
    }

    Stack(Stack&& other) {
        Stack(std::move(other))
    }

    Stack& operator=(const Stack& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr_;
        arr_ = new T[other.sz_];
        sz_ = other.sz_;
        for (int i = 0; i < sz_; ++i) {
            arr_[i] = other.arr_[i];
        }
        top_ = other.top_;
        return *this;
    }

    Stack& operator=(Stack&& other) {
        return Stack(std::move(other));
    }

    ~Stack() {
        delete[] arr_;
    }

    void Push(const T& value) {
        arr_[top_] = value;
        top_++;
        if (top_ * 2 >= sz_) {
            this->Resize();
        }
    }

    void Push(T&& value) {
        Push(std::move(value))
    }

    void Pop() {
        top_--;
    }

    bool Empty() const {
        return top_ == 0;
    }

    T& Top() {
        return arr_[top_ - 1];
    }

    void Clear() {
        top_ = 0;
    }

    int Size() {
        return top_;
    }

private:
    void Resize() {
        T* new_arr = new T[2 * sz_];
        for (int i = 0; i < sz_; ++i) {
            new_arr[i] = arr_[i];
        }
        sz_ *= 2;
        delete[] arr_;
        arr_ = new_arr;
    }


    T* arr_;
    int top_;
    int sz_;
};