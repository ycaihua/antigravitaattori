#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/gl.h>
#include "font.h"

const char *Font::chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!-.:";

const unsigned char Font::fontData[] = {
	0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0x00, 0xFC, 0xC6, 0xC6, 0xFC, 0xC6, 0xC6, 0xFC,
	0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00, 0xF8, 0xCC, 0xC6, 0xC6, 0xC6, 0xCC, 0xF8,
	0x00, 0xFE, 0xC0, 0xC0, 0xFC, 0xC0, 0xC0, 0xFE, 0x00, 0xFE, 0xC0, 0xC0, 0xFC, 0xC0, 0xC0, 0xC0,
	0x00, 0x3E, 0x60, 0xC0, 0xCE, 0xC6, 0x66, 0x3E, 0x00, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6,
	0x00, 0xFC, 0x30, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00, 0x1E, 0x06, 0x06, 0x06, 0xC6, 0xC6, 0x7C,
	0x00, 0xC6, 0xCC, 0xD8, 0xF0, 0xF8, 0xDC, 0xCE, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E,
	0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE, 0xC6,
	0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0xFC, 0xC6, 0xC6, 0xC6, 0xFC, 0xC0, 0xC0,
	0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xDE, 0xCC, 0x7A, 0x00, 0xFC, 0xC6, 0xC6, 0xCE, 0xF8, 0xDC, 0xCE,
	0x00, 0x78, 0xCC, 0xC0, 0x7C, 0x06, 0xC6, 0x7C, 0x00, 0xF8, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
	0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0xC6, 0xC6, 0xC6, 0xEE, 0x7C, 0x38, 0x10,
	0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0xFE, 0xEE, 0xC6, 0x00, 0xC6, 0xEE, 0x7C, 0x38, 0x7C, 0xEE, 0xC6,
	0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x30, 0x00, 0xFE, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xFE,
	0x00, 0x38, 0x4C, 0xC6, 0xC6, 0xC6, 0x64, 0x38, 0x00, 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC,
	0x00, 0x7C, 0xC6, 0x0E, 0x3C, 0x78, 0xE0, 0xFE, 0x00, 0x7E, 0x0C, 0x18, 0x3C, 0x06, 0xC6, 0x7C,
	0x00, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x00, 0xFC, 0xC0, 0xFC, 0x06, 0x06, 0xC6, 0x7C,
	0x00, 0x3C, 0x60, 0xC0, 0xFC, 0xC6, 0xC6, 0x7C, 0x00, 0xFE, 0xC6, 0x0C, 0x18, 0x30, 0x30, 0x30,
	0x00, 0x7C, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0x7C, 0x00, 0x7C, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0x78,
	0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00,
	0x00 };
	
Font Font::instance;

Font::Font()
{
}

Font &Font::getInstance()
{
	return instance;
}

int Font::init()
{
	glGenTextures(NUM_CHARS, textures);
	if(glGetError() != GL_NO_ERROR) return -1;
	
	int c, i, j;
	for(c = 0; c < NUM_CHARS; c++)
	{
		unsigned int data[64];
		
		for(i = 0; i < 8; i++)
		{
			unsigned char temp = fontData[c * 8 + i];
			unsigned char mask = 0x80;
			
			for(j = 0; j < 8; j++)
			{
				data[i * 8 + j] =(temp&mask)?(0xFFFFFFFF):(0x00000000);
				mask >>= 1;
			}
		}
		
		glBindTexture(GL_TEXTURE_2D, textures[c]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		
		if(glGetError() != GL_NO_ERROR) return -1;
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	
	return 0;
}

void Font::deinit()
{
	glDeleteTextures(NUM_CHARS, textures);
}

void Font::drawChar(char c)
{
	int i;
	if(c >= 'a' && c <= 'z') c += 'A' - 'a';
	for(i = 0; i <= NUM_CHARS; i++) if(chars[i] == c) break;
	if(i >= NUM_CHARS) return;
	
	glBindTexture(GL_TEXTURE_2D, textures[i]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(0.0, 1.0);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();
}

void Font::drawString(const char *str)
{
	glPushMatrix();
	glPushMatrix();
	
	while(*str != '\0')
	{
		if(*str == '\n')
		{
			glPopMatrix();
			glTranslatef(0.0, 1.0, 0.0);
			glPushMatrix();
		} else
		{
			drawChar(*str);
			glTranslatef(1.0, 0.0, 0.0);
		}
		
		str++;
	}
	
	glPopMatrix();
	glPopMatrix();
}

void Font::printf(const char *fmt, ...)
{
	/* based on the example code on 'man 3 vsnprintf' */
	/* Guess we need no more than 256 bytes. */
	int n, size = 256;
	char *p, *np;
	va_list ap;

	if((p = (char*)malloc(size)) == NULL) return;

	while(1)
	{
		/* Try to print in the allocated space. */
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);
		
		/* If that worked, break out of the loop */
		if(n > -1 && n < size) break;
		
		/* Else try again with more space. */
		if(n > -1)				/* glibc 2.1 */
			size = n + 1;		/* precisely what is needed */
		else					/* glibc 2.0 */
			size *= 2;			/* twice the old size */
		if((np = (char*)realloc(p, size)) == NULL)
		{
			free(p);
			return;
		} else
		{
			p = np;
		}
	}
	
	drawString(p);
	free(p);
}
