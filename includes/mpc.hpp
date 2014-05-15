/*****************************************************************************
 *
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Orientaor: André Murilo
 *  
 *  Implementacao da classe que disponibiliza o controle preditivo
 *  baseado em modelo linear
 **/

#include <qpOASES.hpp>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;

USING_NAMESPACE_QPOASES

#ifndef _header_mpc_
#define _header_mpc_

/*****************************************************************************
 * @brief descritor do controle preditivo
 *****************************************************************************/
class MPC
{
    MatrixXd  H;                /**< Hessiano da função custo */
    MatrixXd  A;                /**< Matriz das restricoes */
    MatrixXd  PI_E;             /**< Matriz de parametrizacao */
    MatrixXd  G1;               /**< Matriz de restrição dos estados */
    MatrixXd  G2;               /**< Matriz de restrição da variacao do comando*/
    VectorXd  _G3;              /**< Vetor com limiar da restrição */
    MatrixXd  F1;               /**< Gradiente do custo em relacao ao estado atual */
    MatrixXd  F2;               /**< Gradiente do custo em relacao a trajetoria desejada */
    MatrixXd  F3;               /**< Gradiente do custo em relacao ao comando desejado */
    QProblem Solver;      /**< Ponteiro para um descritor do solver qpOASES */
    VectorXd  _last_command;    /**< Último comando enviado */
    real_t  _cmd_ub_;           /**< Limiar superior do comando */
    real_t  _cmd_lb_;           /**< Limiar inferior do comando */
    qpOASES::Options Solver_options;
    public:
        /**
         * @breif Construtor
         */
        MPC(void); 

        /**
         * @brief Realiza a QP para definir o proximo valor do comando
         * @param[in] arg_steer indica o esterçamento das rodas dianteiras
         * @param[in] arg_desired_yaw_rate indica o valor desejado da taxa
         * da taxa de guinada
         * @param[in] arg_x indica o valor atual dos estaados
         * @param[out] arg_sol informa o valor do comando encontrado como solucao
         */
        void get_next_command( double arg_steer, double arg_desired_yaw_rate, 
                               VectorXd * arg_x, VectorXd * arg_sol );
};
#endif
