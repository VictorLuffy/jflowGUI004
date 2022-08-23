/** @file SettingScreen_Maintenance.h
 *  @brief The interfaces for display maintenance screen
 *  @author Thanh Duong
 */

#ifndef SETTINGSCREEN_MAINTENANCE_H
#define	SETTINGSCREEN_MAINTENANCE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "Gui/Setting.h"
#include "Gui/StatusBar.h"
#include "Gui/DisplayControl.h"

/* @brief Common set for maintenance screen
 * @param [in] None
 * @parma [out] None
 * @return None
 */
void SettingScreen_Maintenance_CommonSet(void);

/* @brief Init for maintenance screen
 * @param [in] None
 * @parma [out] None
 * @return None
 */
void SettingScreen_Maintenance_Init(void);

#endif

/* end of file */
