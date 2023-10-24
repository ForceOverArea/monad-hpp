#include <functional>

/// @brief A type to be returned by a function if 
/// @tparam T the type of the useful contained value
template<typename T>
class Maybe
{
private:
    bool is;
    T value;

public:

    Maybe()
    {
        is = false;
    }

    Maybe(T val)
    {
        is = true;
        value = val;
    }
    
    bool is_some()
    {
        return is;
    }

    T unwrap()
    {
        if (is)
            return value;
        else 
            throw;
    }

    template<typename U>
    Maybe<U> apply(std::function<Maybe<U> (T)> operation)
    {
        if (is)
            return operation(value);
        else 
            return Maybe();
    }
};

template<typename T, typename E>
union ResultUnion
{
    T ok;
    E err;
};

template<typename T, typename E>
class Result
{
private:
    bool ok;
    ResultUnion<T, E> value;


public: 
    Result(T ok_value)
    {
        ok = true;
        value.ok = ok_value;
    }

    Result(E error_value)
    {
        ok = false;
        value.err = error_value;
    }

    bool is_ok()
    {
        return ok;
    }

    T unwrap()
    {
        if (ok)
            return value.ok;
        else
            throw;
    }

    E unwrap_err()
    {
        if (!ok)
            return value.err;
        else
            throw;
    }

    template<typename U>
    Result<U, E> apply(std::function<Result<U, E> (T)> operation)
    {
        if (ok)
            return operation(value.ok);
        else
            return Result<U, E>(value.err);
    }
};

