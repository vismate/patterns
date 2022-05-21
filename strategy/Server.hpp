#pragma once

#include <thread>

struct ConnectionPolicy
{
    virtual auto should_retry() -> bool = 0;
    virtual auto sleep_for() -> unsigned = 0;
};

struct RetryFiveTimes : ConnectionPolicy
{
    size_t tries = 5;

    virtual auto should_retry() -> bool override
    {
        return tries-- > 0;
    }

    virtual auto sleep_for() -> unsigned override
    {
        return (5 - tries) * 100;
    }
};

struct RetryForEver : ConnectionPolicy
{
    virtual auto should_retry() -> bool
    {
        return true;
    }

    virtual auto sleep_for() -> unsigned
    {
        return 100;
    }
};

inline auto connect_to_server() -> bool
{
    return (rand() % 7) == 0;
}

// Note to self: DLL example and game modding example

inline auto connect(ConnectionPolicy &pol) -> bool
{
    while (true)
    {
        if (connect_to_server())
        {
            return true;
        }
        else if (pol.should_retry())
        {
            std::cout << "Reconnecting...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(pol.sleep_for()));
            continue;
        }
        else
        {
            return false;
        }
    }
}
