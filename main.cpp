#include <iostream>
#include <cmath>
#include <array>
#include <cassert>
#include <vector>

template <std::size_t, typename T>
using tensor_shape = T;

template <typename T, std::size_t... N>
class DeltaAdditiveFunction
{
public:
    explicit DeltaAdditiveFunction(std::vector<T> data) : functionValues(std::move(data))
    {
        assert(functionValues.size() == (1 * ... * N));
    }

    T& operator()(const std::array<std::size_t, sizeof...(N)>& indexes)
    {
        return functionValues[calculateIndex(indexes)];
    }

    T& operator()(tensor_shape<N, std::size_t>... indexes)
    {
        return operator()({ {indexes...} });
    }
    bool isOneAdditive()
    {
        if(functionValues.size() != 18)
        {
            return false;
        }
        if( (std::abs(functionValues[0]) <= 1) && (std::abs(functionValues[1]) <= 1) && (std::abs(functionValues[2]) <= 1) //X_1', X_2', X_3'
        && (std::abs(functionValues[0] + functionValues[1] - functionValues[3]) <= 1) //X_1' u X_2'
        && (std::abs(functionValues[0] + functionValues[2] - functionValues[4]) <= 1) //X_1' u X_3'
        && (std::abs(functionValues[1] + functionValues[2] - functionValues[5]) <= 1) //X_2' u X_3'
        && (std::abs(functionValues[6] + functionValues[7] - functionValues[9]) <= 1) //X_1 u X_2
        && (std::abs(functionValues[6] + functionValues[8] - functionValues[10]) <= 1) //X_1 u X_3
        && (std::abs(functionValues[7] + functionValues[8] - functionValues[11]) <= 1) //X_2 u X_3
        && (std::abs(functionValues[2] + functionValues[6] - functionValues[13]) <= 1) //X_1 u X_3'
        && (std::abs(functionValues[1] + functionValues[6] - functionValues[12]) <= 1) //X_1 u X_2'
        && (std::abs(functionValues[2] + functionValues[7] - functionValues[14]) <= 1) //X_2 u X_3'
        && (std::abs(functionValues[2] + functionValues[9] - functionValues[15]) <= 1)   //X_1 u X_2 u X_3'
        && (std::abs(functionValues[1] + functionValues[11] - functionValues[16]) <= 1)  //X_1 u X_3 U X_2'
        && (std::abs(functionValues[0] + functionValues[11] - functionValues[17]) <= 1)  //X_2 u X_2 u X_1'
        && (std::abs(functionValues[6] + functionValues[14] - functionValues[15]) <= 1)  //X_1 u X_2 u X_3'
        && (std::abs(functionValues[7] + functionValues[13] - functionValues[15]) <= 1)  //X_1 u X_2 u X_3'
        && (std::abs(functionValues[8] + functionValues[12] - functionValues[16]) <= 1)) //X_1 u X_3 U X_2'
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void printDeltaAdditive()
    {
        typename std::vector<T>::iterator iter;
        int index = 0;
        for (iter = functionValues.begin(); iter != functionValues.end(); ++iter)
        {
            std::cout << index << " " << *iter << std::endl;
            index++;
        }
    }

    static std::size_t calculateIndex(const std::array<std::size_t, sizeof...(N)>& indexes)
    {
        std::array<std::size_t, sizeof...(N)> dimensions{ {N...} };
        std::size_t index = 0;
        std::size_t shift = 1;
        for (size_t i = dimensions.size(); i > 0; --i)
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
    std::vector<std::vector<double>> tensors;
    std::vector<double> V;
    for(int i = 0; i < 18; ++i)
        V.push_back(1.0);
    DeltaAdditiveFunction<double, 3, 3, 2> F(V);
    return 0;
}
