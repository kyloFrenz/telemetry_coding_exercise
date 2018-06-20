//
// Created by fernando on 6/18/18.
//

#ifndef TELEMETRY_PRACTICE_RECORDWINDOW_HPP
#define TELEMETRY_PRACTICE_RECORDWINDOW_HPP


#include "DataRecord.hpp"
#include <deque>

class RecordWindow : public std::deque<DataRecord> {
public:
    /***********************************************************
    * Constructor
    ***********************************************************/
    RecordWindow( unsigned int maxWindowSize );

    /***********************************************************
    * Public Functions
    ***********************************************************/
    void addRecord( DataRecord &record );
    DataRecord process();
    DataRecord calculateAverage();

    /***********************************************************
    * Class constant
    ***********************************************************/
    unsigned long long MAX_TIME_GAP_IN_MILLISECONDS = 1500;

private:
    /***********************************************************
    * private members
    ***********************************************************/
    size_type maxWindowSize = 2;
};


#endif //TELEMETRY_PRACTICE_RECORDWINDOW_HPP
