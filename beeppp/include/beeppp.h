#include "beepc.h"

#include <exception>
#include <string>

namespace bpp
{

class BeepException: public std::exception
{
public:
    explicit BeepException(BeepError error)
            : error_msg(beep_get_error_message(error))
    {}

    [[nodiscard]] const char* what() const noexcept override
    {
        return error_msg.c_str();
    }

private:
    const std::string error_msg;
};

void success_or_throw(BeepError error)
{
    if (error != BeepError_NoError)
        throw BeepException(error);
}

void beep()
{
    success_or_throw(beep_beep());
}

void beep_at(float frequency)
{
    success_or_throw(beep_beep_at(frequency));
}

class ScopedBeeper
{
public:
    ScopedBeeper()
    {
        beep_init();
    }

    ~ScopedBeeper()
    {
        beep_terminate();
    }

    ScopedBeeper(const ScopedBeeper& other) = delete;

    ScopedBeeper& operator=(const ScopedBeeper& other) = delete;
};

} // namespace bpp
