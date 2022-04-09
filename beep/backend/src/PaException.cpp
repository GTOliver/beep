#include "PaException.h"

namespace bb
{

PaException::PaException(PaError error)
        : error_msg_(Pa_GetErrorText(error))
{}

const char* PaException::what() const noexcept
{
    return error_msg_.c_str();
}

void check_pa_error(PaError error)
{
    if (error != 0)
        throw PaException(error);
}

} // namespace bb
