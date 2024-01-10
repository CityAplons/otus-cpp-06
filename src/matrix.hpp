#pragma once

#include <algorithm>
#include <map>
#include <type_traits>
#include <vector>

namespace otus {

struct Position {
    size_t row, column;

    bool operator==(const Position &other) {
        return row == other.row && column == other.column;
    };
};

struct PositionComparator {
    bool operator()(const Position &lhs, const Position &rhs) const {
        bool upper = lhs.row < rhs.row;
        bool lower = !upper ? lhs.column < rhs.column : false;

        return upper || lower;
    }
};

template <class T, T DefaultValue, size_t Dim = 2> class Matrix {

  private:
    struct Proxy {
        Proxy(Matrix *mx, size_t row) noexcept : origin(mx), pos({row, 0}) {}

        Proxy &operator[](size_t column) {
            pos.column = column;
            return *this;
        }

        operator T() const {
            return origin->storage_.contains(pos) ? origin->storage_[pos]
                                                  : origin->default_;
        }

        Proxy &operator=(T value) {
            if (value == origin->default_ && origin->storage_.contains(pos)) {
                origin->storage_.erase(pos);
                origin->positions_.erase(std::remove(origin->positions_.begin(),
                                                     origin->positions_.end(),
                                                     pos),
                                         origin->positions_.end());
            } else {
                origin->storage_[pos] = value;
                origin->positions_.emplace_back(pos);
            }

            return *this;
        }

      private:
        Matrix *origin;
        Position pos;
    };

    std::map<Position, T, PositionComparator> storage_;
    std::vector<Position> positions_;
    T default_ = DefaultValue;

  public:
    struct Iterator {
        Iterator(Matrix *mx, size_t it) : origin(mx), iterator(it) {}

        // T &operator*() const {
        //     return positions.size() == 0
        //                ? origin->default_
        //                : origin->storage_[positions[iterator]];
        // }
        T *operator->() {
            return  origin->positions_.size() == 0
                       ? nullptr
                       : &origin->storage_[ origin->positions_[iterator]];
        }

        std::tuple<size_t, size_t, T> operator*() {
            if ( origin->positions_.size() == 0) {
                return std::make_tuple(0, 0, origin->default_);
            }

            Position pos = origin->positions_[iterator];
            return std::make_tuple(pos.row, pos.column, origin->storage_[pos]);
        }

        Iterator &operator++() {
            iterator++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++((*this).iterator);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.iterator == b.iterator;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.iterator != b.iterator;
        };

      private:
        Matrix *origin;
        size_t iterator = 0;
    };

    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, positions_.size()); }
    size_t size() { return storage_.size(); }

    Proxy operator[](size_t i) { return Proxy(this, i); }

    Matrix() {}
    ~Matrix() {}
};

}   // namespace otus
