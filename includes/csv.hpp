/*****************************************************************************
 *
 *  Autor: Zoé Magalhães r.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Disciplina: Controle Preditivo 01/2018
 *  Professor: André Murilo
 * 
 *  Interface de leitura aos arquivos csv 
 **/

#include <Eigen/Dense>
#include <qpOASES.hpp>
using Eigen::MatrixXd;
using Eigen::VectorXd;

USING_NAMESPACE_QPOASES

#ifndef _header_csv_
#define _header_csv_

/*****************************************************************************
 * @brief copia os valores de um arquivo .csv para uma matrix
 * @param[out] arg_matrix é o endereço da matriz que receberá os valores
 * @param[in] arg_rows é a quantidade de linhas da matriz
 * @param[in] arg_cols é a quantidade de colunas da matriz
 * @param[in] arg_csv_name é o nome do arquivo a ser lido
 *
 * @return #TRUE em caso de sucesso, #FALSE em caso de falha
 *****************************************************************************/
bool get_matrix_from_csv( MatrixXd * arg_matrix, 
                          unsigned int arg_rows, 
                          unsigned int arg_cols,
                          const char * arg_csv_name );

/*****************************************************************************
 * @brief Lê o valor registrado em um arquvo .csv
 * @param[out] arg_value é o endereço da variavel que receberá o valor lido
 * @param[in] arg_csv_name é o nome do arquivo a ser lido
 *
 * @return #TRUE em caso de sucesso, #FALSE em caso de falha
 *****************************************************************************/
bool get_value_from_csv( real_t * arg_value, 
                         const char * arg_csv_name );

/*****************************************************************************
 * @brief copia os valores de um arquivo .csv para um vetor
 * @param[out] arg_vector é o endereço do vetor que receberá os valores
 * @param[in] arg_length é a comprimento do vetor
 * @param[in] arg_csv_name é o nome do arquivo a ser lido
 *
 * @return #TRUE em caso de sucesso, #FALSE em caso de falha
 *****************************************************************************/
bool get_vector_from_csv( VectorXd * arg_vector, 
                          unsigned int arg_length, 
                          const char * arg_csv_name );
#endif
