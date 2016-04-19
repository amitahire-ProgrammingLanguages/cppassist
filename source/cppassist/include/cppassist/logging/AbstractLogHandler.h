#pragma once

#include <cppassist/cppassist_api.h>

namespace cppassist
{

class LogMessage;

/**
*  @brief
*    Abstract interface to handle LogMessages.
*    loggingzeug uses a global logging handler to dispatch all generated LogMessages.
*    This is the abstract interface for handling them.
*    Subclass this class if you wish to replace the global default logging
*    behavior in loggingzeug, which is to write everything to stdout.
*
*  @see setLoggingHandler
*  @see logging.h
*/
class CPPASSIST_API AbstractLogHandler
{
public:
    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractLogHandler()
    {
    }

    /**
    *  @brief
    *
    *  @param[in] message
    */
    virtual void handle(const LogMessage& message) = 0;
};

} // namespace cppassist
