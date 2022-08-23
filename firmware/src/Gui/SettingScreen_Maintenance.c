/** @file SettingScreen_Maintenance.c
 *  @brief The interfaces for display maintenance
 *  @author Thanh Duong
 */

/* This section lists the other files that are included in this file.
 */
#include "Gui/SettingScreen_Maintenance.h"

/* @brief Common set for maintenance screen
 * @param [in] None
 * @parma [out] None
 * @return None
 */
void SettingScreen_Maintenance_CommonSet()
{
    laWidget_SetVisible((laWidget*)SC_MaintenanceKeypad, LA_FALSE);
    laWidget_SetVisible((laWidget*)SC_MaintenanceInvalidPasswordPanel, LA_FALSE);   
}

/* @brief Init for maintenance screen
 * @param [in] None
 * @parma [out] None
 * @return None
 */
void SettingScreen_Maintenance_Init()
{
    laWidget_SetVisible((laWidget*)SC_MaintenanceKeypad, LA_TRUE);
    laWidget_SetVisible((laWidget*)SC_MaintenanceInvalidPasswordPanel, LA_FALSE);
}

// end of file
