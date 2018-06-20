# telemetry_coding_exercise

Object Oriented Design:
-Four main classes to process telemetry data:
*DataRecord: This is a representation of the pre-processed data, post-processed data and additional data such as anomalies found in the record, etc.
*DataReader: Opens a filestream and provides an API to read each line to emulate a real-world scenario where we have a continous live data stream. Each time we read a line, this class parses the telemetry date and creates an a DataRecord Object.
*RecordWindow: This is a data structure to store N number of records so that we can calculate the average of the different telemetry measurements in the set of records contained in such window. As described by the requirements, this is a sliding window and it's a derived class of the dequeue container.
*Logger: Opens an file output stream and allows the user to write a log of the data contained in each record.

Here is a description of the basic dataflow:
1.- Read the next telemetry record from the input file. [DataReader]
2.- Parse data and generate a Data Record (check for anomalies and formats data in a way that can later be processed). [DataReader & DataRecord]
3.- Add Data Record to recordwindow. [DataRecord & RecordWindow]
4.- Calculate average of telemetry measurements when the window is full iff there is no timegap between the records in the window. [DataRecord & RecordWindow]
5.- Log DataRecord after it has been processed. [DataRecord and Logger]

Implementation:
All implementation is contained in the /src directory.
Input data is contained in the /data directory.
Log file name: output_data.log (located at the root of the project).

Testing of requirements:
*Read telemetry in from the attached data file - Write Unit test for reader class. We can mock the getLine() function to stimulate the reader class with a set of known data. We can then write asserts that check that the DataRecord members match the mocked data. We can use the getter functions from the DataRecord to retrieve the private members in the DataRecord class. This method could also be utilized to test the detection of the anomalies since these are detected while we are populating the dataRecord object.

*To check that the set of inputs generate the right outputs I would run a series of automated system level tests where we give the Application a set of known data against its corresponding set of known outputs. The automated tests would include:
**Input data outside the normal boundaries so that we can detect all of the combinations of anomalies, timegaps, averages that were not calculated, etc.
**Input data inside the normal boundaries to check that we are calculating the measurement averages.

Miscellanious:
*Run a profiler to understand if we can make performance improvements.
*Run a memcheck utility such as valgrind to ensure we are normal memory utilization is within requireents and to verify we don't have memory leaks.
*I would run the above tests with different anomaly threshold values and windosize values to verify the logic still works outside of the use case specified in the provided spec. This would allow us to run in different environments or could provide some insight as to how well this app would scale with different windowsizes, max timegap values, etc.

