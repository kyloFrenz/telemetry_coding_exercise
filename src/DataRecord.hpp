//
// Created by fernando on 6/18/18.
//

#ifndef TELEMETRY_PRACTICE_DATARECORD_HPP
#define TELEMETRY_PRACTICE_DATARECORD_HPP

/***********************************************************
* Includes
***********************************************************/
#include <string>
#include <vector>

class DataRecord{
public:
    /***********************************************************
    * DataRecord anomaly enum
    ***********************************************************/
    enum recordAnomaly{
        NONE = 0,
        INVALID_POWER,
        INVALID_VOLTAGE,
        INVALID_CURRENT,

        RECORD_ANOMALY_CNT
    };

    /***********************************************************
    * Array of anomaly strings.
    ***********************************************************/
    std::string ANOMALY_STR_ARRAY[RECORD_ANOMALY_CNT] = { "None", "Kw < 0.0", "V outside range 480V +/- 5", "I < 0.0" };

    /***********************************************************
    * Class Constants
    ***********************************************************/
    static const float MINIMUM_POWER_MEASUREMENT;
    static const float MAX_VOLTAGE_MEASUREMENT;
    static const float MIN_VOLTAGE_MEASUREMENT;
    static const float MIN_CURRENT_MEASUREMENT;

    /***********************************************************
    * Setters
    ***********************************************************/
    void setPower( const float &power );
    void setVoltage( const float &voltage );
    void setCurrent( const float &current );
    void setAnomaly( const recordAnomaly &anomaly );
    void setToInvalid();
    void setAvgProcessedFlag();
    void setAvgPower( const float &avgPower );
    void setAvgVoltage( const float &avgVoltage );
    void setAvgCurrent( const float &avgCurrent );
    void setTime( const std::string &timeString );
    void setTimeGapFlag();

    /***********************************************************
    * Getters
    ***********************************************************/
    std::string getTimeStamp() const;
    unsigned long long getEpochInMilliSeconds();
    float getPower() const;
    float getVoltage() const;
    float getCurrent() const;
    bool isValid() const;

    /***********************************************************
    * Public "interface"
    ***********************************************************/
    void displayData();
    std::string dataToString();

private:
    /***********************************************************
    * Private members
    ***********************************************************/
    std::string timeString;
    time_t epochInSeconds = 0;
    unsigned long long epochInMilliSeconds = 0;
    float power = 0;
    float avgPower = 0;
    float voltage = 0;
    float avgVoltage = 0;
    float current = 0;
    float avgCurrent = 0;
    bool valid = true;
    bool avgProcessed = false;
    bool timeGapFlag = false;
    std::vector<recordAnomaly> anomalyVector;
};

#endif //TELEMETRY_PRACTICE_DATARECORD_HPP
