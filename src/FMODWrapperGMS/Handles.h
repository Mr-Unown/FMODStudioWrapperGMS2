#pragma once
#include <stdio.h>
#include <vector>

#include <iostream>
#include <unordered_map>


template<typename T>
class Handles {
private:
    std::unordered_map<double, T> handles;
    std::vector<double> freeHandles;

public:
    Handles() {}

    double Add(const T& value) {
        double handle;
        if (freeHandles.empty()) {
            handle = handles.size() + 1;  // Assign a new handle if no freed handles are available
        }
        else {
            handle = freeHandles.back();  // Reuse the last freed handle
            freeHandles.pop_back();       // Remove it from the list of freed handles
        }
        handles[handle] = value;  // Add the value to the handles map
        return handle;
    }

    bool Remove(double handle) {
        auto it = handles.find(handle);
        if (it != handles.end()) {
            handles.erase(it);          // Remove the entry from the handles map
            freeHandles.push_back(handle);  // Add the handle to the list of freed handles
            return true;
        }
        return false;
    }

    T* Get(double handle) {
        auto it = handles.find(handle);
        if (it != handles.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    template<typename Function>
    void ForEach(Function&& func) {
        for (auto& entry : handles) {
            std::invoke(std::forward<Function>(func), entry.first);
        }
    }

};
