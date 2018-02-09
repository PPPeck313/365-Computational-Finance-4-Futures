//Preston Peck
//CS 365
//October 14, 2017
//HW 4

#include <iostream>
#include <cmath>
using namespace std;

void ForwardNoDividends(double S0, double r, int t0, double T, double& F);
void ForwardContinuousDividends(double S0, double r, double q, int t0, double T, double& F);
void MarkToMarket(double Ss[], double Fs[], int t0, int T);//T in days

int main() {
    //4.1 Forward Price
    //stock, rate, time end, futures
    double S0, r, T, F = 0.0;
    int t0 = 0;

    S0 = 100.5;
    cout << "Stock Price: $" << S0 << endl;
    r = 5.5;
    cout << "Interest Rate: " << r << endl;
    t0 = 0;
    cout << "Start Year: " << t0 << endl;
    T = .75;
    cout << "End Year: " << T << endl << endl;
    F = 0;

    ForwardNoDividends(S0, r, t0, T, F);
    cout << endl;
    
    S0 = 95.5;
    cout << "Stock Price: $" << S0 << endl;
    r = 5.1;
    cout << "Interest Rate: " << r << endl;
    q = 1.1;
    cout << "Yield Rate: " << q << endl;
    cout << "Start Year: " << t0 << endl;
    T = .65;
    cout << "End Year: " << T << endl << endl;

    ForwardContinuousDividends(S0, r, q, t0, T, F);
    cout << endl;

    //4.2 Forwards: arbitrage
    S0 = 100.0;    
    cout << "Stock Price: $" << S0 << endl;
    r = 5;
    cout << "Interest Rate: " << r << endl;
    cout << "Start Year: " << t0 << endl;
    T = 1.0;
    cout << "End Year: " << T << endl << endl;

    ForwardNoDividends(S0, r, t0, T, F);
    cout << endl;

    //We project a forward value of 105.127 = F
    cout << "Case 1: Net $" << 105.0 - F << endl;
    cout << "Case 2: Net $" << 106.0 - F << endl << endl;
    //In case 1 we have an amount < F at T, so we short sell today and buy it back at the lower price later
    //In case 2 we have an amount > F at T, so we buy today and sell it at the higher price later


    //4.3 Futures: mark to market
        //4.3.1 Random walk 1
        S =  100.0;
        F = 105.5;
        T = 5;
        double Ss1[] = {S, 99.5, 101.3, 101.3, 100.2, 99.3};
        double Fs1[] = {F, 103.3, 104.1, 102.1, 101.3, 99.3};

        cout << "Walk 1" << endl;
        MarkToMarket(Ss1, Fs1, t0, T);
        //What is the TOTAL amount of money the investor pays at T: $105.5

        //4.3.2 Random walk 2
        double Ss2[] = {S, 110.9, 103.8, 106.1, 107.5, 108.3};
        double Fs2[] = {F, 106.3, 108.7, 109.2, 108.3, 108.3};
        ////What is the TOTAL amount of money the investor pays at T: $105.5

        cout << "Walk 2" << endl;
        MarkToMarket(Ss2, Fs2, t0, T);

        //4.3.3 Summary
        //Does the random walk of the stock prices affect the total amount paid by the investor?

        //Given the future prices for each of the mark to market days, the random walk of 
        //stock prices is NOT a factor in the total amount the investor pays, EXCEPT for
        //the stock price on the termination day because the future price converges to it.
        //Future turns to present, and so you need a point of comparison in that day's market
        //to judge how well your market speculation paid off.

        //4.3.5 Random walk 3
        double Ss3[] = {S, 99.5, 101.3, 101.3, 100.1, 102.3};
        double Fs3[] = {F, 106.3, 105.1, 105.8, 104.2, 102.3};

        cout << "Walk 3" << endl;
        MarkToMarket(Ss3, Fs3, t0, T);
        //The investor sells the futures contract on DAY 2: -$0.4
        //The investor sells the futures contract on DAY 3: $0.3
        
        double Ss4[] = {S, 99.7, 101.2, 101.5, 102.8, 102.3};
        double Fs4[] = {F, 106.3, 105.1, 105.8, 104.2, 102.3};

        cout << "Walk 4" << endl;
        MarkToMarket(Ss4, Fs4, t0, T);
        //The investor sells the futures contract on DAY 2: -$0.4
        //The investor sells the futures contract on DAY 3: $0.3

        //4.3.7 Summary
        //Does the random walk of the stock prices affect the profit/loss of the investor?

        //The tables are exactly the same except for stock prices, so change did NOT affect anything else
}

void ForwardNoDividends(double S0, double r, int t0, double T, double& F) {
    double rDecimal = r * .01;
    F = S0 * exp(rDecimal * (T - t0));

    cout << "Forward Price w/o Dividends: $" << F << endl << endl;
}

void ForwardContinuousDividends(double S0, double r, double q, int t0, double T, double& F) {
    double rDecimal = r * .01;
    double qDecimal = q * .01;
    F = S0 * exp((rDecimal - qDecimal) * (T - t0));

    cout << "Forward Price w/ Continuous Dividends: $" << F << endl << endl;
}

void MarkToMarket(double Ss[], double Fs[], int t0, int T) {
    if (t0 <= T) {
        double net = 0;

        for (int i = t0; i <= T; i++) {
            cout << "Day " << i << '\t' 
                 << "Stock Price: $" << Ss[i] << '\t' 
                 << "Future Price: $" << Fs[i] << '\t';

            if (i > 0) {
                if (Fs[i] > Fs[i-1]) {
                    double gain = Fs[i] - Fs[i-1];
                    cout << "Money Received: $" << gain;
                    net += gain;
                    cout << '\t' << '\t' << '\t' << '\t' << "Net: $" << net;
                }

                if (Fs[i] < Fs[i-1]) {
                    double loss = Fs[i-1] - Fs[i];
                    cout << '\t' << '\t' << '\t' << "Money Paid: $" << loss << "  ";
                    net -= loss;

                    cout << '\t' << "Net: $" << net;
                }
            }

            cout << endl;
        }
    }

    cout << endl;
}
