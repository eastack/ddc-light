//
// Created by radix10 on 2021/5/10.
//
#include <ddcutil_c_api.h>
#include "ddc.h"


#define DDC_ERRMSG(function_name, status_code)\
    printf("(%s) %s() returned %d (%s): %s\n",\
    __func__, function_name, status_code,\
    ddca_rc_name(status_code),\
    ddca_rc_desc(status_code))

DDCA_Display_Handle
*open_display_by_dispno(int dispno) {
    printf("Opening display %d...\n", dispno);
    DDCA_Display_Identifier did;
    DDCA_Display_Ref dref;
    DDCA_Display_Handle dh = NULL;

    ddca_create_dispno_display_identifier(dispno, &did);
    DDCA_Status rc = ddca_get_display_ref(did, &dref);
    if (rc != 0) {
        DDC_ERRMSG("ddca_create_display_ref", rc);
    } else {
        rc = ddca_open_display2(dref, false, &dh);
        if (rc != 0) {
            DDC_ERRMSG("ddca_open_display", rc);
        } else {
            printf("Opened display handle: %s\n", ddca_dh_repr(dh));
        }
    }
    return dh;
}

bool
set_nc_value(
        DDCA_Display_Handle dh,
        DDCA_Vcp_Feature_Code feature_code,
        uint8_t new_value
) {
    ddca_reset_stats();
    bool saved_enable_verify = ddca_enable_verify(true);
    ddca_set_non_table_vcp_value(dh, feature_code, 0, new_value);
    ddca_enable_verify(saved_enable_verify);
}

DDCA_Non_Table_Vcp_Value
get_nc_value(DDCA_Display_Handle dh,
             DDCA_Vcp_Feature_Code feature_code) {
    DDCA_Non_Table_Vcp_Value valrec;

    ddca_get_non_table_vcp_value(dh, feature_code, &valrec);

    return valrec;
}

void
set_display_brightness(DDCA_Display_Handle dh,
                       int light) {
    set_nc_value(dh, 0x10, light);
}

uint8_t
get_display_brightness(DDCA_Display_Handle dh) {
    return get_nc_value(dh, 0x10).sl;
}
