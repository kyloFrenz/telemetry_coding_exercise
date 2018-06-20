#include <iostream>
#include "DataReader.hpp"
#include "RecordWindow.hpp"
#include "Logger.hpp"

/***********************************************************
* Configuration Constants
***********************************************************/
static const unsigned int RECORD_WINDOW_SZ = 5;
static const std::string DATA_FILE = "/home/fernando/telemetry_practice/data/telemetry.dat";
static const std::string OUTPUT_FILE = "/home/fernando/telemetry_practice/output_data.log";

/***********************************************************
* Main program
***********************************************************/
int main(){
    /***********************************************************
    * Instantiate classes
    ***********************************************************/
    DataReader dataReader( DATA_FILE );
    RecordWindow recordWindow( RECORD_WINDOW_SZ );
    Logger logger( OUTPUT_FILE );

    /***********************************************************
    * Process file/stream
    ***********************************************************/
    while( true ){
        DataRecord record;
        if(!dataReader.readNextRecord( record )){
            break;
        }
        recordWindow.addRecord( record );
        logger.log( record );
    }
    return 0;
}