//
// Created by fernando on 6/19/18.
//

#include <iostream>
#include "Logger.hpp"
#include "DataRecord.hpp"

/*********************************************************************
* Method Name: Logger
*
* Description:
*	Constructor. Opens output stream.
*
*********************************************************************/
Logger::Logger( std::string fileName ){
    outputStream.open( fileName );
    if( !outputStream.is_open() ){
        std::cout << "Failed to open log file." << std::endl;
        exit( 1 );
    }
    else{
        std::cout << "Succesfully opened log file " << fileName << std::endl;
    }
}

/*********************************************************************
* Method Name: ~Logger
*
* Description:
*	Destructor. Closes output stream.
*
*********************************************************************/
Logger::~Logger(){

}

/*********************************************************************
* Method Name: log
*
* Description:
*	Logs data record
*
*********************************************************************/
void Logger::log( DataRecord &record ){
    std::cout << record.dataToString();
    outputStream << record.dataToString();
}
