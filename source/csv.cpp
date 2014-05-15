/*****************************************************************************
 *
 *  Autor: Zoé Magalhães r.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Disciplina: Controle Preditivo 01/2018
 *  Professor: André Murilo
 * 
 *  Implementacao da leitura dos arquivos csv  
 **/

#include "csv.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
using namespace std;


/*****************************************************************************
 * @brief copia os valores de um arquivo .csv para uma matrix
 *****************************************************************************/
bool get_matrix_from_csv( MatrixXd * arg_matrix, 
                          unsigned int arg_rows, 
                          unsigned int arg_cols,
                          const char * arg_csv_name )
{

    cout << arg_rows << " " << arg_cols << "\r\n";
    arg_matrix->setZero( arg_rows, arg_cols );
    
    std::ifstream file(arg_csv_name);
    for(unsigned int row = 0; row < arg_rows; ++row)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            return 0;

        std::stringstream iss(line);

       
        for (unsigned int col = 0; col < arg_cols; ++col)
        {
            std::string val;
            std::getline(iss, val, ',');

            std::stringstream convertor(val);
            convertor >> (*arg_matrix)(row,col);

        }
    }

    return 1;
}

/*****************************************************************************
 * @brief Lê o valor registrado em um arquvo .csv
 *****************************************************************************/
bool get_value_from_csv( real_t * arg_value, 
                         const char * arg_csv_name )
{

    
    std::ifstream file(arg_csv_name);

        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            return 0;

        std::stringstream iss(line);

        std::string val;
        std::getline(iss, val, ',');
       // if ( !iss.good() )
       //     return 0;

        std::stringstream convertor(val);
        convertor >> *arg_value;
    return 1;
}

/*****************************************************************************
 * @brief copia os valores de um arquivo .csv para um vetor
 *****************************************************************************/
bool get_vector_from_csv( VectorXd * arg_vector, 
                          unsigned int arg_length, 
                          const char * arg_csv_name )
{

    cout << arg_length << " " << "\r\n";
    arg_vector->setZero( arg_length );
    
    std::ifstream file(arg_csv_name);
    for(unsigned int member = 0; member < arg_length; ++member)
    {
        std::string line;
        std::getline(file, line);
        if ( !file.good() )
            return 0;

        std::stringstream iss(line);

        std::string val;
        std::getline(iss, val, ',');
       // if ( !iss.good() )
       //     return 0;

        std::stringstream convertor(val);
        convertor >> (*arg_vector)(member);

    }

    return 1;
}

