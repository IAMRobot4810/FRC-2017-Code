//Source file for Scaler.h
#include <util/Scaler.h>

Scaler::Scaler(){ //Constructor

}

Scaler::~Scaler(){ //Destructor

}

//If you don't know the rest, git gud at math bruh

double Scaler::ExponentialScale(double input, double minIn, double maxIn, double minOut, double maxOut, double exponent){
	double expOut = 0;
	return expOut;
}

double Scaler::LinearScale(double input, double m, double b, bool negativeOpposite){
	double linOut;
	if(negativeOpposite == true){
		if(input > 0){
			linOut = (m*input) + b;
		}
		else if(input < 0){
			linOut = (m*input) - b;
		}
		else{
			linOut = 0;
		}
	}
	else{
		linOut = (m*input) + b;
	}
	return linOut;
}

double Scaler::autoLinearScale(double in, double minIn, double maxIn, double minOut, double maxOut){
	double linOut;
	double m;
	double b;
	m = (maxOut-minOut)/(maxIn-minIn);
	b = minOut-(m*minIn);
	linOut = (m*in) + b;
	return linOut;
}

double Scaler::exponentialScale(double in, int exp, double multiple, double intercept, bool negativesOpposite){
	double expOut;
	if(negativesOpposite == true){
		if(exp % 2 == 0){
			if(in > 0){
				expOut = (multiple*(pow(in, exp))) + intercept;
			}
			else if(in < 0){
				expOut = (multiple*(pow(in, exp))) - intercept;
			}
			else{
				expOut = 0;
			}
		}
		else{
			if(in > 0){
				expOut = (multiple*(pow(in, exp))) + intercept;
			}
			else if(in < 0){
				expOut = -((multiple*(pow(in, exp))) + intercept);
			}
			else{
				expOut = 0;
			}
		}
	}
	else{
		expOut = (multiple*(pow(in, exp))) + intercept;
	}
	return expOut;
}

double Scaler::autoExponentialScale(double in, double minIn, double maxIn, double minOut, double maxOut, double power){
	double out;
	out = 0.0;
	return out;
}
