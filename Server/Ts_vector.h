#ifndef TS_VECTOR_H
#define TS_VECTOR_H

#include<vector>
#include<mutex>
#include<memory>

template <typename T>
class Ts_vector{
private:
    std::vector<T> vector;
    std::mutex mutex;
public:
    Ts_vector(){}

    void push_back(T && element){ // pass by `const &` or `rvalue`
        std::lock_guard<std::mutex> lock(mutex);
        vector.push_back(element);
    }

    void clear(){
        std::lock_guard<std::mutex> lock(mutex);
        vector.clear();
    }

    T& operator[](const int i){ // not thread safe
        std::lock_guard<std::mutex> lock(mutex);
        return vector[i];
    }

    size_t size(){
        std::lock_guard<std::mutex> lock(mutex);
        return vector.size();
    }

    void delete_element(const int i){
        std::lock_guard<std::mutex> lock(mutex);
        vector.erase(vector.begin() + i);
    }
};

#endif