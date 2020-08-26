#include <stdio.h>

int main(void) {
    int digits;

    printf("Enter digits\n");
    scanf("%d", &digits);

    // print 10-20
    if (digits >= 10 && digits < 20) {
        switch(digits) {
            case 10:
                printf("ten");
                break;
            case 11:
                printf("eleven");
                break;
            case 12:
                printf("twelve");
                break;
            case 13:
                printf("thirteen");
                break;
            case 14:
                printf("fourteen");
                break;
            case 15:
                printf("fifteen");
                break;
            case 16:
                printf("sixteen");
                break;
            case 17:
                printf("seventeen");
                break;
            case 18:
                printf("eighteen");
                break;
            case 19:
                printf("nineteen");
                break;
            default:
                printf("Unknown");
                break;
        }
        return 0;
    }

    // print 10s
    switch(digits/10) {
        case 2:
            printf("twenty");
            break;
        case 3:
            printf("thirty");
            break;
        case 4:
            printf("fourty");
            break;
        case 5:
            printf("fifty");
            break;
        case 6:
            printf("sixty");
            break;
        case 7:
            printf("seventy");
            break;
        case 8:
            printf("eighty");
            break;
        case 9:
            printf("ninety");
            break;
        default:
            break;
    }

    // end early if no singles
    if (digits % 10 == 0) {
        return 0;
    }

    // print singles
    switch(digits%10) {
        case 2:
            printf(" two\n");
            break;
        case 3:
            printf(" three\n");
            break;
        case 4:
            printf(" four\n");
            break;
        case 5:
            printf(" five\n");
            break;
        case 6:
            printf(" six\n");
            break;
        case 7:
            printf(" seven\n");
            break;
        case 8:
            printf(" eight\n");
            break;
        case 9:
            printf(" nine\n");
            break;
        default:
            break;
    }
    return 0;


}