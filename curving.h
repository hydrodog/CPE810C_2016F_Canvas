#ifndef CANVASASSIGNMENT
#define CANVASASSIGNMENT

class curving {
private:
	double curved_grades[] = { 0 };		// array of curved grades
public:
	curving();
	void lin_curve();		// perform a linear curve on grades
	void root_curve();		// perform 10*sqrt(g) curve on grades
	double return_curve();	// returns curved array of grades
	double curve_mean();	// return mean of curved grades
	double curve_median();	// return median of curved grades
	double curve_variance();	// return variance of curved grades
};
#endif // CANVASASSIGNMENT