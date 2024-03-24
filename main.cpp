#include <iostream>
#include <cmath>
#include <array>
#include <cassert>
#include <vector>

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

    bool isOneAdditive()
    {
        if(functionValues.size() != 27)
        {
            return false;
        }
        if( (functionValues[0] == 0) && (std::abs(functionValues[1]) <= 1)
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
    std::vector<TensorFunction<double,3,3,3>> one_additive;
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w;
    for(a = 1; a < 4; a+=2)
    {
        for(b = 1; b < 4; b+=2)
        {
            for(c = 1; c < 4; c+=2)
            {
                for(d = 1; d < 4; d+=2)
                {
                    for(e = 1; e < 4; e+=2)
                    {
                        for(f = 1; f < 4; f+=2)
                        {
                            for(g = 1; g < 4; g+=2)
                            {
                                for(h = 1; h < 4; h+=2)
                                {
                                    for(i = 1; i < 4; i+=2)
                                    {
                                        for(j = 1; j < 4; j+=2)
                                        {
                                            for(k = 1; k < 4; k+=2)
                                            {
                                                for(l = 1; l < 4; l+=2)
                                                {
                                                    for(m = 1; m < 4; m+=2)
                                                    {
                                                        for(n = 1; n < 4; n+=2)
                                                        {
                                                            for(o = 1; o < 4; o+=2)
                                                            {
                                                                for(p = 1; p < 4; p+=2)
                                                                {
                                                                    for(q = 1; q < 4; q+=2)
                                                                    {
                                                                        for(r = 1; r < 4; r+=2)
                                                                        {
                                                                            for(s = 1; s < 4; s+=2)
                                                                            {
                                                                                for(t = 1; t < 4; t+=2)
                                                                                {
                                                                                    for(u = 1; u < 4; u+=2)
                                                                                    {
                                                                                        for(v = 1; v < 4; v+=2)
                                                                                        {
                                                                                            for(w = 1; w < 4; w+=2)
                                                                                            {
                                                                                                std::vector<double> vec;
                                                                                                vec.push_back(0.0);
                                                                                                vec.push_back(1.0);
                                                                                                vec.push_back(1.0);
                                                                                                vec.push_back(1.0);
                                                                                                vec.push_back(a);
                                                                                                vec.push_back(b);
                                                                                                vec.push_back(c);
                                                                                                vec.push_back(d);
                                                                                                vec.push_back(e);
                                                                                                vec.push_back(f);
                                                                                                vec.push_back(g);
                                                                                                vec.push_back(h);
                                                                                                vec.push_back(i);
                                                                                                vec.push_back(j);
                                                                                                vec.push_back(k);
                                                                                                vec.push_back(l);
                                                                                                vec.push_back(m);
                                                                                                vec.push_back(n);
                                                                                                vec.push_back(o);
                                                                                                vec.push_back(p);
                                                                                                vec.push_back(q);
                                                                                                vec.push_back(r);
                                                                                                vec.push_back(s);
                                                                                                vec.push_back(t);
                                                                                                vec.push_back(u);
                                                                                                vec.push_back(v);
                                                                                                vec.push_back(w);
                                                                                                TensorFunction<double, 3, 3, 3> fun(vec);
                                                                                                if(fun.isOneAdditive())
                                                                                                {
                                                                                                    one_additive.push_back(fun);
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "Number of one-additive functions " << one_additive.size() << std::endl;
    return 0;
}
