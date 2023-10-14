#ifndef CORE_INTERNAL_BODY_HPP
#define CORE_INTERNAL_BODY_HPP

#include <iostream>
#include <vector>

namespace core {

    class Body {
        public:
        using size_type = std::size_t;
        using shape_type = std::vector<size_type>;

        Body() = default;

        void reshape(const shape_type& shape) {
            shape_ = shape;
            size_ = 1;
            for (size_type dimension : shape_) size_ *= dimension;
        }

        void melt() {
            shape_.clear();
            shape_.push_back(size_);
        }

        void collapse() {
            size_ = 0;
            shape_.clear();
        }

        private:
        size_type size_;
        shape_type shape_;

    };

}

#endif // CORE_INTERNAL_BODY_HPP