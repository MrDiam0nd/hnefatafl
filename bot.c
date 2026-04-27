#include "main.h"
#include "draw.h"

struct move botrandom(struct board board, int turn)
{
    int piecesx[16] = {-1};
    int piecesy[16] = {-1};
    int queenx = -1;
    int queeny = -1;

    int listlength = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            int piece = getpiece(board, i+j*9);
            if(piece == 0x1 && board.turn == 0)
            {
                piecesx[listlength] = i;
                piecesy[listlength] = j;
                listlength++;
            }
            if(piece == 0x1 && board.turn == 1)
            {
                piecesx[listlength] = i;
                piecesy[listlength] = j;
                listlength++;
            }
            if(piece == 0x2 && board.turn == 1)
            {
                queenx = i;
                queeny = j;
            }
        }
    }
    listlength -= 1;

    int selectedpiece = GetRandomValue(0, listlength);
    
    int possiblemovesx[16] = {-1};
    int possiblemovesy[16] = {-1};
    int possiblemovesnumber = 0;

    for (int i = 0; i<9;i++)
    {
        if(checklegal(board, piecesx[selectedpiece], piecesy[selectedpiece], piecesx[selectedpiece], i) == 1)
        {
            possiblemovesx[possiblemovesnumber] = piecesx[selectedpiece];
            possiblemovesy[possiblemovesnumber] = i;
            possiblemovesnumber++;
        }
        if(checklegal(board, piecesx[selectedpiece], piecesy[selectedpiece], i, piecesy[selectedpiece]) == 1)
        {
            possiblemovesx[possiblemovesnumber] = i;
            possiblemovesy[possiblemovesnumber] = piecesy[selectedpiece];
            possiblemovesnumber++;
        }
    }
    possiblemovesnumber -= 1;
    int move = GetRandomValue(0, possiblemovesnumber);

    struct move result = {piecesx[selectedpiece], piecesy[selectedpiece], possiblemovesx[move], possiblemovesy[move]};

    return result;
}