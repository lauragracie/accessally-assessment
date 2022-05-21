#include <iostream>
#include <algorithm>

#define O_NEGATIVE 0
#define O_POSITIVE 1
#define A_NEGATIVE 2
#define A_POSITIVE 3
#define B_NEGATIVE 4
#define B_POSITIVE 5
#define AB_NEGATIVE 6
#define AB_POSITIVE 7

using namespace std;

int useBlood(int blood_type, int patient_type, int *supply, int *patients);
int get_max_blood(int patient_type, int* valid_types, int num_types, int *supply, int *patients);


// Lists of valid blood types for each patient type in order of preference
int o_negative_valid[1] = {O_NEGATIVE};
int o_positive_valid[2] = {O_POSITIVE, O_NEGATIVE};

int a_negative_valid[2] = {A_NEGATIVE, O_NEGATIVE};
int a_positive_valid[4] = {A_POSITIVE, A_NEGATIVE, O_POSITIVE, O_NEGATIVE};

int b_negative_valid[2] = {B_NEGATIVE, O_NEGATIVE};
int b_positive_valid[4] = {B_POSITIVE, B_NEGATIVE, O_POSITIVE, O_NEGATIVE};

int ab_negative_valid[4] = {AB_NEGATIVE, B_NEGATIVE, A_NEGATIVE, O_NEGATIVE};
int ab_positive_valid[8] = {AB_POSITIVE, AB_NEGATIVE, B_POSITIVE, B_NEGATIVE, A_POSITIVE, A_NEGATIVE, O_POSITIVE, O_NEGATIVE};

int main(){

    int blood_supply[8] = {0};
    int patients[8] = {0};

    for (int i = 0; i < 8; ++i) {
        cin >> blood_supply[i];
    }
    for (int i = 0; i < 8; ++i) {
        cin >> patients[i];
    }

    int total = 0;

    total += get_max_blood(O_NEGATIVE, o_negative_valid, 1, blood_supply, patients);
    total += get_max_blood(O_POSITIVE, o_positive_valid, 2, blood_supply, patients);

    total += get_max_blood(A_NEGATIVE, a_negative_valid, 2, blood_supply, patients);
    total += get_max_blood(A_POSITIVE, a_positive_valid, 4, blood_supply, patients);

    total += get_max_blood(B_NEGATIVE, b_negative_valid, 2, blood_supply, patients);
    total += get_max_blood(B_POSITIVE, b_positive_valid, 4, blood_supply, patients);

    total += get_max_blood(AB_NEGATIVE, ab_negative_valid, 4, blood_supply, patients);
    total += get_max_blood(AB_POSITIVE, ab_positive_valid, 8, blood_supply, patients);

    cout << total;
}


// Returns the max number of units that can be used for patient-type given their list of valid_types. Modifies supply and patients
int get_max_blood(int patient_type, int* valid_types, int num_types, int *supply, int *patients) {

    int total = 0;
    for(int i = 0; i < num_types; ++i) {
        total += useBlood(valid_types[i], patient_type, supply, patients);
    }
    return total;
}



// Returns the max number of units of blood_type that can be used for patient_type. Modifies supply and patients
int useBlood(int blood_type, int patient_type, int *supply, int *patients){

    int used_units = min(supply[blood_type], patients[patient_type]);
    supply[blood_type] -= used_units;
    patients[patient_type] -= used_units;
    return used_units;

}

