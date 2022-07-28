#include <vector>
#include <sstream>

#ifndef DEBUG_PDCTRL
#include <iostream>
#endif

namespace pdctr {

template<typename T>
class Item {
private:
    int64_t count_;
    T total_;
public:
    int64_t get_count() {
        return count_;
    }

    T get_total() {
        return total_;
    }

    T get_average() {
        return total_ / count_;
    }

    void add(const T& val) {
        total_ += val;
        count_ ++;
    }

    void clear() {
        total_ = 0;
        count_ = 0;
    }
};

template<typename T>
class Controller {
private:
    int& p_idx_;
    int idx_;

protected:
    int size_;
    std::vector<Item<T>> items_;

public:
    Controller(int size) {
        size_ = size;
        idx_ = 0;
        p_idx_ = &idx_;
    }
    Controller(int size, int& p_idx) {
        size_ = size;
        idx_ = 0;
        p_idx_ = p_idx;
    }

    bool init() {
        assert(size_ < 1);
        size_ = 1;
        items_.resize(size_);
    }

    int switch_slot() {
        if (&idx_ == p_idx_) {
            idx_ = (idx_ + 1) % size_;
        } else {
            *p_idx_ = (*p_idx_ + 1) % size_;
            idx_ = *p_idx_;
        }
        return idx_;
    }

    const Item<T>& get() const {
        int idx = *p_idx_;
        assert(items_.size() > idx);
        return items[idx];
    }

    int get_index_num() const {
        return *p_idx_;
    }

    void add(const T& val) {
        int idx = *p_idx_;
        assert(items_.size() > idx);
        items[idx].add(val);
    }

    virtual bool calculate() {
        return true;
    }
};

}