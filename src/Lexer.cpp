#include "Lexer.h"

Lexer::Lexer()
{}


Lexer::~Lexer()
{
    int s = tokens.size();
    for(int i=0; i<s; i++)
    {
        Token* t = tokens.back();
        t->getType();
        tokens.pop_back();

        delete t;
    }
   // tokens.clear();
}

void Lexer::reset(std::string* buffer)
{

    while(tokens.size() > 0)
    {
        Token* t = tokens.back();
       tokens.pop_back();
        delete t;
    }
    tokens.clear();
    line = 1;
    this->buffer = buffer;
    pos = 0;
    startPos = 0;
   // *(this->buffer) += " ";
}

int Lexer::getPos()
{
    return pos;
}

void Lexer::tokenLine()
{
    Token* token;
    std::string lex;
   if(pos >= buffer->size())
    {
        endofline = true;
        return;
    }

    while( pos < buffer->size() )
    {
        char c  = buffer->operator[](pos);

        int oper = 4;
        int input = -1;
        if( c >= '0' && c <= '9')
              input = c_digit;
        else if( c == 'i')
             input = c_im;
        else if( (c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z') )
             input = c_alph;
        else if( c == '+' || c=='-' || c == '*' || c == '/' || c=='=' || c=='(' || c == ')')
             input = c_op;
        else if( c == '.')
             input = c_dot;
        else if( c == '\t' || c == ' ')
             input = c_ws;
        else if( c == '$' )
            input = c_newline;

        // now the real deal starts here
        switch(state)
        {
            case 0:
                if(input == c_digit)
                {
                    state = 1;
                    pos++;
                }
                else if(input == c_im)
                {
                    state = 5;
                    pos++;
                }
                else if(input == c_alph)
                {
                    state = 9;
                    pos++;
                }
                else if(input == c_op)
                {
                    state = 10;
                    pos++;
                }
                else if(input == c_ws)
                {
                    state = 11;
                    pos++;
                }
                else if(input == c_newline)
                {
                    state = 12;
                    pos++;
                }
                else
                {
                    std::cerr << "error at line "<< line << " at " << pos << " :: invalid input "<< std::endl;
                    token = new Token(ERR);
                    tokens.push_back(token);
                    return;
                }
                break;
            case 1:
                if(input == c_digit)
                {
                    state = 1;
                    pos++;
                }
                else if(input == c_dot)
                {
                    state = 2;
                    pos++;
                }
                else if(input == c_im)
                {
                    state = 4;
                    pos++;
                }
                else // something else, must retract
                {
                    state = 0;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Real_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 2:
                if(input == c_digit)
                {
                    state = 3;
                    pos++;
                }
                else // error
                {
                    std::cerr << "error at line " << line << " at " << pos << " :: expected digit after . for float \n";
                    token = new Token(ERR);
                    tokens.push_back(token);
                    return;
                }
                break;
            case 3:
                if(input == c_digit)
                {
                    state = 3;
                    pos++;
                }
                else if(input == c_im)
                {
                    state = 4;
                    pos++;
                }
                else // retract
                {
                    state = 0;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Real_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 4:
                state = 0;
                lex = buffer->substr(startPos,pos-startPos);
                startPos = pos;
                token = new Imag_T(lex);
                tokens.push_back(token);
                break;
            case 5:
                if(input == c_digit)
                {
                    state = 6;
                    pos++;
                }
                else if(input ==  c_alph || input == c_im)
                {
                    state = 9;
                    pos++;
                }
                else // retract return token
                {
                    state = 0;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Imag_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 6:
                if(input == c_digit)
                {
                    state = 6;
                    pos++;
                }
                else if(input == c_alph || input == c_im)
                {
                    state = 9;
                    pos++;
                }
                else if(input == c_dot)
                {
                    state = 7;
                    pos++;
                }
                else    // retract return token
                {
                    state = 0 ;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Imag_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 7:
                if(input == c_digit)
                {
                    state = 8;
                    pos++;
                }
                else // error
                {
                    std::cerr << "error at line "<<line<<" at pos "<<pos<<" expected digit after . \n";
                    token = new Token(ERR);
                    tokens.push_back(token);
                    return;
                }
                break;
            case 8:
                if(input == c_digit)
                {
                    state = 8;
                    pos++;
                }
                else // retract return token
                {
                    state = 0;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Imag_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 9:
                if(input == c_digit || input == c_im || input == c_alph)
                {
                    state = 9;
                    pos++;
                }
                else // retract return token
                {
                    state = 0;
                    lex = buffer->substr(startPos,pos-startPos);
                    startPos = pos;
                    token = new Iden_T(lex);
                    tokens.push_back(token);
                }
                break;
            case 10:
                state = 0;
                startPos = pos;
                c  = buffer->operator[](pos-1);
                if(c == '+')
                    token = new Token(PLUS);
                else if( c == '-')
                    token = new Token(MINUS);
                else if( c == '*')
                    token = new Token(MULT);
                else if( c == '/')
                    token = new Token(DIVI);
                else if( c == '=')
                    token = new Token(EQUAL);
                else if( c == '(')
                    token = new Token(LB);
                else if( c == ')')
                    token = new Token(RB);
               tokens.push_back(token);
               break;
            case 11:
                state = 0;
                startPos = pos;
                break;
            case 12:
                state = 0;
                line++;
                startPos = pos;
                token = new Token($);
                tokens.push_back(token);
                break;
       }
    }
}

bool Lexer::endOfLine()
{
    return endofline;
}
