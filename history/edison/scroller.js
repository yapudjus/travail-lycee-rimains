f u n c t i o n   g o T o I D ( i d )   { 
         c o n s o l e . l o g ( ` g o i n g   t o   e l e m e n t   $ { i d } ` ) ; 
         d o c u m e n t . g e t E l e m e n t B y I d ( i d ) . s c r o l l I n t o V i e w ( {   b e h a v i o r :   " s m o o t h "   } ) ; 
 } 
 
 f u n c t i o n   c h a n g e C l a s s ( o b j e c t ,   o l d C l a s s ,   n e w C l a s s )   { 
         c o n s o l e . l o g ( ` c h a n g i n g   c l a s s   $ { o l d C l a s s }   o f   o b j e c t   $ { o b j e c t }   t o   $ { n e w C l a s s } ` ) 
         v a r   r e g E x p   =   n e w   R e g E x p ( ' ( ? : ^ | \ \ s ) '   +   o l d C l a s s   +   ' ( ? ! \ \ S ) ' ,   ' g ' ) ; 
         o b j e c t . c l a s s N a m e   =   o b j e c t . c l a s s N a m e . r e p l a c e ( r e g E x p ,   n e w C l a s s ) ; 
 } 
 
 v a r   s l i d e c o u n t   =   9 ; 
 
 s e t T i m e o u t ( ( )   = >   { 
         ( f u n c t i o n   m y L o o p ( i )   { 
                 s e t T i m e o u t ( f u n c t i o n ( )   { 
                         i f   ( i   ! =   1 )   { 
                                 c o n s o l e . l o g ( ` e v e n t _ $ { s l i d e c o u n t + 3 - i } ` ) ; 
                                 g o T o I D ( i d   =   ` e v e n t _ $ { s l i d e c o u n t + 3 - i } ` ) ; 
                         } 
                         i f   ( ( s l i d e c o u n t   +   2   -   i   <   s l i d e c o u n t   +   1 )   &   ( s l i d e c o u n t   +   2   -   i   >   - 1 ) )   { 
                                 c o n s o l e . l o g ( ` s l i d e _ $ { s l i d e c o u n t + 2 - i } ` ) 
                                 g o T o I D ( ` s l i d e _ $ { s l i d e c o u n t + 2 - i } ` ) 
                         } 
                         i f   ( i   ! =   s l i d e c o u n t   +   3 )   { 
                                 c h a n g e C l a s s ( o b j e c t   =   d o c u m e n t . g e t E l e m e n t B y I d ( ` e v e n t _ $ { s l i d e c o u n t + 2 - i } ` ) ,   o l d C l a s s   =   " t i m e l i n e - e v e n t - e n a b l e d " ,   n e w C l a s s   =   " t i m e l i n e - e v e n t " ) ; 
                         } 
                         i f   ( i   >   1 )   { 
                                 c h a n g e C l a s s ( o b j e c t   =   d o c u m e n t . g e t E l e m e n t B y I d ( ` e v e n t _ $ { s l i d e c o u n t + 3 - i } ` ) ,   o l d C l a s s   =   " t i m e l i n e - e v e n t " ,   n e w C l a s s   =   " t i m e l i n e - e v e n t - e n a b l e d " ) ; 
                         } 
                         i f   ( - - i )   m y L o o p ( i ) ;   / /     d e c r e m e n t   i   a n d   c a l l   m y L o o p   a g a i n   i f   i   >   0 
                 } ,   3 0 0 0 ) 
         } ) ( s l i d e c o u n t   +   3 ) ;   / /     p a s s   t h e   n u m b e r   o f   i t e r a t i o n s   a s   a n   a r g u m e n t 
 } ,   5 0 0 0 ) ; 
 