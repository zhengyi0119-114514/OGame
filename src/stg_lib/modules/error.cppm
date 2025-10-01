module;
#include "og_error_h.hpp"
export module OpenGame.error;
export namespace OpenGame::error
{
    using run_as_root_error = ::OpenGame::Error::RunAsRootAtException;
}

