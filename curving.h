#ifndef CANVASASSIGNMENT
#define CANVASASSIGNMENT
/*
   @author:
   @modified:Hansheng Tian
   The objective of this group is to take input data,curve the date for the user, 
   ask for confirmation, then push the changes back into Canvas
*/

/*
 This class is used to take grades and curve them based on the needs of the user
 */
class curving {
private:
	double m_curvedGrades[];
	double m_originalGrades[];
	bool m_confirm;
public:
	Curving();
	void linCurve(int curve,int length);		// perform a linear curve on grades
	void rootCurve(int length);		// perform 10*sqrt(g) curve on grades
	double returnCurve();	// returns curved array of grades
	void acceptChanges();
};
#endif // CANVASASSIGNMENT
