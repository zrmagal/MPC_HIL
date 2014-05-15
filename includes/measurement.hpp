
/*
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Orientador: André Murilo
 *
 *  Leitura dos sensores
 */

#ifndef _header_measurement_
#define _header_measurement_

/**
 * Variaveis medidas
 */
typedef struct measured_values_struct
{
    double long_vel_mps;        /*<< Velocidade longitudinal em m/s */ 
    double lat_vel_mps;         /*<< Velocidade lateral em m/s */
    double yaw_rate_radps;      /*<< Taxa de guinada em rad/s */
    double roll_rate_radps;     /*<< Taxa de rolagem em rad/s */
    double roll_angle_rad;      /*<< Angulo de rolagem em rad */
    double steer_angle_rad;     /*<< Angulo de estercamento das rodas dianteiras em rad */
}measured_values_t;

/**
 * @brief Leitura das variaveis medidas
 *
 * @param[out] arg_values e o endereco que recebera as variaveis medidas. Ver #measured_values_t;
 * 
 */
void get_measured_values( measured_values_t * arg_values ); 

/**
 * @brief Inicia o acesso aos sensores
 */
int init_measurements( void );

/**
 * @brief Encerra o acesso aos sensores liberando os recursos 
 */
void close_measurements( void );
#endif
