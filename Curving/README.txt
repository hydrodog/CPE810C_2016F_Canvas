IMPORTANT
--------------------------------------------------------------------------------------------------------------------------------------
To use this code:
  Import curving.cpp
  Must have a vector<double> to be passed into curving object
  Create a curving object with the vector<double>
  Run performCurve()
  Save new grades using returnCurve()
---------------------------------------------------------------------------------------------------------------------------------------


11/13/16
Contains working curving functions using pointers. Still needs updates to the "acceptChanges" function

12/11/16
curving.cpp, curving.h, and main.cpp contain code using vectors.
other files contain code for statistics of the data, functions need to be updated to work with vectors and merged into the files listed above

12/13/16
curving.cpp updated to have performCurve function, which is an all-encompassing function that can be called after the curving object is created. This function should provide all the functionality needed from curving. Up next we need to contact the automation group to figure out the format they will be pushing us data to make sure our programs are compatible

12/15/16
Finished collaborating with Automation group. The curving code is now implemented into the automation program to allow the user to curve an assigmnent once all the grades have been imputted
