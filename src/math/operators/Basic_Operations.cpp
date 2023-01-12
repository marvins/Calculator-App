/**
 * @file    Basic_Operations.cpp
 * @author  Marvin Smith
 * @date    1/12/2023
 */
#include "Basic_Operations.hpp"

// C++ Libraries
#include <cmath>

/************************************/
/*          Addition Operator       */
/************************************/
int Operation_Plus::Get_Number_Operands() const
{
    return 2;
}

Token Operation_Plus::Process( const std::vector<Token>& values ) const
{
    return Token( TOKEN_TYPE::NUMBER,
                  std::to_string( values[0].Get_Value<double>() + 
                                  values[1].Get_Value<double>() ) );
}

bool Operation_Plus::Check( const Token& token ) const
{
    return ( token.Get_Type() == TOKEN_TYPE::OPERATOR_PLUS );
}

bool Operation_Plus::Is_Operation( const std::string& command ) const
{
    return ( command == "+" );
}

/***************************************/
/*          Subtraction Operator       */
/***************************************/
int Operation_Minus::Get_Number_Operands() const
{
    return 2;
}

Token Operation_Minus::Process( const std::vector<Token>& values ) const
{
    return Token( TOKEN_TYPE::NUMBER,
                  std::to_string( values[0].Get_Value<double>() -
                                  values[1].Get_Value<double>() ) );
}

bool Operation_Minus::Check( const Token& token ) const
{
    return ( token.Get_Type() == TOKEN_TYPE::OPERATOR_MINUS );
}

bool Operation_Minus::Is_Operation( const std::string& command ) const
{
    return ( command == "-" );
}

/******************************************/
/*          Multiplication Operator       */
/******************************************/
int Operation_Times::Get_Number_Operands() const
{
    return 2;
}

Token Operation_Times::Process( const std::vector<Token>& values ) const
{
    return Token( TOKEN_TYPE::NUMBER,
                  std::to_string( values[0].Get_Value<double>() *
                                  values[1].Get_Value<double>() ) );
}

bool Operation_Times::Check( const Token& token ) const
{
    return ( token.Get_Type() == TOKEN_TYPE::OPERATOR_TIMES );
}

bool Operation_Times::Is_Operation( const std::string& command ) const
{
    return ( command == "*" );
}

/************************************/
/*          Division Operator       */
/************************************/
int Operation_Divide::Get_Number_Operands() const
{
    return 2;
}

Token Operation_Divide::Process( const std::vector<Token>& values ) const
{
    return Token( TOKEN_TYPE::NUMBER,
                  std::to_string( values[0].Get_Value<double>() /
                                  values[1].Get_Value<double>() ) );
}

bool Operation_Divide::Check( const Token& token ) const
{
    return ( token.Get_Type() == TOKEN_TYPE::OPERATOR_DIVIDE );
}

bool Operation_Divide::Is_Operation( const std::string& command ) const
{
    return ( command == "/" );
}

/*********************************/
/*          Power Operator       */
/*********************************/
int Operation_Power::Get_Number_Operands() const
{
    return 2;
}

Token Operation_Power::Process( const std::vector<Token>& values ) const
{
    return Token( TOKEN_TYPE::NUMBER,
                  std::to_string( std::pow( values[0].Get_Value<double>(),
                                            values[1].Get_Value<double>() ) ) );
}

bool Operation_Power::Check( const Token& token ) const
{
    return ( token.Get_Type() == TOKEN_TYPE::OPERATOR_POWER );
}

bool Operation_Power::Is_Operation( const std::string& command ) const
{
    return ( command == "^" );
}
