#ifndef CORE_INTERNAL_TENSOR_VARIABLE_HPP
#define CORE_INTERNAL_TENSOR_VARIABLE_HPP

#include "internal_tensor.hpp"

namespace core {

    template<typename Type>
    class Tensor<Type, Trait::Variable> : public Tensor<Type> {
        public:
        using value_type = Type;
        using storage_type = std::vector<value_type>;
        using size_type = Body::size_type;
        using shape_type = Body::shape_type;
        using iterator = typename storage_type::iterator;
        using const_iterator = typename storage_type::const_iterator;

        ~Tensor() override { if (requires_gradient()) delete gradient_; }
        Tensor(const Tensor& other) = delete;
        Tensor(Tensor&& other) = delete;
        Tensor& operator=(const Tensor& other) = delete;
        Tensor& operator=(Tensor&& other) = delete;

        Tensor(const shape_type& shape, bool gradient_requirement = false) {
            this->body().reshape(shape);
            this->requires_gradient(gradient_requirement);
            if (requires_gradient()) {
                gradient_ = new Tensor<Type, Trait::Variable>(shape, false);
            }
        }

        iterator begin() { return data_.begin(); }
        iterator end() { return data_.end(); }
        const_iterator begin() const { return data_.cbegin(); }
        const_iterator end() const { return data_.cend(); }
        const_iterator cbegin() const { return data_.cbegin(); }
        const_iterator cend() const { return data_.cend(); }

        Tensor<Type, Trait::Variable>* gradient() const { return gradient_; }

        private:  
        storage_type data_;
        Tensor<Type, Trait::Variable>* gradient_ = nullptr;

    };
}

#endif // CORE_INTERNAL_TENSOR_VARIABLE_HPP