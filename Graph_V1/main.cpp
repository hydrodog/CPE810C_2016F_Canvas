#include <iostream>
#include <iomanip>
using namespace std;

void arraySort(double scores[], int numScores);


void arraySort(double scores[], int numScores)

{
 bool exchanges;
 do
 {
  exchanges = false;                                                           // assume no exchanges
  for(int i = 0; i < numScores - 1; i++){
   if(scores[i] > scores[i + 1]){
    double temp = scores[i];
    scores[i] = scores[i+1];
    scores[i+1] = temp;
    exchanges = true;                                                               // after exchange, must look again
   }
  }
 }
 while(exchanges);
}


int main (void)
{
 double *scores,                                                          //To dynamically allocate an array
 total = 0.0,                                                            // Accumulator
 mean;                                                                  // To hold average scores
 int numScores,                                                        //To hold the number of test scores
 count;                                                               //Counter variable


 cout << "How many test scores would you like to enter? ";
 cin >> numScores;



 scores = new double[numScores];                                         //Dynamically allocate an array large enough to hold that many test scores


 cout << "Enter the test scores below.\n";

 for (count = 0; count < numScores; count++)
 {
  cout << "Test Score " << (count + 1) << ": ";
  cin >> scores[count];
 }


 for (count = 0; count < numScores; count++)
 {
  total += scores[count];                         //Calculate the total of the scores
 }


 mean = total / numScores;                                               //Calculate the mean test score


 cout << fixed << showpoint << setprecision(2);
 cout << "Mean score is: " << mean << endl;


 arraySort(scores,numScores);

 for (count = 0; count < numScores; count++)
 {
  cout<<"score "<<(count+1)<<": "<<scores[count]<<endl;
 }


                                                                                //Free dynamically allocated memory
 delete [] scores;
 scores = 0;                                                                     //Make scores point to null.
 cin.ignore(INT_MAX, '\n');
 cin.ignore(INT_MAX, '\n');

 return 0;
}

