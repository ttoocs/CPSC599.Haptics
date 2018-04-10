#pragma once

#define r5_c12

//Note: this has been swapped:
#define c(Y,X)  case X : return Y ; break;

#ifdef r5_c12

rfbKeySym getKey(char c){
  switch (c) {
    c(XK_dead_grave , '`' )
    c(XK_1 , '1' )
    c(XK_2 , '2' )
    c(XK_3 , '3' )
    c(XK_4 , '4' )
    c(XK_5 , '5' )
    c(XK_6 , '6' )
    c(XK_7 , '7' )
    c(XK_8 , '8' )
    c(XK_9 , '9' )
    c(XK_0 , '0' )
    c(XK_plusminus , '-' )
    c(XK_KP_Equal , '=' )
    c(XK_BackSpace  , '\b' )

    c(XK_Tab , '\t')
    c(XK_Q , 'q' )
    c(XK_W , 'w' )
    c(XK_E , 'e' )
    c(XK_R , 'r' )
    c(XK_T , 't' )
    c(XK_Y , 'y' )
    c(XK_U , 'u' )
    c(XK_I , 'i' )
    c(XK_O , 'o' )
    c(XK_P , 'p' )
//    c( , '[' )
//    c(111 , ']' )
//    c(112 , '\\' )
    
    
    c(XK_A , 'a' )
    c(XK_S , 's' )
    c(XK_D , 'd' )
    c(XK_F , 'f' )
    c(XK_A , 'g' )
    c(XK_H , 'h' )
    c(XK_Q , 'j' )
    c(XK_K , 'k' )
    c(XK_L , 'l' )
//    c(XK_ , ';' )
//    c(211 , '\'' )
    c(XK_Return , '\n' )

    
    c(XK_Z , 'z' )
    c(XK_X , 'x' )
    c(XK_C , 'c' )
    c(XK_V , 'v' )
    c(XK_B , 'b' )
    c(XK_N , 'n' )
    c(XK_M , 'm' )
//    c(XK_ , ',' )
//    c(309 , '.' )
//    c(310 , '/' )

    c(XK_KP_Space, ' ')

    default: return XK_VoidSymbol ; break;
}
}


#endif
