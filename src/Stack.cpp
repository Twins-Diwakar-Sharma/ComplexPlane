#include <Stack.h>

void Stack::push(Node* node)
{
    storage.push_back(node);
    //std::cout << " @@@@@@@@@@@ Pushed " << node->type << " :: InhzStr(" << node->inh.zStr << ") , SynzStr(" << node->syn.zStr << ")  @@@@@@@@@@@@@@\n";
    s_top++;
}

int Stack::getSize()
{
    return storage.size();
}

void Stack::display()
{
    std::cout << "Elements in stack  : " << std::endl;
    for(int i=0; i<storage.size(); i++)
    {
        std::cout << storage[i]->type << "   ";
    }
    std::cout << std::endl;
}

void Stack::pop()
{
    Node::Element* elem;

    //std::cout << " poped " << storage[s_top]->type <<" and operator "<<storage[s_top]->op << std::endl;
   // std::cout << " inhZstr : " << storage[s_top]->inh.zStr << " & synZstr : " << storage[s_top]->syn.zStr << std::endl;

    if(storage[s_top -1]->color == RED)
    {
        elem = &(storage[s_top - 1]->syn);
    }
    else if(storage[s_top -1]->color == WHITE)
    {
        elem = &(storage[s_top - 1]->inh);
    }

    if( storage[s_top]->op == O_EQ)
    {
       *elem = storage[s_top]->syn;
       elem->pure = storage[s_top]->syn.pure;
    }
    else if (storage[s_top]->op == O_PL)
    {
     // std::cout << " inhZstr : " << storage[s_top]->inh.zStr << " & synZstr : " << storage[s_top]->syn.zStr << std::endl;

   elem->re = storage[s_top]->inh.re + storage[s_top]->syn.re;
        elem->im = storage[s_top]->inh.im + storage[s_top]->syn.im;
        elem->pure = true;
        if(!storage[s_top]->inh.pure && !storage[s_top]->syn.pure)
        {
          //  std::cout << "both not pure \n";
            elem->pure = false;
           elem->zStr = storage[s_top]->inh.zStr + "+" + storage[s_top]->syn.zStr;
        }
        else if(!storage[s_top]->inh.pure && storage[s_top]->syn.pure)
        {
         //   std::cout << " inh Not pure, syn PURE \n";
            elem->zStr = storage[s_top]->inh.zStr;
            elem->pure = false;
        }
        else if(storage[s_top]->inh.pure && !storage[s_top]->syn.pure)
        {
        //    std::cout << "inh PURE , syn not pure \n ";
             elem->zStr = storage[s_top]->syn.zStr;
             elem->pure = false;
        }
       // std::cout << "elemZstr : " << elem->zStr << std::endl;
   }
    else if (storage[s_top]->op == O_MI)
    {
        elem->re = storage[s_top]->inh.re - storage[s_top]->syn.re;
        elem->im = storage[s_top]->inh.im - storage[s_top]->syn.im;
        elem->pure = true;
        if(!storage[s_top]->inh.pure && !storage[s_top]->syn.pure)
        {
            elem->zStr = storage[s_top]->inh.zStr + "-" + storage[s_top]->syn.zStr;
            elem->pure = false;
        }
       else if(!storage[s_top]->inh.pure && storage[s_top]->syn.pure)
       {
             elem->zStr = storage[s_top]->inh.zStr;
             elem->pure = false;
       }
       else if(storage[s_top]->inh.pure && !storage[s_top]->syn.pure)
       {
             elem->zStr = "-" + storage[s_top]->syn.zStr;
             elem->pure = false;
       }
   }
    else if (storage[s_top]->op == O_MU)
    {
            Node::Element* inh = &(storage[s_top]->inh);
            Node::Element* syn = &(storage[s_top]->syn);

       // if both of them are pure
       // std::cout << " inh " << inh->pure << " , syn " << syn->pure << std::endl;
        if(inh->pure && syn->pure)
        {
           // std::cout << " Pure are both " << std::endl;
            elem->zStr = "";
            elem->re = (inh->re * syn->re) - (inh->im * syn->im);
            elem->im = (inh->im * syn->re) + (inh->re * syn->im);
            elem->pure = true;
        }
        else
        {
     //       std::cout << " NOT PURE, Processing : "<<inh->zStr << "  --  "<< syn->zStr << std::endl;
            std::string inhS;
            inhS = inh->zStr;
            if(inh->re != 0 || inh->im != 0)
                inhS += "+vec2(" + std::to_string(inh->re) + "," + std::to_string(inh->im) + ")";

            std::string synS;
            synS = syn->zStr;
            if(syn->re != 0 || syn->im != 0)
               synS += "+vec2(" + std::to_string(syn->re) + "," + std::to_string(syn->im) + ")";

            elem->zStr = "multiply(" + inhS + "," + synS + ")";
      //      std::cout << " ANS : " << elem->zStr << std::endl;
            elem->pure = false;
            elem->re = 0;
            elem->im = 0;
        }
    }
    else if (storage[s_top]->op == O_DI)
    {
            Node::Element* inh = &(storage[s_top]->inh);
            Node::Element* syn = &(storage[s_top]->syn);
            if(inh->pure && syn->pure)         // pure
            {
                elem->zStr = "";
               syn->im = -syn->im;


               elem->re = (inh->re * syn->re) - (inh->im * syn->im);
               elem->im = (inh->im * syn->re) + (inh->re * syn->im);

               float leng = (syn->re) * (syn->re) + (syn->im) * (syn->im);
               elem->re = elem->re / leng;
               elem->im = elem->im / leng;
               elem->pure = true;
            }
            else
            {
                std::string inhS;
                inhS = inh->zStr;
                if(inh->re != 0 || inh->im != 0)
                   inhS += "+vec2(" + std::to_string(inh->re) + "," + std::to_string(inh->im) + ")";

                 std::string synS;
                 synS = syn->zStr;
                 if(syn->re != 0 || syn->im != 0)
                     synS += "+vec2(" + std::to_string(syn->re) + "," + std::to_string(syn->im) + ")";

                 elem->zStr = "divide(" + inhS + "," + synS + ")";
                 elem->pure = false;
                 elem->re = 0;
                 elem->im = 0;
            }
    }
     delete storage[s_top];
    s_top--;
    storage.pop_back();
}

int Stack::top()
{
    return s_top;
}

Node* Stack::get(int i)
{
   return storage[i];
}

void Stack::clear()
{
    s_top = -1;
    while(storage.size() > 0)
    {
        delete storage.back();
        storage.pop_back();
    }
    storage.clear();
}
