/*
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Orientador: André Murilo
 *
 *  Leitura dos sensores
 */
//BIBLIOTECAS NECESSARIAS PARA ANALOG_READ

#include "settings.hpp"
#include "measurement.hpp"
#include "pruio.h"
#include "pruio_pins.h"

#define ADC_LONG_VEL    ( 0 )
#define ADC_LAT_VEL     ( 1 )
#define ADC_YAW_RATE    ( 2 )
#define ADC_ROLL_RATE   ( 3 )
#define ADC_ROLL_ANGLE  ( 4 )
#define ADC_STEER_ANGLE ( 5 )

#define ADC_RAW_TO_ANALOG( _raw_, _out_min_, _out_max_  ) \
(((_raw_) - 0.0f)*((_out_max_) - (_out_min_))/(65520.0f - 0.0f) + 0.0f)

pruIo *_io;


const double MAX_MEASURED_VALUE[] = 
{ 
    LONG_VEL_MAX,
    LAT_VEL_MAX,
    YAW_RATE_MAX,
    ROLL_RATE_MAX,
    ROLL_ANGLE_MAX,
    STEER_ANGLE_MAX 
};


const double  MIN_MEASURED_VALUE[] = 
{ 
    LONG_VEL_MIN,
    LAT_VEL_MIN,
    YAW_RATE_MIN,
    ROLL_RATE_MIN,
    ROLL_ANGLE_MIN,
    STEER_ANGLE_MIN 
};

int init_measurements(void)
{
    _io = pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1);
    if( _io->Errr )
    {
        return -1;
    }

    if(pruio_config(_io,1,0x1FE,0,4))
    {
        return -1;
    }

    return 0;
}

void close_measurements( void )
{
    pruio_destroy(_io);
}

void get_measured_values( measured_values_t * arg_values )
{

    arg_values->long_vel_mps = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_LONG_VEL],
                                                  LONG_VEL_MIN, LONG_VEL_MAX );
    arg_values->lat_vel_mps = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_LAT_VEL],
                                                  LAT_VEL_MIN, LAT_VEL_MAX );
    arg_values->yaw_rate_radps = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_YAW_RATE],
                                                  YAW_RATE_MIN, YAW_RATE_MAX );
    arg_values->roll_rate_radps = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_ROLL_RATE],
                                                  ROLL_RATE_MIN, ROLL_RATE_MAX );
    arg_values->roll_angle_rad = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_ROLL_ANGLE],
                                                  ROLL_ANGLE_MIN, ROLL_ANGLE_MAX );
    arg_values->steer_angle_rad = ADC_RAW_TO_ANALOG( (double)_io->Adc->Value[ADC_STEER_ANGLE],
                                                  STEER_ANGLE_MIN, STEER_ANGLE_MAX );
                                                  
}

