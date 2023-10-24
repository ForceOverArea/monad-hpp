#include <iostream>
#include <math.h>
#include <string>
#include "monad.hpp"

Result<float, const char *> safe_division(float num, float denom)
{
    using Output = Result<float, const char *>;
    if (denom == 0.0f)
        return Output((const char *)"error (safe_division): result is undefined...");
    else
        return Output((float)(num / denom));
}

Result<float, const char *> safe_sqrt(float radicand)
{
    using Output = Result<float, const char *>;
    if (radicand < 0.0f)
        return Output((const char *)"error (safe_sqrt): result is inaginary...");
    else 
        return Output((float)std::sqrt(radicand));
}

int main()
{
    Result<float, const char *> successful_result = safe_division(1, 2)
        .apply<float>(safe_sqrt)
        .apply<float>([](float x){ return safe_division(x, 4.0f); });

    Result<float, const char *> unsuccessful_result = safe_division(1, 0)
        .apply<float>(safe_sqrt)
        .apply<float>([](float x){ return safe_division(x, 4.0f); });

    std::cout << "Successful Result: " << successful_result.unwrap() << std::endl;

    std::cout << "Unsuccessful Result: " << unsuccessful_result.unwrap_err() << std::endl;

    return 0;
}
