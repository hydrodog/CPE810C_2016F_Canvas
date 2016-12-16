public class Polynomials
{
	// Data Fields

	private int degree;

	private double coefficients[];

	// Constructor

	public Polynomials(int n, double a[])
	{
		if (n < 0)
		{
			System.out.println("The degree of the polynomial cannot be negative.");
			System.exit(1);
		}

		//check length of array - should be same as degree
		if (n != a.length - 1)
		{
			System.out.println("The degree of the polynomial must match the length of the array of coefficients.");
			System.exit(1);
		}

		degree = n;
		coefficients = a;
	}

	// Methods

	public void setDegree(int m)
	{
		if (m < 0)
		{
			System.out.println("The degree of the polynomial cannot be negative.");
			System.exit(1);
		}

		degree = m;
	}

	public void setCoefficients(double ai[])
	{
		if (this.getDegree() != ai.length - 1)
		{
			System.out.println("The degree of the polynomial must match the length of the array of coefficients.");
			System.exit(1);
		}

		//ai should be an array
		coefficients = ai;
	}

	// Calculates P(x) given x
	public double compute(double x)
	{
		int arraylength = this.coefficients.length;
		double total = 0;
		for (int i = 0; i < arraylength; i++)
			total += this.coefficients[i]*(Math.pow(x,i));
		return total;
	}

	// Add 2 Polynomials
	public void addPolynomials(Polynomials other)
	{
		double newCoeffs[] = new double[Math.max(other.getDegree() + 1, this.getDegree() + 1)];
		
		//System.out.println("length of newCoeffs: " + newCoeffs.length);

		for (int i = 0; i <= Math.min(other.getDegree(), this.getDegree()); i++)
		{
			//System.out.println("other: " + other.getValue(i));
			//System.out.println("this: " + this.getValue(i));
			//System.out.println("i: " + i);
			newCoeffs[i] = other.getValue(i) + this.getValue(i);
		}

		if (this.getDegree() > other.getDegree())
		{
			for (int i = other.getDegree() + 1; i <= this.getDegree(); i++)
			{
				newCoeffs[i] = this.getValue(i);
			}
		}

		else
		{
			for (int i = this.getDegree() + 1; i <= other.getDegree(); i++)
			{
				//System.out.println("i: " + i);
				newCoeffs[i] = other.getValue(i);
			}
		}

		this.setDegree(Math.max(other.getDegree(), this.getDegree()));
		this.setCoefficients(newCoeffs);
	}

	public int getDegree()
	{
		return this.degree;
	}

	public double[] getCoefficients()
	{
		return this.coefficients;
	}

	//gets value at index in array
	public double getValue(int index)
	{
		return this.coefficients[index];
	}


	public String toString()
	{
		String print = "P(X) = ", current;

		for (int i = 0; i < this.getDegree(); i++)
		{
			//System.out.println("looping through the loop");
			if (this.getValue(i) != 0)
			{
				if (i == 0)
				{
					current = this.getValue(i) + " + ";
				}

				else
				{
					current = this.getValue(i) + "x^" + i + " + ";
				}
				//System.out.println("current: " + current);
				print += current;
				//System.out.println("print: " + print);
			}
		}

		current = this.getValue(this.getDegree()) + "x^" + this.getDegree(); 
		print += current;
		return print;
	}


	public static void main(String[] arg)
	{
		double[] a = {3.7, 5, 7, 1};
		Polynomials first = new Polynomials(3, a);
		System.out.println("First Polynomial: " + first.toString());

		double[] b = {3, 0, 4.2};
		Polynomials second = new Polynomials(2, b);
		System.out.println("Second Polynomial: " + second.toString());

		//uncomment code below when testing each part individually

		//first.addPolynomials(first);
		//System.out.println("First Polynomial + First Polynomial: " + first.toString());

		//second.addPolynomials(first);
		//System.out.println("Second Polynomial + First Polynomial: " + second.toString());

		//second.addPolynomials(second);
		//System.out.println("Second Polynomial + Second Polynomial: " + second.toString());

		//first.addPolynomials(second);
		//System.out.println("First Polynomial + Second Polynomial: " + first.toString());

		//check compute
		double[] c = {3, -2, 1};
		Polynomials third = new Polynomials(2, c);
		System.out.println(third.toString());
		System.out.println("P(3) = " + third.compute(3));
	}
}
	
