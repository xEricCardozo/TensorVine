#ifndef CORE_INTERNAL_TENSOR_EXPRESSION_HPP
#define CORE_INTERNAL_TENSOR_EXPRESSION_HPP

#include <iostream>
#include <variant>

#include "internal_tensor.hpp"

namespace core {

    enum class axis {
        Row,
        Column
    };

    template<typename Type> class Linear;
    template<typename Type> class ReLU;
    template<typename Type, axis dimension> class LogSoftmax;

    template<typename Type>
    class Tensor<Type, Trait::Expression> : public Tensor<Type> {
        using expression_variant = std::variant<
            Linear<Type>,
            ReLU<Type>,
            LogSoftmax<Type, axis::Row>,
            LogSoftmax<Type, axis::Column>
        >

        public:
        template<class Expression>
        Tensor(Expression&& expression) {
            expression_ = { std::forward<Expression>(expression) };
        }

        private:
        expression_variant expression_;
    };

}

#endif // CORE_INTERNAL_TENSOR_EXPRESSION_HPP