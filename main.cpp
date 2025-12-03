#include <iostream>
#include <cmath>
#include <array>
#include <cassert>
#include <vector>
#include <ranges>

constexpr std::size_t K = 23;

template <std::size_t, typename T>
using tensor_shape = T;

template <typename T, std::size_t... N>
class TensorFunction
{
public:
    explicit TensorFunction(std::vector<T> data) : functionValues(std::move(data))
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

    bool isSizePowerOfThree()
    {
        long long n = functionValues.size();
        while (n % 3 == 0)
            n /= 3;
        return n == 1;
    }

    bool isOneAdditive()
    {
        if(!(this->isSizePowerOfThree()))
        {
            return false;
        }
        if( (functionValues[0] == 0) && (std::abs(functionValues[26]) == 3) && (std::abs(functionValues[1]) <= 1)
        && (std::abs(functionValues[2]) <= 1) && (std::abs(functionValues[3]) <= 1)
        && (std::abs(functionValues[1] + functionValues[2] - functionValues[4]) <= 1) //X_1' u X_2'
        && (std::abs(functionValues[1] + functionValues[3] - functionValues[5]) <= 1) //X_1' u X_3'
        && (std::abs(functionValues[2] + functionValues[3] - functionValues[6]) <= 1) //X_2' u X_3'
        && (std::abs(functionValues[7] + functionValues[8] - functionValues[10]) <= 1) //X_1 u X_2
        && (std::abs(functionValues[7] + functionValues[9] - functionValues[11]) <= 1) //X_1 u X_3
        && (std::abs(functionValues[8] + functionValues[9] - functionValues[12]) <= 1) //X_2 u X_3
        && (std::abs(functionValues[2] + functionValues[7] - functionValues[13]) <= 1) //X_1 u X_2'
        && (std::abs(functionValues[3] + functionValues[7] - functionValues[14]) <= 1) //X_1 u X_3'
        && (std::abs(functionValues[1] + functionValues[8] - functionValues[15]) <= 1) //X_2 u X_1'
        && (std::abs(functionValues[3] + functionValues[8] - functionValues[16]) <= 1) //X_2 u X_3'
        && (std::abs(functionValues[1] + functionValues[9] - functionValues[17]) <= 1) //X_3 u X_1'
        && (std::abs(functionValues[2] + functionValues[9] - functionValues[18]) <= 1) //X_3 u X_2'
        && (std::abs(functionValues[7] + functionValues[16] - functionValues[19]) <= 1)  //X_1 u X_2 u X_3'
        && (std::abs(functionValues[8] + functionValues[14] - functionValues[19]) <= 1)  //X_1 u X_2 u X_3'
        && (std::abs(functionValues[3] + functionValues[10] - functionValues[19]) <= 1)  //X_1 u X_2 u X_3'
        && (std::abs(functionValues[7] + functionValues[18] - functionValues[20]) <= 1)  //X_1 u X_3 u X_2'
        && (std::abs(functionValues[9] + functionValues[13] - functionValues[20]) <= 1)  //X_1 u X_3 u X_2'
        && (std::abs(functionValues[2] + functionValues[11] - functionValues[20]) <= 1)  //X_1 u X_3 u X_2'
        && (std::abs(functionValues[8] + functionValues[17] - functionValues[21]) <= 1)  //X_2 u X_3 u X_1'
        && (std::abs(functionValues[9] + functionValues[15] - functionValues[21]) <= 1)  //X_2 u X_3 u X_1'
        && (std::abs(functionValues[1] + functionValues[12] - functionValues[21]) <= 1)  //X_2 u X_3 u X_1'
        && (std::abs(functionValues[1] + functionValues[6] - functionValues[22]) <= 1)   //X_1' u X_2' u X_3'
        && (std::abs(functionValues[2] + functionValues[5] - functionValues[22]) <= 1)   //X_1' u X_2' u X_3'
        && (std::abs(functionValues[3] + functionValues[4] - functionValues[22]) <= 1)   //X_1' u X_2' u X_3'
        && (std::abs(functionValues[7] + functionValues[6] - functionValues[23]) <= 1)   //X_1 u X_2' u X_3'
        && (std::abs(functionValues[2] + functionValues[14] - functionValues[23]) <= 1)  //X_1 u X_2' u X_3'
        && (std::abs(functionValues[3] + functionValues[13] - functionValues[23]) <= 1)  //X_1 u X_2' u X_3'
        && (std::abs(functionValues[8] + functionValues[5] - functionValues[24]) <= 1)   //X_2 u X_1' u X_3'
        && (std::abs(functionValues[1] + functionValues[16] - functionValues[24]) <= 1)  //X_2 u X_1' u X_3'
        && (std::abs(functionValues[3] + functionValues[15] - functionValues[24]) <= 1)  //X_2 u X_1' u X_3'
        && (std::abs(functionValues[9] + functionValues[4] - functionValues[25]) <= 1)   //X_3 u X_1' u X_2'
        && (std::abs(functionValues[1] + functionValues[18] - functionValues[25]) <= 1)  //X_3 u X_1' u X_2'
        && (std::abs(functionValues[2] + functionValues[17] - functionValues[25]) <= 1)  //X_3 u X_1' u X_2'
        && (std::abs(functionValues[7] + functionValues[12] - functionValues[26]) <= 1)  //X_1 u X_2 u X_3
        && (std::abs(functionValues[8] + functionValues[11] - functionValues[26]) <= 1)  //X_1 u X_2 u X_3
        && (std::abs(functionValues[9] + functionValues[10] - functionValues[26]) <= 1)  //X_1 u X_2 u X_3
        )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void printTensor()
    {
        typename std::vector<T>::iterator iter;
        int index = 0;
        for (iter = functionValues.begin(); iter != functionValues.end(); ++iter)
        {
            std::cout << index << " " << *iter << std::endl;
            index++;
        }
    }

    void printOneAdditive()
    {
        if(this->isOneAdditive())
        {
            std::cout << "| " << functionValues[0] << " " << functionValues[1] << " " << functionValues[2] << " | "
            << functionValues[9] << " " << functionValues[10] << " " << functionValues[11] << " | "
            << functionValues[18] << " " << functionValues[19] << " " << functionValues[20] << " |" << std::endl;
            std::cout << "| " << functionValues[3] << " " << functionValues[4] << " " << functionValues[5] << " | "
            << functionValues[12] << " " << functionValues[13] << " " << functionValues[14] << " | "
            << functionValues[21] << " " << functionValues[22] << " " << functionValues[23] << " |" << std::endl;
            std::cout << "| " << functionValues[6] << " " << functionValues[7] << " " << functionValues[8] << " | "
            << functionValues[15] << " " << functionValues[16] << " " << functionValues[17] << " | "
            << functionValues[24] << " " << functionValues[25] << " " << functionValues[26] << " |" << std::endl;
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
    auto to_tensor = [](const unsigned long long mask) {
        std::array<double, 4 + K> arr{0.0, 1.0, 1.0, 1.0};

        for (std::size_t i = 0; i < K; ++i)
            arr[4 + i] = (mask & (1ULL << i)) ? 3.0 : 1.0;

        const std::vector<double> vec(arr.begin(), arr.end());
        return TensorFunction<double,3,3,3>(vec);
    };

    constexpr auto all_masks = std::views::iota(0ULL, (1ULL << K));
    std::vector<TensorFunction<double,3,3,3>> one_additive;

    for (const auto mask : all_masks)
    {
        if (auto f = to_tensor(mask); f.isOneAdditive())
            one_additive.push_back(std::move(f));
    }

    std::cout << "Number of one-additive functions " << one_additive.size() << std::endl;
    return 0;
}
