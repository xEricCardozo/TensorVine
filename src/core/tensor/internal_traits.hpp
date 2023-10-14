#ifndef CORE_INTERNAL_TRAITS_HPP
#define CORE_INTERNAL_TRAITS_HPP

namespace core {

    enum class Trait {
        Variable,
        Expression,
        View
    };

    template<typename Type, Trait ... >
    class Tensor;
}

#endif // CORE_INTERNAL_TRAITS_HPP