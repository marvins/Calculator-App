/**
 * @file    Token.cpp
 * @author  Marvin Smith
 * @date    1/11/2023
 */
#include "Token.hpp"

// C++ Libraries
#include <sstream>

/********************************/
/*          Constructor         */
/********************************/
Token::Token( TOKEN_TYPE         tp,
              const std::string& value )
  : m_type( tp ),
    m_value( value )
{
}

/********************************/
/*          Constructor         */
/********************************/
Token::Token( TOKEN_TYPE tp )
  : m_type( tp )
{
}

/****************************************/
/*          Get the Token Type          */
/****************************************/
TOKEN_TYPE  Token::Get_Type() const
{
    return m_type;
}

/****************************************/
/*          Get the Token Value         */
/****************************************/
std::string Token::Get_Value() const
{
    return m_value;
}

/************************************/
/*          Convert to String       */
/************************************/
std::string   Token::To_String() const
{
    std::stringstream sout;
    sout << "Token, Type: " << TokenType2String( m_type ) << ", Value: " << m_value;
    return sout.str(); 
}
