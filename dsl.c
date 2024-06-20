#include <inttypes.h>

typedef uint8_t Std_ReturnType;
uint8_t ext_flag=0, seed_req_flag=0, send_key_flag=0;
#define E_OK 1
#define E_NOT_OK 0

//#define 10 DIAG_SESSION_CONTROL
//#define 11 ECU_RESET
//#define 02 DLC_REQ

Std_ReturnType PduR_DcmTransmit(uint8_t PduIdType, uint8_t *PduInfoType1)
{
    printf("\n\nIn DSL: \nThe PduIdType is : %x", PduIdType);

    printf("\nThe PduInfoType is : ");
    for(int i=0; i<8; i++)
    {
        printf("%.2x ", PduInfoType1[i]);
    }

    uint8_t pci_frame_id = PduInfoType1[0];
    uint8_t dlc_req = PduInfoType1[1];
    uint8_t sid = PduInfoType1[2];
    uint8_t sub_fun = PduInfoType1[3];

    printf("\nSID : %.2x", sid);
    if (dlc_req == 02)
    {
    valid_SID(sid, sub_fun, dlc_req);
    }
    else
    {
        printf("\n\nNRC: 0x13 - Incorrect Message Length");
    }

    return E_OK;
}

void valid_SID(uint8_t sid, uint8_t sub_fun,  uint8_t dlc_req)
{
    switch(sid)
    {
    case 0x10:
        printf("\nDiagnostic Session Control Service...!");

        switch(sub_fun)
        {
        case 0x01:
            printf("\nDefault Session Activated...!");

            break;
        case 0x02:
            printf("\nProgramming Session Activated...!");

            break;
        case 0x03:
            printf("\nExtended Session Activated...!\n");
            printf("positive response\n");
            printf("resp : 0x06\t0x50\t0x03\tP2\tP2*\n\n");
            ext_flag++;
            main();
            break;
        default:
            printf("\n\nNRC: 0x12 - Subfunction not supported");
            break;
        }
        break;

    case 0x11:
        printf("\nECU Reset Service...!");
        break;

    case 0x27:
        printf("\nSecurity Access Service...!\n");

        switch(sub_fun)
        {
        case 0x01:
            printf("\nLevel 1 seed request...!\n");

            break;
        case 0x03:
            printf("\nLevel 2 seed request...!\n");
            if(ext_flag == 1)
            {
                printf("positive response\n");
                printf("resp : 0x06\t0x67\t0x03\t0x11\t0x12\n\n");
                ext_flag = 0;
                seed_req_flag++;
                if(seed_req_flag == 1)
                {
                    send_key_flag++;
                    main();
                }
            }
            else
            {
                printf("NRC : 24\n");
            }
            break;
        case 0x04:
            printf("\nLevel 2 send key...!\n");
            if(send_key_flag == 1)
            {
                printf("positive response\n");
                printf("resp : 0x02\t0x67\t0x04\n\n");
                send_key_flag = 0;
            }
            else
            {
               printf("NRC : 24\n");
            }
            break;
        case 0x05:
            printf("\nLevel 3 seed request...!\n");

            break;

        default:
            printf("\n\nNRC: 0x12 - Subfunction not supported");
            break;
        }
        break;

    case 0x28:
        printf("\nCommunication Control Service...!");
        break;

    case 0x3E:
        printf("\nTester present Service...!");
        break;

    default:
        printf("\n\nNRC: 0x11 - Service not supported");

    }
    }




