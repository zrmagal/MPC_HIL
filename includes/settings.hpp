/*****************************************************************************
 *
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Disciplina: Controle Preditivo 01/2018
 *  Professor: André Murilo
 * 
 *  Configuracoes do programa 
 **/
 
/*****************************************************************************
 * Configuracoes
 *****************************************************************************/
//Quantidade estados
#define STATES_SIZE (4)
//Quantidade de parâmetros de decisão da QP
#define QP_SIZE (4)
//Quantidade de entradas controladas
#define COMMAND_SIZE (1)
//Quantidade de entradas não controladas
#define DIST_SIZE (1)
//Quantidade amostras no horizonte de predição
#define HORIZON_SIZE (101)
//Quantidade de estados regulados
#define REG_OUTPUTS_SIZE (1)
//Quantidade de estados com restrição imposta
#define CONST_OUTPUTS_SIZE (1)
//Quantidade total de entradas controladas e não controladas
#define INPUT_SIZE ( DIST_SIZE + COMMAND_SIZE )
//Quantidade de restrições
// - restrição nos estados ( CONST_OUTPUTS_SIZES * HORIZON_SIZE)*2
// - restrição na variação das entradas ( INPUT_SIZE * HORIZON_SIZE)*2
#define CONSTRAINTS_SIZE (( CONST_OUTPUTS_SIZE + INPUT_SIZE )*2*HORIZON_SIZE)
// Tamanho do vetor de trajetoria desejada
#define TRACK_SIZE ( REG_OUTPUTS_SIZE*HORIZON_SIZE )
// Quantidade de restrição incluindo:
// - restrição no valor das entradas  INPUT_SIZE*HORIZON_SIZE*2
#define BOUNDED_CONSTRAINTS_SIZE ( CONSTRAINTS_SIZE + INPUT_SIZE*HORIZON_SIZE*2 )

// Valores maximos e minimos das variaveis medidas
#define LONG_VEL_MAX           ( 1 )
#define LONG_VEL_MIN           ( -1 )
#define LAT_VEL_MAX            ( 1 )
#define LAT_VEL_MIN            ( -1 )
#define YAW_RATE_MAX           ( 1 )
#define YAW_RATE_MIN           ( -1 )
#define ROLL_RATE_MAX          ( 1 )
#define ROLL_RATE_MIN          ( -1 )
#define ROLL_ANGLE_MAX         ( 1 )
#define ROLL_ANGLE_MIN         ( -1 )
#define STEER_ANGLE_MAX        ( 1 )
#define STEER_ANGLE_MIN        ( -1 )


