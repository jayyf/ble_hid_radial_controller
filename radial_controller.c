/********************************************************************************
	*	@file     radial_controller.c
	* @author   Jay
  * @version  V1.0.0
  * @date     2017-3-22
	* @brief    radial_controller module
	******************************************************************************/

#include <stdio.h>
#include "app_error.h"
#include "radial_controller.h"
#include "ble_gatts.h"
#include "ble_hids.h"
#ifdef RTT_LOG_ENABLED
#include "rtt_log.h"
#endif


#define RADIAL_CONTROLLER_LOG_ENABLE

#ifdef RADIAL_CONTROLLER_LOG_ENABLE
#ifdef RTT_LOG_ENABLED
#define RADIAL_LOG(format, ...)	logi(format, ##__VA_ARGS__)
#else
#define RADIAL_LOG(...)
#endif
#else
#define RADIAL_LOG(...)
#endif


radial_controller_data_t 							m_radial_controller;
extern ble_hids_t                     m_hids;
extern bool                           m_in_boot_mode;

/**@brief Function for calculating the dial of the radial controller.
 *
 * @param[in]   delta_pos   The delta Y postion of the PMT9123.
 *
 * @return      The dial value of the radial controller.
 */
double calculate_radial_controller_dial(int16_t delta_pos)
{
    double dial = 0;

    const double PI = 3.14159;
    double diameter = RADIAL_CONTROL_SHELL_DIAMETER/25.4;   //The unit of diameter is inch

    dial = (double)((double)delta_pos*360/(PI*diameter*CPI_PMT9123));
    //RADIAL_LOG("Dial=%d\r\n", dial);

    return dial;
}

/**@brief Function for sending a Mouse Movement.
 *
 * @param[in]   button_state   Button state.
 * @param[in]   dial   		Relative rotation.
 * @param[in]   x_delta   Horizontal movement.
 * @param[in]   y_delta   Vertical movement.
 */
void radial_controller_send(bool button_state, int16_t dial, uint16_t x_delta, uint16_t y_delta)
{
    uint32_t err_code;
    uint8_t buffer[INPUT_REPORT_RADIAL_CONTROLLER_MAX_LEN];

    if (m_in_boot_mode)
        return;

    buffer[0] = (button_state & 0x1) | ((dial & 0x7F) << 1); //取最低7bit,然后右移1bit
    buffer[1] = (dial >> 7) & 0xFF;       //取高8bit

    buffer[2] = x_delta & 0xFF;
    buffer[3] = (x_delta >> 8) & 0xFF;
    buffer[4] = y_delta & 0xFF;
    buffer[5] = (y_delta >> 8) & 0xFF;
    buffer[6] = RADIAL_CONTROLLER_REPORT_WIDTH & 0xFF;
    buffer[7] = (RADIAL_CONTROLLER_REPORT_WIDTH >> 8) & 0xFF;

    err_code = ble_hids_inp_rep_send(&m_hids,
                                     INPUT_REP_RADIAL_CONTROLLER_INDEX,
                                     INPUT_REPORT_RADIAL_CONTROLLER_MAX_LEN,
                                     buffer);

    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != BLE_ERROR_NO_TX_PACKETS) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       )
    {
        APP_ERROR_HANDLER(err_code);
    }
}
