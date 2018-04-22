/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dseabel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 14:17:36 by dseabel           #+#    #+#             */
/*   Updated: 2018/04/22 15:40:15 by dseabel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int isAvailable(int **puzzle, int row, int col, int num)
{
    int row_start = (row/3) * 3;
    int col_start = (col/3) * 3;
    int i;

    i = 0;
    while (i < 9)
    {
        if (puzzle[row][i] == num) //checks if in row
            return (0);
        if (puzzle[i][col] == num) //checks if in col
            return (0);
        if (puzzle[row_start + (i % 3)][col_start + (i / 3)] == num) //checks if in block
            return (0);
        i++;
    }
    return (1); //return true if no match found
}

int fillSudoku(int **puzzle, int row, int col)
{
    int i;

    i = 0;
    if(row < 9 && col < 9)
    {
        if(puzzle[row][col] != 0) //if occupied by a valid number
        {
		 if ((col + 1) < 9) //if next col is not out of bounds
                return fillSudoku(puzzle, row, col + 1); //go to next col
            else if ((row + 1) < 9) //if next row not out of bounds
                return fillSudoku(puzzle, row + 1, 0); //go to next row
            else return (1); //otherwise all occupied
        }
        else //if occupied by invalid number
        {
            while (i < 9) //go through all rows
            {
                if (isAvailable(puzzle, row, col, i + 1)) //if the next number can be used
                {
                    puzzle[row][col] = i + 1; //invalid number replaced by i+1 value
                    if ((col + 1) < 9) //if the next col is not out of bounds
                    {
                        if (fillSudoku(puzzle, row, col + 1)) //go to next col
                            return (1); //the i+1 number has been successfully added
                        else puzzle[row][col] = 0; //the i+1 number cannot be used in the current block
                    }
                    else if ((row + 1) < 9) //if the next row is not out of bounds and at end of the col for current row
                    {
                        if (fillSudoku(puzzle, row + 1, 0)) //go to next row
                            return (1); //the i+1 number has been successfully added
                        else puzzle[row][col] = 0; //the i+1 number cannot be used in the current block
                    }
                    else return (1); //already filled
                }
				 }
                i++; //increment to go to next row
            }
        }
        return (0); //invalid input
    }
    //else 
	//return (1); //successfully filled the puzzle
//}

void    fill_input(int **puzzle, int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i] != '\0')
    {
        j = 0;
        while (argv[i][j] != '\0' && i < 10)
        {
            if (argv[i][j] == '.')
                argv[i][j] = 0;
            puzzle[i - 1][j] = atoi(&argv[i][j]);
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    int i;
    int j;
    int **puzzle;

    i = 1;
    j = 0;
    puzzle = (int**)malloc(sizeof(int**) * 9);
    while (j < 9)
    {
        puzzle[j] = (int*)malloc(sizeof(int*) * 9);
        j++;
    }
    j = 0;
    if (argc == 10)
    {
        fill_input(puzzle, argc, argv);
        if(fillSudoku(puzzle, 0, 0))
         {
            printf("\n+-----+-----+-----+\n");
            while (i < 10)
            {
                while (j < 9)
                {
                    printf("|%i", puzzle[i-1][j]);
                    j++;
                }
                printf("|\n");
                if (i%3 == 0) printf("+-----+-----+-----+\n");
                j = 0;
                i++;
            }
			   }
    }
    else printf("\n\nNO SOLUTION\n\n");

    return (0);
}
