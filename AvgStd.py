class AvgStd:
    def __init__(self):
        self.reset()
        
    def reset(self):
        self.N = 0
        self.avg = 0
        self.var = 0
        self.min = 0
        self.max = 0
        self.r_sigma = -1
        self.skewness = 0
        self.kurtosis = 0
        
    def add_reading(self, val):
        if (self.N == 0):
            self.avg = val;
            self.min = val;
            self.max = val;
        elif (N == 1):
            # set min/max
            self.max = val if val > self.max else self.max
            self.min = val if val < self.min else self.min        
                
            
            thisavg = (self.avg + val)/2;
            # initial value is in avg
            self.var = (self.avg - thisavg)*(self.avg - thisavg) + (val - self.thisavg) * (val - self.thisavg);
            self.skewness = self.var * (self.avg - thisavg);
            self.kurtosis = self.var * self.var;
            self.avg = thisavg;
        else:
            # set min/max
            self.max = val if val > self.max else self.max;
            self.min = val if val < self.min else self.min;        
            
            M = self.N
    
            # b-factor =(<v>_N + v_(N+1)) / (N+1)
            b = (val - self.avg) / (M+1);
    
            self.kurtosis = self.kurtosis + (M *(b*b*b*b) * (1+M*M*M))- (4* b * self.skewness) + (6 * b *b * self.var * (M-1));
    
            self.skewness = self.skewness + (M * b*b*b *(M-1)*(M+1)) - (3 * b * self.var * (M-1));
    
            # var = var * ((M-1)/M) + ((val - avg)*(val - avg)/(M+1)) ;
            self.var = self.var * ((M-1)/M) + (b * b * (M+1));
            
            self.avg = self.avg * (M/(M+1)) + val / (M+1);
        
        self.N += 1
