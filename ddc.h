//
// Created by radix10 on 2021/5/10.
//

#ifndef DDC_LIGHT_DDC_H
#define DDC_LIGHT_DDC_H

bool
set_nc_value(
        DDCA_Display_Handle dh,
        DDCA_Vcp_Feature_Code feature_code,
        uint8_t new_value
);

DDCA_Non_Table_Vcp_Value
get_nc_value(
        DDCA_Display_Handle dh,
        DDCA_Vcp_Feature_Code feature_code
);

void
set_display_brightness(DDCA_Display_Handle dh,
                       int light);

uint8_t
get_display_brightness(DDCA_Display_Handle dh);

DDCA_Display_Handle
*open_display_by_dispno(int dispno);

void get_display_info_list();

#endif //DDC_LIGHT_DDC_H
