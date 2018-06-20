//
// Created by fernando on 6/19/18.
//

#ifndef TELEMETRY_PRACTICE_LOGGER_HPP
#define TELEMETRY_PRACTICE_LOGGER_HPP


#include <string>
#include <fstream>
#include "DataRecord.hpp"

class Logger{
public:
    /***********************************************************
    * Constructor & Destructor
    ***********************************************************/
    Logger( std::string fileName );
    ~Logger();

    /***********************************************************
    * Public Functions
    ***********************************************************/
    void log( DataRecord &record );

private:
    /***********************************************************
    * Private members
    ***********************************************************/
    std::ofstream outputStream;
};


#endif //TELEMETRY_PRACTICE_LOGGER_HPP
