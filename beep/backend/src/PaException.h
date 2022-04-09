#pragma once

#include <exception>
#include <string>

#include "portaudio.h"

namespace bb
{

// Wrapper around PaError
class PaException: public std::exception
{
public:
    explicit PaException(PaError err);

    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string error_msg_;
};

/**
 * Check the PaError
 *
 * If an error has occurred, throw it as a PaException
 */
void check_pa_error(PaError err);

} // namespace bb
