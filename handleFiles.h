/* 
 * File:   handleFiles.h
 * Author: balhar
 *
 * Created on 17. prosinec 2013, 14:01
 */

#ifndef HANDLEFILES_H
#define	HANDLEFILES_H

#ifdef	__cplusplus
extern "C" {
#endif

floattype **loadMatrix(char *filePath);
void saveMatrix(floattype **matrix, char *filePath, size_t amountOfRows, size_t amountOfCols);

#ifdef	__cplusplus
}
#endif

#endif	/* HANDLEFILES_H */