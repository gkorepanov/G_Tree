// In that file, some macros for errors are defined

#ifndef ALERTS_H
#define ALERTS_H

#define DEBUGMODE 0



#define IFDEBUG(code)\
    {\
        if (DEBUGMODE) {\
            code\
        }\
    }\


#define ERRORSTR\
    fprintf(stderr, "------------------------------------------------------------------------------------------------\n"\
                    "|                                         FATAL ERROR                                          |\n"\
                    "------------------------------------------------------------------------------------------------\n");

//for errors, caused by user. Normally they must be implemented through ex's TODO(#1)
#define USERERR(...)\
    {\
        fprintf(stderr, __VA_ARGS__);\
        fprintf(stderr, "\n");\
        fflush(stderr);\
        exit(0);\
    }
     
/* Some errors that might be caused either by user, or by bugs, or by 'world', like allocation errors 
   they should be handled as well TODO(#1)*/
#define EXERR(...)\
    {\
        ERR(__VA_ARGS__);\
    }

//Actually, that is the core of alerts.h. For debugging the code and getting maximum information.
#define ERR(...)\
    {\
        ERRORSTR\
        fprintf(stderr,  __VA_ARGS__);\
        fprintf(stderr, "\nINFORMATION:"\
                        "\nFile: %s\nLine: %d\nFunction: %s\n",\
                        __FILE__, __LINE__, __PRETTY_FUNCTION__);\
        fflush(stderr);\
        exit(1);\
    }

#define DBGPRINT(...)\
    {\
        if (DEBUGMODE) {\
            printf(__VA_ARGS__);\
            printf("\n");\
        }\
    }

#endif
