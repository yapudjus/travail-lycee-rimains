s e t T i m e o u t ( ( )   = >   { 
         / /   G e t   t h e   m o d a l 
         v a r   m o d a l   =   d o c u m e n t . g e t E l e m e n t B y I d ( ' m y M o d a l ' ) ; 
         / /   G e t   t h e   i m a g e   a n d   i n s e r t   i t   i n s i d e   t h e   m o d a l   -   u s e   i t s   " a l t "   t e x t   a s   a   c a p t i o n 
         v a r   m o d a l I m g   =   d o c u m e n t . g e t E l e m e n t B y I d ( " i m g 0 1 " ) ; 
         v a r   c a p t i o n T e x t   =   d o c u m e n t . g e t E l e m e n t B y I d ( " c a p t i o n " ) ; 
         c o n s t   i m g _ z o o m s   =   [ 
                 " d s g f " , 
                 " r g 1 2 " , 
                 " e d g 5 " , 
                 " e r s 6 " , 
                 " a p c 4 " 
         ] 
         f o r   ( l e t   i   =   0 ;   i   <   i m g _ z o o m s . l e n g t h ;   i + + )   { 
                 c o n s o l e . l o g ( ` i m g _ z o o m s [ $ { i } ]   =   $ { i m g _ z o o m s [ i ] } ` ) ; 
                 c o n s o l e . l o g ( ` d o c u m e n t . g e t E l e m e n t B y I d ( $ { i m g _ z o o m s [ i ] } )   =   $ { d o c u m e n t . g e t E l e m e n t B y I d ( i m g _ z o o m s [ i ] ) } ` ) ; 
                 v a r   i m g   =   d o c u m e n t . g e t E l e m e n t B y I d ( ` $ { i m g _ z o o m s [ i ] } _ i m g ` ) ; 
                 i m g . o n c l i c k   =   f u n c t i o n ( )   { 
                         m o d a l . s t y l e . d i s p l a y   =   " b l o c k " ; 
                         m o d a l I m g . s r c   =   t h i s . s r c ; 
                         m o d a l I m g . a l t   =   t h i s . a l t ; 
                         c a p t i o n T e x t . i n n e r H T M L   =   t h i s . a l t ; 
                 } 
         } 
 
         / /   W h e n   t h e   u s e r   c l i c k s   o n   < s p a n >   ( x ) ,   c l o s e   t h e   m o d a l 
         m o d a l . o n c l i c k   =   f u n c t i o n ( )   { 
                 i m g 0 1 . c l a s s N a m e   + =   "   o u t " ; 
                 s e t T i m e o u t ( f u n c t i o n ( )   { 
                         m o d a l . s t y l e . d i s p l a y   =   " n o n e " ; 
                         i m g 0 1 . c l a s s N a m e   =   " m o d a l - c o n t e n t " ; 
                 } ,   4 0 0 ) ; 
 
         } 
 } ,   5 0 0 0 ) ; 