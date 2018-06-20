//
// Created by fernando on 6/18/18.
//

#include <iostream>
#include "RecordWindow.hpp"

/*********************************************************************
* Method Name: RecordWindow
*
* Description:
*	Constructor. Minimum window size must be 2 in order to be able
*	to calculate averages. Configurable to be any size.
*	In a real world scenario this would have to be limited for
*	performance and memory constraints/optimization.
*
*********************************************************************/
RecordWindow::RecordWindow( unsigned int maxWindowSize ){
    if( maxWindowSize < 2 ){
        this->maxWindowSize = 2;
    }
    else{
        this->maxWindowSize = maxWindowSize;
    }
}

/*********************************************************************
* Method Name: addRecord
*
* Description:
*	Adds record to window
*
*********************************************************************/
void RecordWindow::addRecord( DataRecord &record ){
    size_type windowSize = this->size();

    /***********************************************************
    * Check for TimeGap
    ***********************************************************/
    static bool timeGapDetected = false;
    static unsigned int dirtyWindowCount = 0;
    if( windowSize ){
        DataRecord previousRecordAdded = this->front();
        unsigned long long timeGap = record.getEpochInMilliSeconds() - previousRecordAdded.getEpochInMilliSeconds();
        if( timeGap > MAX_TIME_GAP_IN_MILLISECONDS ){
            record.setTimeGapFlag();
            timeGapDetected = true;
            dirtyWindowCount = 4;
        }
    }

    /***********************************************************
    * Push record to front of dequeue
    ***********************************************************/
    this->push_front( record );
    windowSize++;

    /***********************************************************
    * Keep window size at desired size.
    * Process
    ***********************************************************/
    bool windowFull = true;
    if( windowSize < maxWindowSize ){
        windowFull = false;
    }else if( windowSize > maxWindowSize ){
        this->pop_back();
    }

    /***********************************************************
    * Process window if window is fully populated and if
    * no time gap has been found in the last 5 seconds.
    ***********************************************************/
    if( windowFull ){
        if( !timeGapDetected ){
            record = this->process();
        }
        else if( !--dirtyWindowCount ){
            timeGapDetected = false;
        }
    }
}

/*********************************************************************
* Method Name: process
*
* Description:
*	This function processes the current data record window.
*
*********************************************************************/
DataRecord RecordWindow::process(){
    /***********************************************************
    * Calculate Average
    ***********************************************************/
    DataRecord processedRecord = calculateAverage();

    /***********************************************************
    * Other operations could be added here. That's why the
    * process function() was created instead of just calling
    * calculate average.
    ***********************************************************/
    // Stubbed - Other process operations added here if needed.

    return processedRecord;
}

/*********************************************************************
* Method Name: calculateAverage
*
* Description:
*	Calculates average measurements of records in window.
*
*********************************************************************/
DataRecord RecordWindow::calculateAverage(){
    /***********************************************************
    * Defining local variables
    ***********************************************************/
    float powerSum = 0;
    float voltageSum = 0;
    float currentSum = 0;

    /***********************************************************
    * Sum of window measurements
    ***********************************************************/
    auto it = this->rbegin();
    for( ; it != this->rend(); ++it ){
        powerSum += it->getPower();
        voltageSum += it->getVoltage();
        currentSum += it->getCurrent();
    }

    /***********************************************************
    * Calculate Average
    ***********************************************************/
    it--;
    it->setAvgPower( powerSum / maxWindowSize );
    it->setAvgVoltage( voltageSum / maxWindowSize );
    it->setAvgCurrent( currentSum / maxWindowSize );
    it->setAvgProcessedFlag();
    return *it;
}
