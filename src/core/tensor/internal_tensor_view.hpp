#ifndef CORE_INTERNAL_TENSOR_VIEW_HPP
#define CORE_INTERNAL_TENSOR_VIEW_HPP

#include <iostream>
#include <span>

#include "internal_tensor.hpp"

namespace core {

    template<typename Type>
    class Tensor<Type, Trait::View> : public Tensor<Type> {
        public:
        using value_type = Type;
        using storage_type = std::span<value_type>;
        using iterator = typename storage_type::iterator;
        using const_iterator = typename storage_type::const_iterator;

        private:
        storage_type storage_;
    };
    
}

#endif // CORE_INTERNAL_TENSOR_VIEW_HPP