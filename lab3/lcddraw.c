/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"

//creates a plane
/** 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */

void randomDraw(char col, char row, u_int colorBGR)
{
  for (int i = 0; i < row; i += 2)
  {
    drawPixel(col, row, COLOR_BLACK);
    col *row / 2;
    row++;
    for (int j = 0; j < col; j += 2)
    {
      drawPixel(col, row, COLOR_BLACK);
      col / 2;
      row *col / 5;
    }
  }
}
void jet(char col, char row, u_int colorBGR)
{
  int i;
  //top center
  drawPixel(50, 50, COLOR_BLACK);

  //left side

  //next level size 2
  drawPixel(49, 51, COLOR_BLACK);
  drawPixel(49, 52, COLOR_BLACK);

  //next level size 3
  drawPixel(48, 53, COLOR_BLACK);
  drawPixel(48, 54, COLOR_BLACK);
  drawPixel(48, 55, COLOR_BLACK);

  //next level size 2
  drawPixel(47, 56, COLOR_BLACK);
  drawPixel(47, 57, COLOR_BLACK);

  //next level size 4
  drawPixel(46, 58, COLOR_BLACK);
  drawPixel(45, 58, COLOR_BLACK);
  drawPixel(44, 58, COLOR_BLACK);
  drawPixel(43, 58, COLOR_BLACK);
  drawPixel(42, 58, COLOR_BLACK);
  drawPixel(41, 58, COLOR_BLACK);
  drawPixel(40, 58, COLOR_BLACK);

  //down one
  drawPixel(40, 59, COLOR_BLACK);

  //under part of first arm
  drawPixel(41, 60, COLOR_BLACK);
  drawPixel(42, 60, COLOR_BLACK);
  //next level
  drawPixel(43, 61, COLOR_BLACK);
  drawPixel(44, 61, COLOR_BLACK);
  //next level
  drawPixel(45, 62, COLOR_BLACK);
  drawPixel(46, 62, COLOR_BLACK);
  //next level
  drawPixel(47, 63, COLOR_BLACK);
  drawPixel(47, 64, COLOR_BLACK);
  drawPixel(47, 65, COLOR_BLACK);

  //legs
  drawPixel(46, 66, COLOR_BLACK);
  drawPixel(46, 67, COLOR_BLACK);

  //last line
  drawPixel(47, 67, COLOR_BLACK);
  drawPixel(48, 67, COLOR_BLACK);
  drawPixel(49, 67, COLOR_BLACK);
  drawPixel(50, 67, COLOR_BLACK);
  drawPixel(51, 67, COLOR_BLACK);
  drawPixel(52, 67, COLOR_BLACK);
  drawPixel(53, 67, COLOR_BLACK);
  drawPixel(54, 67, COLOR_BLACK);

  //right side
  //next level size 2
  drawPixel(51, 51, COLOR_BLACK);
  drawPixel(51, 52, COLOR_BLACK);

  //next lvel size 3
  drawPixel(52, 53, COLOR_BLACK);
  drawPixel(52, 54, COLOR_BLACK);
  drawPixel(52, 55, COLOR_BLACK);

  //next level size 2
  drawPixel(53, 56, COLOR_BLACK);
  drawPixel(53, 57, COLOR_BLACK);

  //next level size 6
  drawPixel(54, 58, COLOR_BLACK);
  drawPixel(55, 58, COLOR_BLACK);
  drawPixel(56, 58, COLOR_BLACK);
  drawPixel(57, 58, COLOR_BLACK);
  drawPixel(58, 58, COLOR_BLACK);
  drawPixel(59, 58, COLOR_BLACK);
  drawPixel(60, 58, COLOR_BLACK);

  //down 1
  drawPixel(60, 59, COLOR_BLACK);

  //under part of second arm
  drawPixel(59, 60, COLOR_BLACK);
  drawPixel(58, 60, COLOR_BLACK);
  //next level
  drawPixel(57, 61, COLOR_BLACK);
  drawPixel(56, 61, COLOR_BLACK);
  //next level
  drawPixel(55, 62, COLOR_BLACK);
  drawPixel(54, 62, COLOR_BLACK);
  //next level
  drawPixel(53, 63, COLOR_BLACK);
  drawPixel(53, 64, COLOR_BLACK);
  drawPixel(53, 65, COLOR_BLACK);

  //legs
  drawPixel(54, 66, COLOR_BLACK);
  drawPixel(54, 67, COLOR_BLACK);
}

/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR)
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height,
                   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total)
  {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR)
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c,
                 u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8)
  {
    while (col < 5)
    {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

void drawChar8x12(u_char rcol, u_char rrow, char c,
                  u_int fgColorBGR, u_int bgColorBGR)
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x80;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 7, rrow + 12); /* relative to requested col/row */
  while (row < 13)
  {
    while (col < 8)
    {
      u_int colorBGR = (font_8x12[oc][row] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
      bit >>= 1;
    }
    col = 0;
    bit = 0x80;
    row++;
  }
}
void drawString8x12(u_char col, u_char row, char *string,
                    u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string)
  {
    drawChar8x12(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 9;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
                   u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string)
  {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
                     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

// calls star to draw the shape star.
//basically a help function
void drawJet()
{
  jet(40, 30, COLOR_WHITE);
}

void drawRand()
{
  randomDraw(10, 10, COLOR_BLACK);
}