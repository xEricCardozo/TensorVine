#include <iostream>
#include <eigen3/Eigen/Dense>

/*
x = torch.tensor([[1,2,3],[-1,3,2]], dtype = torch.float32, requires_grad = True)
y = F.log_softmax(x, dim = 1)
I = torch.tensor([[1,3,1],[1,2,1]], dtype = torch.float32)
print(y)

y.backward(I)

print(x.grad)

tensor([[-2.4076, -1.4076, -0.4076],
        [-4.3266, -0.3266, -1.3266]], grad_fn=<LogSoftmaxBackward0>)
tensor([[ 0.5498,  1.7764, -2.3262],
        [ 0.9471, -0.8856, -0.0616]])


def log_softmax(x):
    max_x = np.max(x)
    logsumexp = max_x + np.log(np.sum(np.exp(x - max_x), axis=1, keepdims=True))
    return x - logsumexp

def log_softmax_backward(log_softmax_x, grad_output):
    softmax_x = np.exp(log_softmax_x)
    grad_input = grad_output - softmax_x * np.sum(grad_output, axis=1, keepdims=True)
    return grad_input

*/


int main() {
    std::vector<float> x = {1,2,3,-1,3,2};
    std::vector<float> y = x;
    std::vector<float> I = {1,3,1,1,2,1};

    /*calculate the softmax*/
    /*

    for axis = 1

    Eigen::Map<Eigen::Array<float, -1, -1, 1>> input_map(y.data(), 2, 3);

    auto shifted = (input_map.colwise() - input_map.rowwise().maxCoeff());
    input_map = shifted.colwise() - shifted.exp().rowwise().sum().log();

    std::cout << input_map << std::endl;

    //calculate the gradient

    Eigen::Map<Eigen::Array<float, -1, -1, 1>> grad_map(I.data(), 2, 3); 

    grad_map -= input_map.exp().colwise() * grad_map.rowwise().sum();

    std::cout << grad_map << std::endl;

    */


    Eigen::Map<Eigen::Array<float, -1, -1, 1>> input_map(y.data(), 2, 3);

    auto shifted = (input_map.colwise() - input_map.rowwise().maxCoeff());
    input_map = shifted.rowwise() - shifted.exp().colwise().sum().log();

    std::cout << input_map << std::endl;

    //calculate the gradient

    Eigen::Map<Eigen::Array<float, -1, -1, 1>> grad_map(I.data(), 2, 3); 

    grad_map -= input_map.exp().rowwise() * grad_map.colwise().sum();

    std::cout << grad_map << std::endl;

    return 0;   
}