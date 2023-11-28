#include <iostream>
#include <cmath>
#include <array>
#include <cassert>
#include <vector>

template <std::size_t, typename T>
using tensor_shape = T;

template <typename T, std::size_t... N>
class OneAdditiveFunction
{
public:

    OneAdditiveFunction(std::vector<T> data) : functionValues(std::move(data))
    {
        assert(functionValues.size() == (1 * ... * N));
    }
    
    T& operator()(const std::array<std::size_t, sizeof...(N)>& indexes)
    {
        return functionValues[calculateIndex(indexes)];
    }

    T& operator()(tensor_shape<N, std::size_t>... indexes)
    {
        return operator()({{indexes...}});
    }

    static std::size_t calculateIndex(const std::array<std::size_t, sizeof...(N)>& indexes)
    {
        std::array<std::size_t, sizeof...(N)> dimensions{{N...}};
        std::size_t index = 0;
        std::size_t shift = 1;
        for(size_t i = dimensions.size(); i > 0; --i) 
        {
            index += indexes[i - 1] * shift;
            shift *= dimensions[i - 1];
        }
        return index;
    }
private:
    std::vector<T> functionValues;
};

int main()
{
std::vector<OneAdditiveFunction<double, 3, 3, 2>> tensors;
}
