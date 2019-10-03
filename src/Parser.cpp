#include "Parser.h"

Parser::Parser()
{
    lexer = new Lexer();

    prod[0] = &Parser::fM;
    prod[1] = &Parser::fX0; prod[2] = &Parser::fX1;
    prod[3] = &Parser::fE;
    prod[4] = &Parser::fE_0; prod[5] = &Parser::fE_1; prod[6] = &Parser::fE_2;
    prod[7] = &Parser::fT;
    prod[8] = &Parser::fT_0; prod[9] = &Parser::fT_1; prod[10] = &Parser::fT_2;
    prod[11] = &Parser::fF0; prod[12] = &Parser::fF1; prod[13] = &Parser::fF2; prod[14] = &Parser::fF3;
    prod[15] = &Parser::fY0; prod[16] = &Parser::fY1;
    prod[17] = &Parser::fH0; prod[18] = &Parser::fH1;

    initTable();

    currID = new Identifier();
}

Parser::~Parser()
{
    delete currID;
   // delete lexer;
}

void Parser::reset(std::string* buffer, std::string zLexeme)
{
    tokenIndex = 0;
    symbol::purge();

    lexer->reset(buffer);
    symbol::z = zLexeme;
    bool isZ;
   symbol::fetchId(symbol::z,&isZ,&finalZ);
   finalZ->zStr = "z";

    end = false;
    line = 1;

}


void Parser::display()
{
    lexer->tokenLine();
    for(int i=0; i<lexer->tokens.size(); i++)
    {
        Token* token = lexer->tokens[i];
        if(token == nullptr || token == NULL)
        {
            std::cout << "Haulted due to error " << std::endl;
            return;
        }


        int type = token->getType();
    //    std::cout << type << std::endl;

        if( type == IDEN)
        {
            Iden_T* iden = (Iden_T*)token;
            //std::cout << " Identifier("<< iden->getLexeme() << ") ";
            bool isZ;
            Identifier* symIden;
            symbol::fetchId(iden->getLexeme(),&isZ,&symIden);
            if(isZ)
            {
                std::cout << " IdenZ(" << symbol::z << ") ";
            }
            else
            {
                std::cout << " Identifier(" << iden->getLexeme() << ") ";
            }
        }
        else if(type == IMAG)
        {
            Imag_T* ima = (Imag_T*)token;
            std::cout << " Imaginary(" << ima->getValue() << ") ";
        }
        else if(type == REAL)
        {
            Real_T* rea = (Real_T*)token;
            std::cout << " Real(" << rea->getValue() << ") ";
        }
        else if(type == $)
        {
            std::cout << " $ "  << std::endl;
        }
        else if(type == PLUS)
        {
            std::cout << " + ";
        }
        else if(type == MINUS)
        {
            std::cout << " - ";
        }
        else if(type == MULT)
        {
            std::cout << " * ";
        }
        else if(type == DIVI)
        {
            std::cout << " / ";
        }
        else if(type == EQUAL)
        {
            std::cout << " = ";
        }
        else if(type == LB)
        {
            std::cout << " ( ";
        }
        else if(type == RB)
        {
            std::cout << " ) ";
        }
        else if(type == ERR)
        {
            std::cout << " err \n" ;
        }

    //   delete lexer->tokens[i];
    }
}

bool Parser::parseAndTranslate(std::string* compiledCode)
{

    lexer->tokenLine();
    Node* dollar = new Node;
    dollar->type = $;
    stac.push(dollar);
    Node* m = new Node;
    m->type = M;
    stac.push(m);
    int times = 0;
    while(!end)
    {
        times++;
        Node* tos = stac.get(stac.top());
    //    std::cout << "\n\n" << times << "> Input token["<<tokenIndex<<"] type : " << lexer->tokens[tokenIndex]->getType() << "  &&  Stack top type : " << tos->type << "\n";
       if(tos->color == WHITE)
        {
 //           std::cout << " tos color white " ;

            if( tos->type >= 900)  // is Non Terminal
             {
//                 std::cout << " && is a NonTerminal " << std::endl;
                  // apply production
                    int input = lexer->tokens[tokenIndex]->getType();
   //                 std::cout<<"Idarich>>>>>>>>>>>>>>>::::::::::::(((((((((((((())))))))))))))";
                    int stackTop = tos->type;
                    int prodIndex = getProd(stackTop,input);
                    if(prodIndex < 0)
                    {
                        *compiledCode = "Error in line " + std::to_string(line);
                        return false;
                    }
                   else
                   {
//                       std::cout << "production " << prodIndex << " chosen. Applying ... " << std::endl;
                        (this->*prod[prodIndex])();
                   }
           }
           else  // is a Terminal
          {
                   int termType = tos->type;
                   if(termType != lexer->tokens[tokenIndex]->getType())
                   {
                        *compiledCode = "ERROR in line " + std::to_string(line) + ": Unexpected terminal found ";
                        return false;
                   }
                    if(termType == PLUS)
                        fPlus();
                     else if(termType == MINUS)
                        fMinus();
                     else if(termType == MULT)
                        fMultiply();
                     else if(termType == DIVI)
                        fDivide();
                     else if(termType == LB)
                        fLB();
                     else if(termType == RB)
                        fRB();
                     else if(termType == LB)
                        fLB();
                     else if(termType == IDEN)
                     {
                       fIden();
                     }
                     else if(termType == $)
                    {
                        fDollar();
      //                  std::cout << "Budbak";
                    }
                    else if(termType == EQUAL)
                        fEqual();
                    else if(termType == REAL)
                        fReal();
                    else if(termType == IMAG)
                        fImag();
                     else if(termType == ERR)
                     {
                        *compiledCode = "Error detected !! Token not recognized ";
                        return false;
                     }

          }
       }
       else if(tos->color == RED) // already processed
       {
            stac.pop();
       }
   }
    *compiledCode = finalZ->zStr;
    return true;
}

void Parser::fM()
{
    stac.get(stac.top())->color = RED;

    Node* x = new Node;
    x->type = X;
    stac.push(x);

    Node* equ = new Node;
    equ->type = EQUAL;
    stac.push(equ);

    Node* ide = new Node;
    ide->type = IDEN;
    stac.push(ide);
}

void Parser::fX0()
{
    stac.get(stac.top())->color = RED;

    Node* e = new Node;
    e->type = E;
    stac.push(e);

    Node* minuss = new Node;
    minuss->type = MINUS;
    stac.push(minuss);

}

void Parser::fX1()
{
    stac.get(stac.top())->color = RED;

    Node* e = new Node;
    e->type = E;
    stac.push(e);
}

void Parser::fE()
{
    stac.get(stac.top())->color = RED;
   // std::cout << "Inh zStr of E -- " << stac.get(stac.top())->inh.zStr  << "  -- "<< std::endl;
    Node* e_ = new Node;
    e_->type = E_;
    stac.push(e_);

    Node* t = new Node;
    t->type = T;
    stac.push(t);

    stac.get(stac.top())->inh = stac.get(stac.top()-2)->inh;
}

void Parser::fE_0()
{
    stac.get(stac.top())->color = RED;

    Node* e_ = new Node;
    e_->type = E_;
    stac.push(e_);

    Node* t = new Node;
    t->type = T;
    stac.push(t);

    Node* pluss = new Node;
    pluss->type = PLUS;
    stac.push(pluss);

    stac.get(stac.top())->inh = stac.get(stac.top() - 3)->inh;
}


void Parser::fE_1()
{
    stac.get(stac.top())->color = RED;

    Node* e_ = new Node;
    e_->type = E_;
    stac.push(e_);

    Node* t = new Node;
    t->type = T;
    stac.push(t);

    Node* minuss = new Node;
    minuss->type = MINUS;
    stac.push(minuss);

    stac.get(stac.top())->inh = stac.get(stac.top() - 3)->inh;
}

void Parser::fE_2()
{
    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh;
}

void Parser::fT()
{
    //std::cout << "inh zStr of T --- " << stac.get(stac.top())->inh.zStr << " ---\n";
    stac.get(stac.top())->color = RED;

    Node* t_ = new Node;
    t_->type = T_;
    stac.push(t_);

    Node* f = new Node;
    f->type = F;
    stac.push(f);

    stac.get(stac.top())->inh = stac.get(stac.top()-2)->inh;
}
void Parser::fT_0()
{
    stac.get(stac.top())->color = RED;

    Node* t_ = new Node;
    t_->type = T_;
    stac.push(t_);

    Node* f = new Node;
    f->type = F;
    stac.push(f);

    Node* mult = new Node;
    mult->type = MULT;
    stac.push(mult);

    stac.get(stac.top())->inh = stac.get(stac.top() - 3)->inh;
}

void Parser::fT_1()
{
    stac.get(stac.top())->color = RED;

    Node* t_ = new Node;
    t_->type = T_;
    stac.push(t_);

    Node* f = new Node;
    f->type = F;
    stac.push(f);

    Node* divi = new Node;
    divi->type = DIVI;
    stac.push(divi);

    stac.get(stac.top())->inh = stac.get(stac.top() - 3)->inh;
}

void Parser::fT_2()
{

    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh;
}

void Parser::fF0()
{
    //std::cout << "Inh str of F *** " << stac.get(stac.top())->inh.zStr << " **\n";
    stac.get(stac.top())->color = RED;

    Node* ide = new Node;
    ide->type = IDEN;
    stac.push(ide);

    stac.get(stac.top())->inh = stac.get(stac.top()-1)->inh;
}

void Parser::fF1()
{
    stac.get(stac.top())->color = RED;

    Node* rea = new Node;
    rea->type = REAL;
    stac.push(rea);

    stac.get(stac.top())->inh = stac.get(stac.top()-1)->inh;
}

void Parser::fF2()
{
    stac.get(stac.top())->color = RED;

    Node* imagine = new Node;
    imagine->type = IMAG;
    stac.push(imagine);

    stac.get(stac.top())->inh = stac.get(stac.top()-1)->inh;
}

void Parser::fF3()
{
    stac.get(stac.top())->color = RED;

    Node* why = new Node;
    why->type = Y;
    stac.push(why);

    Node* lBrack = new Node;
    lBrack->type = LB;
    stac.push(lBrack);

    stac.get(stac.top())->inh = stac.get(stac.top()-2)->inh;
}

void Parser::fY0()
{
    stac.get(stac.top())->color = RED;

    Node* rBrack = new Node;
    rBrack->type = RB;
    stac.push(rBrack);

    Node* e = new Node;
    e->type = E;
    stac.push(e);

    stac.get(stac.top())->inh = stac.get(stac.top()-2)->inh;
}

void Parser::fY1()
{
    stac.get(stac.top())->color = RED;

    Node* rBrack = new Node;
    rBrack->type = RB;
    stac.push(rBrack);

    Node* h = new Node;
    h->type = H;
    stac.push(h);

    Node* minuss = new Node;
    minuss->type = MINUS;
    stac.push(minuss);

    //stac.get(stac.top())->inh = stac.get(stac.top()-3)->inh;
}

void Parser::fH0()
{
    stac.get(stac.top())->color = RED;

    Node* re = new Node;
    re->type = REAL;
    stac.push(re);

}

void Parser::fH1()
{
    stac.get(stac.top())->color = RED;

    Node* im = new Node;
    im->type = IMAG;
    stac.push(im);
}




// tokens
void Parser::fPlus()
{
    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh; // syn = inh
    stac.get(stac.top()-1)->op = O_PL; // set operator to plus to terminal below it
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fMinus()
{
    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh;
    stac.get(stac.top()-1)->op = O_MI;
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fMultiply()
{
    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh;
    stac.get(stac.top()-1)->op = O_MU;
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fDivide()
{
    stac.get(stac.top())->color = RED;

    stac.get(stac.top())->syn = stac.get(stac.top())->inh;
    stac.get(stac.top()-1)->op = O_DI;
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fEqual()
{
    stac.get(stac.top())->color = RED;
    bool isZ;
    Identifier* fet;
    symbol::fetchId(stac.get(stac.top())->syn.zStr, &isZ, &fet);
    currID->zStr = fet->zStr;
    currID->re = fet->re;
    currID->im = fet->im;
    currIDLex = stac.get(stac.top())->syn.zStr;
    if(isZ)
        finalZ = fet;
    //stac.get(stac.top())->syn.zStr = stac.get(stac.top())->inh.zStr + "=";
    stac.get(stac.top()-1)->op = O_EQ;
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fIden()
{
    //std::cout << "Inh str of iden !!! " << stac.get(stac.top())->inh.zStr << " !!!\n";
    stac.get(stac.top())->color = RED;
            Iden_T* iden = (Iden_T*)(lexer->tokens[tokenIndex]);
            bool isZ;
            Identifier* symIden;
            symbol::fetchId(iden->getLexeme(),&isZ,&symIden);
           // std::cout << "################## " <<iden->getLexeme() << " : zStr(" << symIden->zStr << ") , im(" << symIden->im << ") , re(" << symIden->re << ") , pure(" << symIden->pure <<")\n";
        //    std::cout<<isZ<<" aaaaooooooooooooooooooo \n";
            if(isZ)
            {
                if(stac.get(stac.top()-1)->type == EQUAL) // equal is below me
                {
                     stac.get(stac.top()-1)->syn.zStr = symbol::z;
                }
                stac.get(stac.top())->syn.zStr = symIden->zStr;
                stac.get(stac.top())->syn.re = symIden->re;
                stac.get(stac.top())->syn.im = symIden->im;
                stac.get(stac.top())->syn.pure = symIden->pure;
          //      std::cout<<"here";
            }
            else
            {
                if(stac.get(stac.top()-1)->type == EQUAL) // equal is below me
                {
                     stac.get(stac.top()-1)->syn.zStr = iden->getLexeme();
                }
                stac.get(stac.top())->syn.zStr = symIden->zStr;
                stac.get(stac.top())->syn.re = symIden->re;
                stac.get(stac.top())->syn.im = symIden->im;
                stac.get(stac.top())->syn.pure = symIden->pure;

            }
            //std::cout<<"here 1";
            lexer->tokens[tokenIndex]->discard();
           // std::cout<<"Here 2";
            //lexer->tokens.erase(lexer->tokens.begin() + tokenIndex -1);
            tokenIndex++;
}

void Parser::fLB()
{
    stac.get(stac.top())->color = RED;

    //stac.get(stac.top())->syn.zStr = std::string("(");
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fRB()
{
    stac.get(stac.top())->color = RED;

    //if inh->zStr has only ( then keep re and im and remove zStr
    Node::Element* inh = &(stac.get(stac.top())->inh);
    //std::cout << "I am RB , purity is " << inh->pure << std::endl;
    if(inh->pure)
    {
        stac.get(stac.top())->syn.zStr = "";
        stac.get(stac.top())->syn.re = inh->re;
        stac.get(stac.top())->syn.im = inh->im;
        stac.get(stac.top())->syn.pure = true;
    }
    else
    {
        std::string oss;
        oss = "(" + inh->zStr ;
        if( inh->re != 0 || inh->im !=0)
            oss += "+vec2(" + std::to_string(inh->re) + "," + std::to_string(inh->im) + ")";
        oss += ")";
        stac.get(stac.top())->syn.zStr = oss;
        stac.get(stac.top())->syn.re = 0;
        stac.get(stac.top())->syn.im = 0;
        stac.get(stac.top())->syn.pure = false;
    }
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fDollar()
{
    //std::cout <<  "\n Here my friend holy $ was called \n\n";
    line++;

    currID->zStr = stac.get(stac.top())->inh.zStr;
    currID->re = stac.get(stac.top())->inh.re;
    currID->im = stac.get(stac.top())->inh.im;
    currID->pure = stac.get(stac.top())->inh.pure;
    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;

    // donot use pop as there is nothing below $
    //clear stack instead
   // stac.clear();
    bool isZ;
    Identifier* resetID;
    symbol::fetchId(currIDLex,&isZ,&resetID);
    resetID->zStr = currID->zStr;
    resetID->re = currID->re;
    resetID->im = currID->im;
    resetID->pure = currID->pure;

    std::string sss = currID->zStr + "vec2(" + std::to_string(currID->re) + "," + std::to_string(currID->im) + ")";
    if(tokenIndex >= lexer->tokens.size())
    {

          sss = "z=" + finalZ->zStr;
        if(finalZ->re != 0 || finalZ->im != 0)
           sss += "+vec2(" + std::to_string(finalZ->re) + "," + std::to_string(finalZ->im) + ")";
        sss += ";";
        finalZ->zStr = sss;
    //    std::cout << "\n(((((((((((((((((((((((finaly)))))))))))))))))))))))\n";
       stac.clear();
        end = true;
    }
    else
    {

        Node* m = new Node;
         m->type = M;
         stac.push(m);
    }
}

void Parser::fReal()
{
    stac.get(stac.top())->color = RED;

    Real_T* rea = (Real_T*)(lexer->tokens[tokenIndex]);
    stac.get(stac.top())->syn.re = rea->getValue();
    //stac.get(stac.top())->syn.im = 0;
    stac.get(stac.top())->syn.pure = true;

    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::fImag()
{
    stac.get(stac.top())->color = RED;

    Imag_T* ima = (Imag_T*)(lexer->tokens[tokenIndex]);
    stac.get(stac.top())->syn.im = ima->getValue();
    //stac.get(stac.top())->syn.re = 0;
    stac.get(stac.top())->syn.pure = true;

    lexer->tokens[tokenIndex]->discard();
    tokenIndex++;
}

void Parser::initTable()
{
    for(int i=0; i<9; i++)
        for(int j=0; j<11; j++)
            table[i][j] = -1;

    table[0][7] = 0;
    table[1][1] = 1; table[1][5] = 2; table[1][7] = 2; table[1][9] = 2; table[1][10] = 2;
    table[2][5] = 3; table[2][7] = 3; table[2][9] = 3; table[2][10] = 3;
    table[3][0] = 4; table[3][1] = 5; table[3][6] = 6; table[3][8] = 6;
    table[4][5] = 7; table[4][7] = 7; table[4][9] = 7; table[4][10] = 7;
    table[5][0] = 10; table[5][1] = 10; table[5][2] = 8; table[5][3] = 9; table[5][6] = 10; table[5][8] = 10;
    table[6][5] = 14; table[6][7] = 11; table[6][9] = 12; table[6][10] = 13;
    table[7][1] = 16; table[7][5] = 15; table[7][7] = 15; table[7][9] = 15; table[7][10] = 15;
}

int Parser::getProd(int NonT, int Term)
{
    NonT = NonT - 900;
    Term = Term - 500;

    return table[NonT][Term];
}
