#ifndef CORE_INTERNAL_TENSOR_HPP
#define CORE_INTERNAL_TENSOR_HPP

#include <iostream>
#include <vector>

#include "internal_body.hpp"
#include "internal_traits.hpp"

namespace core {

    template<typename Type>
    class Tensor<Type>  {
        public:
        virtual ~Tensor() = default;

        bool requires_gradient() const { return requires_gradient_; }
        void requires_gradient(bool gradient_requirement) {
            requires_gradient_ = gradient_requirement;
        }

        Body& body() { return body_; }
        const Body& body() const { return body_; }

        private:
        bool requires_gradient_;
        Body body_;
    };

}

#endif // CORE_INTERNAL_TENSOR_HPP