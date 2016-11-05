/**
 * Library to calculate the average and standard deviation of a 
 * reading iteratively: without storing the whole data set.
 * 
 * Stores: 
 * double average
 * double variance
 * int numberOfReadings
 * double min
 * double max
 **/
 
 /* 
Copyright (c) 2016 Edoardo Pasca

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#include "AvgStd.h"
#include <math.h>


AvgStd::AvgStd(){
    AvgStd::reset();
}

/**
 * Adds a reading only if it is within boundaries (not rejected).
 */
void AvgStd::checkAndAddReading(float val){

    if (N < 2)
        AvgStd::addReading(val);
    else {
        if (r_sigma == -1 || (int) AvgStd::getVariance() == 0)
            AvgStd::addReading(val);
        else {
            if (fabs(avg - val) <= (r_sigma * sqrt(var)) )
                AvgStd::addReading(val);
        }
    }

}

void AvgStd::addReading(float val){
        
    if (N == 0) {
        avg = val;
        min = val;
        max = val;
    } else if (N == 1) {
        //set min/max
        max = val > max? val : max;
        min = val < min? val : min;        
            
        
        float thisavg = (avg + val)/2;
        // initial value is in avg
        var = (avg - thisavg)*(avg-thisavg) + (val - thisavg) * (val-thisavg);
        skewness = var * (avg - thisavg);
        kurtosis = var * var;
        avg = thisavg;
    } else {
        // set min/max
        max = val > max? val : max;
        min = val < min? val : min;        
        
        float M = (float)N;

        // b-factor =(<v>_N + v_(N+1)) / (N+1)
        float b = (val -avg) / (M+1);

        kurtosis = kurtosis + (M *(b*b*b*b) * (1+M*M*M))- (4* b * skewness) + (6 * b *b * var * (M-1));

        skewness = skewness + (M * b*b*b *(M-1)*(M+1)) - (3 * b * var * (M-1));

        //var = var * ((M-1)/M) + ((val - avg)*(val - avg)/(M+1)) ;
        var = var * ((M-1)/M) + (b * b * (M+1));
        
        avg = avg * (M/(M+1)) + val / (M+1);
    }
    N++;
}



void AvgStd::reset(){
    N = 0;
    avg = 0;
    var = 0;
    min = 0;
    max = 0;
    r_sigma = -1;
    skewness = 0;
    kurtosis = 0;
}

float AvgStd::getMean(){return avg;}
float AvgStd::getStd() {
    float ret = 0;
    if (N>1)
        ret = sqrt(var);
    return ret;
}
float AvgStd::getVariance() {return var;}
unsigned int AvgStd::getN(){return N;}
float AvgStd::getMin() {return min;}
float AvgStd::getMax() {return max;}

void AvgStd::setRejectionSigma(float sigmas){
    r_sigma = sigmas;
};

float AvgStd::getSkewness(){
	return skewness/pow(var,1.5);
};
float AvgStd::getKurtosis(){
	return kurtosis/pow(var,2);
};


