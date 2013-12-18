/* 
 * File:   statistics.h
 * Author: balhar
 *
 * Header Files should document interface
 * Source Files should document implementation
 */

#ifndef STATISTICS_H
#define	STATISTICS_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * It stores basic information about statistics.
 */
void StartStatistics(size_t rowAmount);

/*
 * It gets actual time as a stop time. Then it prints out the time of process
 * and size of matrix.
 * The data are printed into stdout.
 */ 
void StopAndPrintStatistics();


#ifdef	__cplusplus
}
#endif

#endif	/* STATISTICS_H */

