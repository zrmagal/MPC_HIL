/*****************************************************************************
 *
 *  Autor: Zoé Magalhães (zr.magal@gmail.com)
 *  Mestrando do PPMEC-Unb, matrícula 170172767
 *  Orientador: André Murilo
 *  
 *  Implementacao da classe que disponibiliza o controle preditivo
 *  baseado em modelo linear
 **/
 
#include "mpc.hpp"
#include "settings.hpp"
#include "csv.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <Eigen/Eigenvalues>
using namespace std;


/*****************************************************************************
 * Tamanho das matrizes
 *****************************************************************************/
#define H_ROWS QP_SIZE
#define H_COLS QP_SIZE
#define H_SIZE ( H_ROWS*H_COLS )

#define A_ROWS BOUNDED_CONSTRAINTS_SIZE
#define A_COLS QP_SIZE
#define A_SIZE (A_ROWS*A_COLS)

#define PI_E_ROWS (INPUT_SIZE*HORIZON_SIZE)
#define PI_E_COLS QP_SIZE
#define PI_E_SIZE ( PI_E_ROWS*PI_E_COLS )

#define G1_ROWS CONSTRAINTS_SIZE 
#define G1_COLS STATES_SIZE
#define G1_SIZE ( G1_ROWS*G1_COLS )

#define G2_ROWS CONSTRAINTS_SIZE
#define G2_COLS COMMAND_SIZE
#define G2_SIZE ( G2_ROWS*G2_COLS )

#define _G3_SIZE CONSTRAINTS_SIZE

#define F1_ROWS (INPUT_SIZE*HORIZON_SIZE)
#define F1_COLS (STATES_SIZE)
#define F1_SIZE ( F1_ROWS*F1_COLS )

#define F2_ROWS (INPUT_SIZE*HORIZON_SIZE)
#define F2_COLS (REG_OUTPUTS_SIZE*HORIZON_SIZE)
#define F2_SIZE ( F2_ROWS*F2_COLS )

#define F3_ROWS (INPUT_SIZE*HORIZON_SIZE)
#define F3_COLS (INPUT_SIZE)
#define F3_SIZE ( F3_ROWS*F3_COLS )



/*****************************************************************************
 * @brief Construtor do descritor de controle preditivo
 *****************************************************************************/
MPC::MPC(void)
{
    /****************************
     *Leitura dos arquivos .csv
     ***************************/
    cout << "\r\nH\r\n";
    if( !get_matrix_from_csv(&H,H_ROWS,H_COLS,"input/H.csv") )
        cout << "\r\n Erro ao ler H";

    cout << "\r\nA\r\n";
    if( !get_matrix_from_csv(&A,A_ROWS,A_COLS,"input/A_CONSTRAINT.csv") )
        cout << "\r\n Erro ao ler A";

    cout << "\r\nPI_E\r\n";
    if( !get_matrix_from_csv(&PI_E,PI_E_ROWS,PI_E_COLS,"input/PI_E.csv") )
        cout << "\r\n Erro ao ler PI_E";
    
    cout << "\r\nG1\r\n";
    if( !get_matrix_from_csv(&G1,G1_ROWS,G1_COLS,"input/G1.csv") )
        cout << "\r\n Erro ao ler G1";

    cout << "\r\nG2\r\n";
    if( !get_matrix_from_csv(&G2,G2_ROWS,G2_COLS,"input/G2.csv") )
        cout << "\r\n Erro ao ler G2";

    cout << "\r\nG3\r\n";
    if( !get_vector_from_csv(&_G3,_G3_SIZE,"input/G3.csv") )
        cout << "\r\n Erro ao ler G3";

    cout << "\r\nF1\r\n";
    if( !get_matrix_from_csv(&F1,F1_ROWS,F1_COLS,"input/F1.csv") )
        cout << "\r\n Erro ao ler F1";

    cout << "\r\nF2\r\n";
    if( !get_matrix_from_csv(&F2,F2_ROWS,F2_COLS,"input/F2.csv") )
        cout << "\r\n Erro ao ler F2";

    cout << "\r\nF3\r\n";
    if( !get_matrix_from_csv(&F3,F3_ROWS,F3_COLS,"input/F3.csv") )
        cout << "\r\n Erro ao ler F3";
    
    cout << "\r\ncmd_lb\r\n";
    if( !get_value_from_csv(&_cmd_lb_,"input/cmd_lb.csv") )
        cout << "\r\n Erro ao ler _cmd_lb_";
    
    cout << "\r\ncmd_ub\r\n";
    if( !get_value_from_csv(&_cmd_ub_,"input/cmd_ub.csv") )
        cout << "\r\n Erro ao ler cmd_ub";

    cout << "\r\nub\r\n" <<_cmd_ub_;
    cout << "\r\nlb\r\n" <<_cmd_lb_;
   
    MatrixXd transp;
    
    transp = H.transpose();
    H = transp;
    transp = A.transpose();
    A = transp;
    
    //Calcula o valor inicial do comando
    _last_command.setZero(1);
}

/*****************************************************************************
 * @brief Fornece o proximo valor do comando
 *****************************************************************************/
void MPC::get_next_command( double arg_steer, double arg_desired_yaw_rate, 
        VectorXd * arg_x,  VectorXd * arg_sol )
{
    VectorXd _B = VectorXd::Zero(BOUNDED_CONSTRAINTS_SIZE);
    VectorXd _F = VectorXd::Zero(QP_SIZE);
    VectorXd _track = VectorXd::Ones(TRACK_SIZE,1)*arg_desired_yaw_rate;
    static VectorXd _sol = VectorXd::Zero(QP_SIZE,1);
    static VectorXd _sol2 = VectorXd::Zero(QP_SIZE,1);
    VectorXd _in_ub(INPUT_SIZE);
    VectorXd _in_lb(INPUT_SIZE);
    VectorXd _horizon_in_ub(INPUT_SIZE*HORIZON_SIZE);
    VectorXd _horizon_in_lb(INPUT_SIZE*HORIZON_SIZE);
    VectorXd _desired_input(INPUT_SIZE);
    VectorXd _sol_lb(QP_SIZE);
    VectorXd _sol_ub(QP_SIZE);
    int_t _nWSR_ = 20;
    static bool first = 1;

    //Comando sejado
    // comando controlado igual a zero e valor atual igual a ele mesmo
    _desired_input << 0, arg_steer; 
    
    //Restricao trivial do comando
    //Comando controlado limitado por seus valores maximos minimos
    //Entrada nao controlada limitada ao seu valor medido a priore
    _in_ub << _cmd_ub_ , arg_steer;
    _in_lb << _cmd_lb_ , arg_steer;
    
       
    //Expansão da restrição no horzionte de predição
    _horizon_in_ub = _in_ub.replicate(HORIZON_SIZE,1);
    _horizon_in_lb = _in_lb.replicate(HORIZON_SIZE,1);

    //Restrição da solução com parametrezição exponencial
    //Parametros do comando controlado limitados aos limites do comando
    //Parametros da entrada nao controlada limitados ao seu valor atual
    _sol_lb << _cmd_lb_, _cmd_lb_, _cmd_lb_, arg_steer;
    _sol_ub << _cmd_ub_, _cmd_ub_, _cmd_ub_, arg_steer;

     //Calcular limiar das restrições A * sol < _B
     _B.head(CONSTRAINTS_SIZE) = G1*(*arg_x) + G2*_last_command + _G3;
       
     _B.segment(CONSTRAINTS_SIZE,INPUT_SIZE*HORIZON_SIZE) = -_horizon_in_lb;
     
     _B.tail(INPUT_SIZE*HORIZON_SIZE) = _horizon_in_ub;

    //cout << "\r\n" << _B;
    //Calcula gradiente da função custo
    _F = F1*(*arg_x)+ F2*_track + F3*_desired_input;
    _F = PI_E.transpose()*_F;

   
    
    //Realiza qp
    if( first )
    {

        Solver=qpOASES::QProblem( QP_SIZE, BOUNDED_CONSTRAINTS_SIZE );
        Solver_options.printLevel = qpOASES::PL_LOW;
        Solver.setOptions(Solver_options);
        Solver.init( H.data(), _F.data(), A.data(), _sol_lb.data(), _sol_ub.data(), NULL, _B.data(), _nWSR_ );
        first = 0;
    }
    else  
    {
         Solver.hotstart(_F.data(),_sol_lb.data(),_sol_ub.data(),NULL,_B.data(),_nWSR_ ); 
    }


    //Le o resultado da qp
    Solver.getPrimalSolution(_sol.data());


    //cout << "\r\nsol\r\n" << _sol;
    _last_command = PI_E.block(0,0,COMMAND_SIZE,QP_SIZE)*_sol;
    *arg_sol = _last_command;
}

