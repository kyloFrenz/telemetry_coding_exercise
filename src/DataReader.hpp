//
// Created by fernando on 6/18/18.
//

#ifndef TELEMETRY_PRACTICE_DATAREADER_HPP
#define TELEMETRY_PRACTICE_DATAREADER_HPP

#include <string>
#include <fstream>
#include "DataRecord.hpp"

/***********************************************************
* DataReader Class.
*
* This clase will take an input
*
***********************************************************/
class DataReader{

public:
    /***********************************************************
    * Constructor & Destructor
    ***********************************************************/
    DataReader(std::string fileName);
    virtual ~DataReader();

    /***********************************************************
    * Public Functions
    ***********************************************************/
    bool readNextRecord( DataRecord &record );

    /***********************************************************
    * Class constans/enums
    ***********************************************************/
    enum ParsingElements{
        TIMESTAMP = 0,
        POWER,
        VOLTAGE,
        CURRENT,

        ELEMENT_COUNT
    };

    /***********************************************************
    * Class constants
    ***********************************************************/
    const std::string PARSING_DELIMITER = ", ";

private:
    /***********************************************************
    * Private Members
    ***********************************************************/
    std::ifstream inputStream;

};


#endif //TELEMETRY_PRACTICE_DATAREADER_HPP
