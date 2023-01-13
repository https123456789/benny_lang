#ifndef BLC_H_
#define BLC_H_

#define VERSION_STRING "blc v0.0.1-dev"

#define MSG_ERROR   "[\x1b[31m ERROR \x1b[0m] "
#define MSG_INFO    "[\x1b[36m INFO  \x1b[0m] "

/** read_file
 * Read the entire contents of the specified file into a string
 * @param file_name The name of the file to read
 * @return char* The contents of the file
*/
char *read_file(char *file_name);

#endif  /* BLC_H_ */
