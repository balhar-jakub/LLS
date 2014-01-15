/* 
 * File:   codes.h
 * Author: balhar
 *
 * Created on 18. prosinec 2013, 9:23
 */

#ifndef CODES_H
#define	CODES_H

#ifdef	__cplusplus
extern "C" {
#endif

    static const int CODE_OK = 0;
    
    static const int CODE_NO_FILE = 1;
    static const int CODE_CANT_CLOSE = 2;
    static const int CODE_CANT_WRITE = 3;
    static const int CODE_WRONG_HEADER_FILE = 4;
    static const int CODE_NOT_ENOUGH_PARAMETERS = 5;
    static const int CODE_MALFORMED_PARAMETERS = 6;
    static const int CODE_MUTUAL_EXCLUSIVE_PARAMETERS = 7;
    static const int CODE_CANT_CREATE_THREAD = 8;


#ifdef	__cplusplus
}
#endif

#endif	/* CODES_H */

