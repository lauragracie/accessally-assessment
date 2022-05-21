#include <iostream>
#include <cmath>

using namespace std;

#define MIN_IN_12_HOURS 720

int count_num_sequences(int total_min);
int get_first_digit(int n);


int main() {


    int total_min;
    cin >> total_min;

    int full_cycles = total_min / MIN_IN_12_HOURS;
    int last_cycle = total_min % MIN_IN_12_HOURS;


    // There are the same number of algebraic sequences in every 12 hour sequence, so we can just count it once

    if (full_cycles > 0) {
        cout << full_cycles * count_num_sequences(MIN_IN_12_HOURS - 1) + count_num_sequences(last_cycle);
    } else {
        cout << count_num_sequences(last_cycle);
    }

}

int count_num_sequences(int total_min) {
    int current_hour = 12;

    //For end_time, 12 o'clock becomes 00. Ex: 34 minutes -> 034
    int end_hours = (total_min / 60) % 12;
    int end_time = end_hours * 100 + total_min % 60;

    int num_sequences = 0;
    int num_digits = 0;
    int seq_time = 0;
    int first_digit = 0;
    int next_digit = 0;

    bool invalid_num = false;

    while(1){


        first_digit = get_first_digit(current_hour);

        // Lowest possible diff is -4 (9:51) and highest is 4 (1:59)
        for (int diff = -4; diff <= 4; ++diff) {

            if (current_hour >= 10) {
                num_digits = 4;
            } else {
                num_digits = 3;
            }

            if (current_hour >= 10 && (current_hour % 10 != first_digit + diff)) {
                //Exit loop if the hour digits don't work with diff. Ex: current_hour = 12 and diff != 1
                continue;
            }

            for(int i = 0; i < num_digits; ++i) {
                next_digit = first_digit + (i*diff);

                //Add digit to the sequence if it is in the proper range
                if (0 <= next_digit && next_digit <= 9) {
                    seq_time += next_digit * pow(10, num_digits - i - 1);
                } else {
                    invalid_num = true;
                    break;
                }
            }

            if (!invalid_num) {
                if ((seq_time % 1200) > end_time) {
                    break;
                } else if ((seq_time / 100 == current_hour) && (seq_time % 100 < 60)) {
                    ++num_sequences;
                }
            }

            invalid_num = false;
            seq_time = 0;

        }

        if (current_hour % 12 == end_hours) {
            break;
        } else {
            current_hour = (current_hour + 1) % 12;
        }

    }

    return num_sequences;

}


// Returns first digit of a 1 or 2 digit number
int get_first_digit(int n) {

    if (n >= 10){
        return n / 10;
    } else {
        return n % 10;
    }
}

