//
// Created by fernando on 6/18/18.
//

#include <iostream>
#include <sstream>
#include <cstring>
#include "DataRecord.hpp"

/***********************************************************
* Defining class constants
***********************************************************/
const float DataRecord::MINIMUM_POWER_MEASUREMENT = 0.0f;
const float DataRecord::MAX_VOLTAGE_MEASUREMENT = 485.0f;
const float DataRecord::MIN_VOLTAGE_MEASUREMENT = 475.0f;
const float DataRecord::MIN_CURRENT_MEASUREMENT = 0.0f;

/*********************************************************************
* Method Name: getTimeStamp
*
* Description:
*   Timestamp Getter
*
*********************************************************************/
std::string DataRecord::getTimeStamp() const{
    return timeString;
}

/*********************************************************************
* Method Name: getPower
*
* Description:
*	Power getter
*
*********************************************************************/
float DataRecord::getPower() const{
    return power;
}

/*********************************************************************
* Method Name: getVoltage
*
* Description:
*	Voltage Getter
*
*********************************************************************/
float DataRecord::getVoltage() const{
    return voltage;
}

/*********************************************************************
* Method Name: getCurrent
*
* Description:
*	Current getter
*
*********************************************************************/
float DataRecord::getCurrent() const{
    return current;
}

/*********************************************************************
* Method Name: setPower
*
* Description:
*	Power setter
*
*********************************************************************/
void DataRecord::setPower( const float &power ){
    this->power = power;
}

/*********************************************************************
* Method Name: setVolgate
*
* Description:
*	Voltage setter
*
*********************************************************************/
void DataRecord::setVoltage( const float &voltage ){
    this->voltage = voltage;
}

/*********************************************************************
* Method Name: setCurrent
*
* Description:
*	Current setter
*
*********************************************************************/
void DataRecord::setCurrent( const float &current ){
    this->current = current;
}

/*********************************************************************
* Method Name: setAnomality
*
* Description:
*	Anomality setter
*
*********************************************************************/
void DataRecord::setAnomaly( const recordAnomaly &anomaly ){
    anomalyVector.push_back( anomaly );
}

/*********************************************************************
* Method Name: setToInvalid
*
* Description:
*	Set record valid flag to false
*
*********************************************************************/
void DataRecord::setToInvalid(){
    valid = false;
}

/*********************************************************************
* Method Name: setProcessedFlag
*
* Description:
*	Set processed flag to true
*
*********************************************************************/
void DataRecord::setAvgProcessedFlag(){
    avgProcessed = true;
}

/*********************************************************************
* Method Name: setAvgPower
*
* Description:
*   Average power setter
*
*********************************************************************/
void DataRecord::setAvgPower( const float &avgPower ){
    this->avgPower = avgPower;
}

/*********************************************************************
* Method Name: setAvgVoltage
*
* Description:
*   Average voltage setter
*
*********************************************************************/
void DataRecord::setAvgVoltage( const float &avgVoltage ){
    this->avgVoltage = avgVoltage;
}

/*********************************************************************
* Method Name: setAvgCurrent
*
* Description:
*   Average current setter
*
*********************************************************************/
void DataRecord::setAvgCurrent( const float &avgCurrent ){
    this->avgCurrent = avgCurrent;
}

/*********************************************************************
* Method Name: isValid
*
* Description:
*   Is this record valid?
*
*********************************************************************/
bool DataRecord::isValid() const{
    return valid;
}

/*********************************************************************
* Method Name: displayData
*
* Description:
*	Displays record data on console
*
*********************************************************************/
void DataRecord::displayData(){
    std::cout << timeString << ", ";
    std::cout << power << ", ";
    std::cout << voltage << ", ";
    std::cout << current << ", ";
    if( avgProcessed ){
        std::cout << avgPower << ", ";
        std::cout << avgVoltage << ", ";
        std::cout << avgCurrent << std::endl;
    }
    else{
        std::cout << ", , " << std::endl;
    }
}

/*********************************************************************
* Method Name: dataToString
*
* Description:
*   Converst record data to a string
*
*********************************************************************/
std::string DataRecord::dataToString(){
    std::stringstream dataToStringStream;

    if( timeGapFlag ){
        dataToStringStream << "Anomaly - time gap detected" << std::endl;
    }

    dataToStringStream << timeString << ", ";
    dataToStringStream << power << ", ";
    dataToStringStream << voltage << ", ";
    dataToStringStream << current << ", ";
    if( avgProcessed ){
        dataToStringStream << avgPower << ", ";
        dataToStringStream << avgVoltage << ", ";
        dataToStringStream << avgCurrent << std::endl;
    }
    else{
        dataToStringStream << ", , " << std::endl;
    }

    if( !valid ){
        for( auto it = anomalyVector.begin(); it != anomalyVector.end(); it++)
        dataToStringStream << "Anomaly - " << ANOMALY_STR_ARRAY[*it] << std::endl;
    }

    return dataToStringStream.str();
}

/*********************************************************************
* Method Name: setTime
*
* Description:
*   Set time to its different representations from a timestamp string
*
*********************************************************************/
void DataRecord::setTime( const std::string &timeString ){
    /***********************************************************
    * Local constants
    ***********************************************************/
    const std::string MILLISEC_DELMITER = ".";
    const std::string TIMESTAMP_FORMAT = "%F %H:%M:%S";
    /***********************************************************
    * Store time in its string representation
    ***********************************************************/
    this->timeString = timeString;

    /***********************************************************
    * Parse timestamp up to seconds.
    * Parse milliseconds
    ***********************************************************/
    size_t pos = this->timeString.find( MILLISEC_DELMITER );
    std::string timeUpToSecondsStr = this->timeString.substr( 0, pos );
    std::string recordMillisecondsStr = this->timeString.substr( pos + MILLISEC_DELMITER.length(), timeString.length());

    /***********************************************************
    * Convert time to integer values so that we can compare
    * later.
    ***********************************************************/
    struct tm tm_time;
    memset( &tm_time, 0 , sizeof(tm_time));
    strptime( timeUpToSecondsStr.c_str(), TIMESTAMP_FORMAT.c_str(), &tm_time);
    epochInSeconds = mktime( &tm_time );
    epochInMilliSeconds = static_cast<unsigned long long>(epochInSeconds) * 1000 + stoull(recordMillisecondsStr);
}

/*********************************************************************
* Method Name: getEpochInMilliSeconds
*
* Description:
*	Epoch in MilliSeconds getter
*
*********************************************************************/
unsigned long long DataRecord::getEpochInMilliSeconds(){
    return epochInMilliSeconds;
}

/*********************************************************************
* Method Name: setTimeGapFlag
*
* Description:
*   Sets Time Gap Anomality Flag to true.
*
*********************************************************************/
void DataRecord::setTimeGapFlag(){
    timeGapFlag = true;
}

