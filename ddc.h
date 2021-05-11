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

void
set_display_light(DDCA_Display_Handle dh,
                  int light);

DDCA_Display_Handle
*open_display_by_dispno(int dispno);

#endif //DDC_LIGHT_DDC_H
