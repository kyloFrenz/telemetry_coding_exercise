//
// Created by fernando on 6/18/18.
//

#include "DataReader.hpp"
#include <iostream>

/*********************************************************************
* Method Name: DataReader
*
* Description:
*	Constructor. Create/Open and input filestream of name fileName.
*   If failed to open the program will exit. This could be improved
*   by throwing exceptions.
*
*********************************************************************/
DataReader::DataReader( std::string fileName ){
    inputStream.open( fileName );
    if( !inputStream.is_open()){
        std::cout << "Failed to open data file." << std::endl;
        exit( 1 );
    }
    else{
        std::cout << "Succesfully opened input file " << fileName << std::endl;
    }
}

/*********************************************************************
* Method Name: ~DataReader
*
* Description:
*	Destructor. Closes input filesream if open.
*
*********************************************************************/
DataReader::~DataReader(){
    if( inputStream.is_open()){
        inputStream.close();
    }
}

/*********************************************************************
* Method Name: readNextRecord
*
* Description:
*	This functions reads the next line of the data stream and returns
*   a DataRecord struct.
*
*********************************************************************/
bool DataReader::readNextRecord( DataRecord &record ){
    /***********************************************************
    * Local variables
    ***********************************************************/
    DataRecord nextRecord{};
    std::string nextString = {};

    /***********************************************************
    * Ingest next line of stream.
    * Parse it into individual data elements.
    * Format individual elements and populate structure
    ***********************************************************/
    if( std::getline( inputStream, nextString )){
        unsigned int parsedElements = 0;
        while( parsedElements < ELEMENT_COUNT ){
            size_t pos = nextString.find( PARSING_DELIMITER );
            std::string token = nextString.substr( 0, pos );
            nextString.erase( 0, pos + PARSING_DELIMITER.length());

            /***********************************************************
            * Populate DataRecord
            ***********************************************************/
            switch( parsedElements ){
                case TIMESTAMP:{
                    nextRecord.setTime( token );
                    break;
                }

                case POWER:{
                    float power = atof(token.c_str());
                    nextRecord.setPower(power);
                    if( power < DataRecord::MINIMUM_POWER_MEASUREMENT ){
                        nextRecord.setToInvalid();
                        nextRecord.setAnomaly( DataRecord::INVALID_POWER );
                    }
                    break;
                }

                case VOLTAGE:{
                    float voltage = atof( token.c_str());
                    nextRecord.setVoltage( voltage );
                    if( voltage < DataRecord::MIN_VOLTAGE_MEASUREMENT || voltage > DataRecord::MAX_VOLTAGE_MEASUREMENT ){
                        nextRecord.setToInvalid();
                        nextRecord.setAnomaly( DataRecord::INVALID_VOLTAGE );
                    }
                    break;
                }

                case CURRENT:{
                    float current = atof( token.c_str());
                    nextRecord.setCurrent( current );
                    if( current < DataRecord::MIN_CURRENT_MEASUREMENT ){
                        nextRecord.setToInvalid();
                        nextRecord.setAnomaly( DataRecord::INVALID_CURRENT );
                    }
                    break;
                }

                default:
                    break;
            };
            parsedElements++;
        }
        record = nextRecord;
        return true;
    }
    else{
        std::cout << "End of Stream. Application Exiting.";
        return false;
    }
}
