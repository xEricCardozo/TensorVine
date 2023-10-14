#include <iostream>
#include <vector>
#include <memory>

// Here I will invent some crazy design patterns for my tensor library.
// This is my hobby, so if you see some crazy stuff, please don't be surprised.
// just doing it for fun.

class Body {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Body(const shape_type& shape) {
        shape_ = shape;
        size_ = 1;
        for (size_type dimension : shape_) size_ *= dimension;
    }

    size_type size() const { return size_; }
    size_type rank() const { return shape_.size(); }
    const shape_type& shape() { return shape_; }

    private:
    size_type size_;
    shape_type shape_;
};

enum class Trait {
    Variable,
    Expression,
};

// variadic template for tensor

template<typename Type, Trait ... > class Tensor;

template<typename Type>
class Tensor<Type> {
    public:
    virtual ~Tensor() = default;
    virtual void backward(Tensor<Type>* gradient) = 0;
    virtual Tensor<Type>* forward() = 0;
};

class Base {


};

template<typename Type>
class Tensor<Type, Trait::Variable> : public Tensor<Type>, Base {

};

template<typename Type>
class Tensor<Type, Trait::Expression> : public Tensor<Type>, Base {

};



int main() {
    return 0;
}