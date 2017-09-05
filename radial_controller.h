/********************************************************************************
	*	@file     radial_controller.h
	* @author   Jay
  * @version  V1.0.0
  * @date     2017-3-22
	* @brief    head file for radial_controller.c
	******************************************************************************/

#ifndef RADIAL_CONTROLLER_H__
#define RADIAL_CONTROLLER_H__

#include <stdint.h>
#include <stdbool.h>


#define OUTPUT_REPORT_ENABLE
#define FEATURE_REPORT_ENABLE

//Macro define for the radial controller size
#define RADIAL_CONTROLLER_REPORT_WIDTH									3000										/**< Width of bounding box around a contact, const value. */

// PMT9123 default CPI(0x0B -> 1000 cpi, Register 0x48)
#define CPI_PMT9123									                    2000
#define RADIAL_CONTROL_SHELL_DIAMETER								    54.8    								/**< Diameter of radial controller's shell, int unitof millimeter. */   


#define INPUT_REP_RADIAL_CONTROLLER_INDEX								0										     /**< Index of Input Report. */
#define INPUT_REPORT_RADIAL_CONTROLLER_MAX_LEN       		8                        /**< Maximum length of the Input Report characteristic. */
#define INPUT_REP_REF_RADIAL_CONTROLLER_ID              1                        /**< Id of reference to Radial Controller Input Report. */    

#ifdef OUTPUT_REPORT_ENABLE
#define OUTPUT_REP_HAPTIC_FEEDBACK_INDEX								0									       /**< Index of Output Report. */
#define OUTPUT_REPORT_HAPTIC_FEEDBACK_MAX_LEN       		5                        /**< Maximum length of the Output Report characteristic. */
#define OUTPUT_REP_REF_HAPTIC_FEEDBACK_ID               0//2                        /**< Id of reference to Haptic Feedback Output Report. */ 
#endif

#ifdef FEATURE_REPORT_ENABLE 
#define FEATURE_REPORT_COUNT                            3//1                        /**< Number of feature reports in this application. */
#define FEATURE_REPORT_HAPTIC_CONTROL_INDEX             0                        /**< Index of Feature Report. */
#define FEATURE_REPORT_WAVEFORM_LIST_INDEX              1                        /**< Index of Feature Report. */
#define FEATURE_REPORT_DURATION_LIST_INDEX              2                        /**< Index of Feature Report. */
#define FEATURE_REPORT_HAPTIC_CONTROL_MAX_LEN           15//11                       /**< Maximum length of the Feature Report characteristic. */
#define FEATURE_REPORT_WAVEFORM_LIST_MAX_LEN            2                        /**< Maximum length of the Feature Report characteristic. */
#define FEATURE_REPORT_DURATION_LIST_MAX_LEN            2                        /**< Maximum length of the Feature Report characteristic. */
#define FEATURE_REP_REF_HAPTIC_CONTROL_ID               2                        /**< Id of reference to Featuret Report. */ 
#define FEATURE_REP_REF_WAVEFORM_LIST_ID                2//3                        /**< Id of reference to Featuret Report. */ 
#define FEATURE_REP_REF_DURATION_LIST_ID                2//4                        /**< Id of reference to Featuret Report. */ 
#endif


/** Radial Controller report data */
typedef struct
{
		bool 			 button_state;	 /**< State of the button located on radial controller */
    int16_t    dial;   				 /**< Relative rotation of the radial controller */
    uint16_t   postion_x;      /**< X coodinate of contact position */
    uint16_t   postion_y;      /**< Y coodinate of contact position */
}radial_controller_data_t;


extern radial_controller_data_t m_radial_controller;

double calculate_radial_controller_dial(int16_t delta_pos);
void radial_controller_send(bool button_state, int16_t dial, uint16_t x_delta, uint16_t y_delta);


#endif // RADIAL_CONTROLLER_H__

/** @} */
