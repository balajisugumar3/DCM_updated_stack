#include <stdio.h>
#include <inttypes.h>

typedef uint8_t Std_ReturnType;
#define E_OK 1
#define E_NOT_OK 0

uint8_t PduInfoType[8];

void main()
{
    printf("Enter the Elements (in hex format): ");
    for(int i=0; i<8; i++)
    {
        scanf("%x", &PduInfoType[i]);        //00 02 10 03 00 00 00 00 //00 02 27 03 00 00 00 00 //00 02 27 04 12 11 00 00
    }

    printf("\nIn Main: \nThe above SDU is : ");
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", PduInfoType[i]);
    }

    uint8_t PduIdType = PduInfoType[0];

    Std_ReturnType result = PduR_DcmTransmit(PduIdType, &PduInfoType[0]);

    if(result == 1)
    {
        printf("\nResult : E_OK");
    }
    else
    {
        printf("\nResult : E_NOT_OK");
    }

}

//Std_ReturnType  PduR_DcmTransmit(Std_ReturnType, PduIdType, const PduInfoType*):
//Dcm_TpRxIndication(PduIdType, Std_ReturnType);

