CS3203 Static Program Analyzer (SPA)

The SPA Program is an interactive tool that automatically answers queries about programs give an input of a source program, followed by specific queries.
This SPA Program is functional for a source program written in a programming language SIMPLE.

In order to test this SPA Program, an automated Tester "AutoTester" is provided. 
To test the SPA program using the Autotester:
1. Open StartupSPASolution.sln in Visual Studio 2019.
2. Right Click on the project AutoTester and Select Build
3. Run the AutoTester from the command prompt by navigating to the AutoTester.exe file and input 3 arguments:
    - Name of file containing the SIMPLE source program
    - Name of file containing queries
    - Output file to store testing results.
For example, this is a possible input:
> AutoTester ..\Tests\Sample_source.txt ..\Tests\Sample_queries.txt ..\Tests\out.xml
4. Finally, you can view the results of the test by opening your output file (in .xml) in NotePad or Mozilla Firefox.

To turn off optimisations for the code, navigate to the <<Team22\Code22\AutoTester\source\TestWrapper.cpp>> file.
and change the value of <<QueryEvaluator::getInstance().isOptimize>> to "false
on line 39

It is possible to switch on the extraction of Extension-related features, by changing the value of 
<<bool isExtension>> to "true"
on line 23
in the <<Team22\Code22\AutoTester\source\TestWrapper.cpp>> file.