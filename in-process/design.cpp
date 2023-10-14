#include <iostream>
#include <vector>
#include <memory>
#include <variant>

// The CaberNet internals need a redesign.
// Here I will invent some crazy design patterns for my tensor library.
// This is my hobby, so if you see some crazy stuff, please don't be surprised.
// just doing it for fun.


class Body {
    public:
    using size_type = std::size_t;
    using shape_type = std::vector<size_type>;

    Body() = default;

    void reshape(const shape_type& shape) {
        size_ = 1; 
        shape_ = shape;
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

    size_type size() const { return size_; }
    size_type rank() const { return shape_.size(); }
    const shape_type& shape() { return shape_; }

    private:
    size_type size_ = 0;
    shape_type shape_;
};

enum class Trait {
    Variable,
    Expression,
    View
};

// variadic template for tensor

template<typename Type, Trait ... > class Tensor;

template<typename Type>
class Tensor<Type>  {
    public:
    using size_type = typename Body::size_type;
    using shape_type = typename Body::shape_type;
    
    virtual ~Tensor() = default;


    Body& body() { return body_; }
    const Body& body() const { return body_; }

    private:
    Body body_;
};

template<typename Type>
class Tensor<Type, Trait::Variable> : public Tensor<Type> {
    public:
    using size_type = typename Tensor<Type>::size_type;
    using shape_type = typename Tensor<Type>::shape_type;
    using Tensor<Type>::body;

    Tensor(const shape_type& shape, bool gradient_requirement = false) {
        body().reshape(shape);
        requires_gradient_ = gradient_requirement;
        if (requires_gradient_) {
            gradient_ = new Tensor<Type, Trait::Variable>(shape, false);
        }
    }




    /*
    Tensor(const shape_type& body, bool gradient_requirement = false) {
        body_ = body;
        requires_gradient_ = gradient_requirement;
        if (requires_gradient) {
            gradient_ = new Tensor<Type, Trait::Variable>(shape, false);
        }
    }

    const body_type& body() const { return body_; }

    private:
    bool requires_gradient_;
    std::vector<Type> data_;
    Tensor<Type, Trait::Variable>* gradient_;
    */

    Tensor<Type, Trait::Variable>* gradient() const { return gradient_; }

    private:
    bool requires_gradient_;
    Tensor<Type, Trait::Variable>* gradient_;


};

template<typename Type, class Derived>
class Expression {
    public:
    void print() {
        static_cast<Derived*>(this)->print();
    }
};

template<typename Type> class Linear;
template<typename Type> class ReLU;

template<typename Type>
class Tensor<Type, Trait::Expression> : public Tensor<Type> {
    using expression_variant = std::variant<
        Linear<Type>,
        ReLU<Type>
    >;

    public:
    template<class Expression>
    Tensor(Expression&& expression) {
        expression_ = { std::forward<Expression>(expression) };
    }

    void print() {
        std::visit([](auto&& argument) { argument.print(); }, expression_);
    }


    private:
    expression_variant expression_;
};

template<typename Type>
class Linear : public Expression<Type, Linear<Type>> {
    public:
    Linear() = default;
    Linear(int x) {
        x_ =  x;
    }

    void print() {
        std::cout << "Linear" << x_ << std::endl;
    }

    private:
    int x_;
};

template<typename Type>
class ReLU : public Expression<Type, ReLU<Type>> {
    public:
    ReLU() = default;
    void print() {
        std::cout << "ReLU" << std::endl;
    }
};

class array {
    public:

    Body& body() { return body_; }
    const Body& body() const { return body_; }

    private:
    Body body_;
};


int main() {
    Tensor<int, Trait::Expression>* tensor = new Tensor<int, Trait::Expression>{Linear<int>(2)};
    tensor->print();

    delete tensor;

    return 0;
}