#include <stdio.h>
#include <math.h>

//1. This is the math engine for the whole program
double calculate_hypergeometric(int x, int N, int K, int n) {
    if (x < 0 || N < 0 || K < 0 || n < 0 || K > N || n > N || x > K || x > n) {
        return 0.0;
    }
    double lnum = lgamma(K + 1) - (lgamma(x + 1) + lgamma(K - x + 1)) +
                  lgamma(N - K + 1) - (lgamma(n - x + 1) + lgamma(N - K - (n - x) + 1));
    double lden = lgamma(N + 1) - (lgamma(n + 1) + lgamma(N - n + 1));
    return exp(lnum - lden);
}


int main() {
    int N, K, n, x;
    char repeat;

    printf(" Deck Probability & Risk Calculator \n");

    // 2. Generate user input for the deck size, target cards, number of draws, and successes
    do {
        printf("\nTotal cards in deck : ");
        scanf("%d", &N);
        printf("Total target cards : ");
        scanf("%d", &K);
        printf("Cards to draw : ");
        scanf("%d", &n);
        printf("Desired successes : ");
        scanf("%d", &x);

        char mode;
        printf("Calculate for exactly '%d' or at least '%d'? (e/a): ", x, x);
        scanf(" %c", &mode);

        double final_p = 0.0;

        // 3. The actual calculation's are performed
        if (mode == 'a' || mode == 'A') {
            for (int i = x; i <= n && i <= K; i++) {
                final_p += calculate_hypergeometric(i, N, K, n);
            }
            printf("\nProbability of AT LEAST %d targets: %.4f%%\n", x, final_p * 100);
        } else {
            final_p = calculate_hypergeometric(x, N, K, n);
            printf("\nProbability of EXACTLY %d targets: %.4f%%\n", x, final_p * 100);
        }

        
        
        // 4.This is where expected value is calculated
        if (final_p > 0) {
            double odds = 1.0 / final_p;
            printf("Odds: 1 in %.2f (or %.2f to 1 against)\n", odds, odds - 1);
        }

        char calc_ev;
        printf("\nCalculate Expected Value (EV) for this draw? (y/n): ");
        scanf(" %c", &calc_ev);

        if (calc_ev == 'y' || calc_ev == 'Y') {
            double wgr, pay, ev; 
            
            printf("Enter wager amount ($): ");
            scanf("%lf", &wgr);
            printf("Enter potential payout profit ($): ");
            scanf("%lf", &pay);
            
            ev = (final_p * pay) - ((1.0 - final_p) * wgr);
            
            printf("\n Risk Assessment \n");
            if (ev > 0) {
                printf("Expected Value: +$%.2f [+EV Profitable]\n", ev);
            } else if (ev < 0) {
                printf("Expected Value: -$%.2f [-EV Unprofitable]\n", ev * -1);
            } else {
                printf("Expected Value: $0.00 [Break-Even]\n");
            }
        }
        
        
        

        printf("\nPerform another calculation? (y/n): ");
        scanf(" %c", &repeat);

    } while (repeat == 'y' || repeat == 'Y');

    printf("Exiting. Thank you.\n");
    return 0;
}